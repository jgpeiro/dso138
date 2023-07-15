/*
 * task_dso.c
 *
 *  Created on: May 9, 2020
 *      Author: jose
 */

#include "task_dso.h"
#include "cmsis_os.h"
#include "imgui.h"
#include "task_adc.h"
#include <stdlib.h> //itoa

int16_t get_vmin( int16_t *buffer, int16_t len )
{
	int16_t i = 0;
	int16_t value = buffer[0];
	for( i = 0 ; i < len ; i++ )
	{
		if( buffer[i] < value )
		{
			value = buffer[i];
		}
	}
	return value;
}

int16_t get_vmax( int16_t *buffer, int16_t len )
{
	int16_t i = 0;
	int16_t value = buffer[0];
	for( i = 0 ; i < len ; i++ )
	{
		if( buffer[i] > value )
		{
			value = buffer[i];
		}
	}
	return value;
}

int16_t get_vavg( int16_t *buffer, int16_t len )
{
	int16_t i = 0;
	int32_t value = 0;

	for( i = 0 ; i < len ; i++ )
	{
		value += buffer[i];
	}

	return value/len;
}

int16_t get_period( int16_t *buffer, int16_t len, int16_t mx, int16_t mn, int16_t avg )
{
	int16_t t0 = 0;
	int16_t t1 = 0;
	int16_t t2 = 0;
	int16_t i = 0;

	int16_t thr1 = mn + 3*(mx - mn)/4;
	int16_t thr2 = mn + 1*(mx - mn)/4;

	if( abs(mx - mn) < 20 )
	{
		return 0;
	}

	for( i = 0 ; i < len-1 ; i++ )
	{
		if( buffer[i] > thr1 && buffer[i+1] <= thr1 )
		{
			t0 = i;
			for( i = t0+1 ; i < len-1 ; i++ )
			{
				if( buffer[i] < thr2 && buffer[i+1] >= thr2 )
				{
					t1 = i;
					for( i = t1+1 ; i < len-1 ; i++ )
					{
						if( buffer[i] > thr1 && buffer[i+1] <= thr1 )
						{
							t2 = i;
							return t2-t0;
						}
					}
				}
			}
		}
	}

	return 0;

}

int16_t get_duty( int16_t *buffer, int16_t len, int16_t mx, int16_t mn, int16_t avg )
{
	int16_t t0 = 0;
	int16_t t1 = 0;
	int16_t t2 = 0;
	int16_t i = 0;

	int16_t thr1 = mn + 3*(mx - mn)/4;
	int16_t thr2 = mn + 1*(mx - mn)/4;

	if( abs(mx - mn) < 20 )
	{
		return 0;
	}

	for( i = 0 ; i < len-1 ; i++ )
	{
		if( buffer[i] > thr1 && buffer[i+1] <= thr1 )
		{
			t0 = i;
			for( i = t0+1 ; i < len-1 ; i++ )
			{
				if( buffer[i] < thr2 && buffer[i+1] >= thr2 )
				{
					t1 = i;
					for( i = t1+1 ; i < len-1 ; i++ )
					{
						if( buffer[i] > thr1 && buffer[i+1] <= thr1 )
						{
							t2 = i;
							if( (t1-t0) == 0 )
							{
								return 0;
							}
							else
							{
								return 100-(100*(t1-t0))/(t2-t0);
							}
						}
					}
				}
			}
		}
	}

	return 0;
}

char *signal_paths[27] =
{
	"10 mVDC", "0.1 VDC", "  1 VDC",
	"20 mVDC", "0.2 VDC", "  2 VDC",
	"50 mVDC", "0.5 VDC", "  5 VDC",

	"10 mVAC", "0.1 VAC", "  1 VAC",
	"20 mVAC", "0.2 VAC", "  2 VAC",
	"50 mVAC", "0.5 VAC", "  5 VAC",

	"    GND", "    GND", "    GND",
	"    GND", "    GND", "    GND",
	"    GND", "    GND", "    GND",
};

char *sample_freqs[] = {
	"1 uS", "2 uS", "5 uS",
	"10 uS", "20 uS", "50 uS",
	"100 uS", "200 uS", "500 uS",
	"1 mS", "2 mS", "5 mS",
	"10 mS", "20 mS", "50 mS",
	"100 mS", "200 mS", "500 mS"
};

const uint16_t arr_table[18] =
{ 			// @ fcpu = 72e6 and presc = 35+1
	1,		//   1 uS
	3,		//   2 uS
	9,		//   5 uS
	19,		//  10 uS
	39,		//  20 uS
	99,		//  50 uS
	199,	// 100 uS
	399,	// 200 uS
	999,	// 500 uS

	1999,	//   1 mS
	3999,	//   2 mS
	9999,	//   5 mS
	19999,	//  10 mS
	39999,	//  20 mS
	99999&0xFFFF,	//  50 mS // uint16_t
	199999&0xFFFF,	// 100 mS // uint16_t
	399999&0xFFFF,	// 200 mS // uint16_t
	999999&0xFFFF,	// 500 mS // uint16_t
};

void update_measurements( tDsoState *pState )
{
	static TickType_t xLastWakeTime = 0;
	TickType_t xCurrentTime;

	xCurrentTime = xTaskGetTickCount();
	if( xCurrentTime - xLastWakeTime < 100  )
	{
		return;
	}
	xLastWakeTime = xCurrentTime;

	int16_t mx = get_vmax( pState->buffer, 320 );
	int16_t mn = get_vmin( pState->buffer, 320 );
	int16_t avg = get_vavg( pState->buffer, 320 );
	int16_t vamp = mx - mn;
	int16_t freq = get_period( pState->buffer, 320, mx, mn, avg );
	int16_t duty = get_duty( pState->buffer, 320, mx, mn, avg );

	static char text_vmax[8];
	static char text_vmin[8];
	static char text_vavg[8];
	static char text_vamp[8];
	static char text_vfreq[8];
	static char text_vduty[8];

	/*33 BUTTON Vmax
	34 BUTTON Vmin
	35 BUTTON Vavg
	36 BUTTON Freq
	37 BUTTON Duty
	72 BUTTON Vamp
	*/

	/*int16_t a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
	switch( pState->pWidgets[33].value )
	{
		case 0:
			a = mx;
			break;
		case 1:
			a = mn;
			break;
		case 2:
			a = avg;
			break;
		case 3:
			a = vamp;
			break;
		case 4:
			a = freq;
			break;
		case 5:
			a = duty;
			break;
		default:
			break;
	}
	switch( pState->pWidgets[34].value )
	{
		case 0:
			b = mx;
			break;
		case 1:
			b = mn;
			break;
		case 2:
			b = avg;
			break;
		case 3:
			b = vamp;
			break;
		case 4:
			b = freq;
			break;
		case 5:
			b = duty;
			break;
		default:
			break;
	}
	switch( pState->pWidgets[35].value )
	{
		case 0:
			c = mx;
			break;
		case 1:
			c = mn;
			break;
		case 2:
			c = avg;
			break;
		case 3:
			c = vamp;
			break;
		case 4:
			c = freq;
			break;
		case 5:
			c = duty;
			break;
		default:
			break;
	}

	switch( pState->pWidgets[36].value )
	{
		case 0:
			d = mx;
			break;
		case 1:
			d = mn;
			break;
		case 2:
			d = avg;
			break;
		case 3:
			d = vamp;
			break;
		case 4:
			d = freq;
			break;
		case 5:
			d = duty;
			break;
		default:
			break;
	}
	switch( pState->pWidgets[37].value )
	{
		case 0:
			e = mx;
			break;
		case 1:
			e = mn;
			break;
		case 2:
			e = avg;
			break;
		case 3:
			e = vamp;
			break;
		case 4:
			e = freq;
			break;
		case 5:
			e = duty;
			break;
		default:
			break;
	}
	switch( pState->pWidgets[72].value )
	{
		case 0:
			f = mx;
			break;
		case 1:
			f = mn;
			break;
		case 2:
			f = avg;
			break;
		case 3:
			f = vamp;
			break;
		case 4:
			f = freq;
			break;
		case 5:
			f = duty;
			break;
		default:
			break;
	}*/
	itoa( mx, text_vmax, 10 );
	itoa( mn, text_vmin, 10 );
	itoa( avg, text_vavg, 10 );
	itoa( vamp, text_vamp, 10 );
	itoa( freq, text_vfreq, 10 );
	itoa( duty, text_vduty, 10 );

	pState->pWidgets[38].text = text_vmax;
	pState->pWidgets[39].text = text_vmin;
	pState->pWidgets[40].text = text_vavg;
	pState->pWidgets[73].text = text_vamp;
	pState->pWidgets[41].text = text_vfreq;
	pState->pWidgets[42].text = text_vduty;

	widget_clear( &pState->pWidgets[38], 0xF7BE );
	widget_draw( &pState->pWidgets[38] );
	widget_clear( &pState->pWidgets[39], 0xF7BE );
	widget_draw( &pState->pWidgets[39] );
	widget_clear( &pState->pWidgets[40], 0xF7BE );
	widget_draw( &pState->pWidgets[40] );
	widget_clear( &pState->pWidgets[73], 0xF7BE );
	widget_draw( &pState->pWidgets[73] );
	widget_clear( &pState->pWidgets[41], 0xF7BE );
	widget_draw( &pState->pWidgets[41] );
	widget_clear( &pState->pWidgets[42], 0xF7BE );
	widget_draw( &pState->pWidgets[42] );
}

void update_cursors( tDsoState *pState )
{
	static TickType_t xLastWakeTime = 0;
	TickType_t xCurrentTime;

	xCurrentTime = xTaskGetTickCount();
	if( xCurrentTime - xLastWakeTime < 100  )
	{
		return;
	}
	xLastWakeTime = xCurrentTime;

	int16_t x1 = pState->cursor_a;
	int16_t x2 = pState->cursor_b;
	int16_t dx = x2-x1;
	int16_t y1 = pState->buffer[x1];
	int16_t y2 = pState->buffer[x2];
	int16_t dy = y2-y1;

	static char text_x1[8];
	static char text_x2[8];
	static char text_dx[8];
	static char text_y1[8];
	static char text_y2[8];
	static char text_dy[8];

	itoa( x1, text_x1, 10 );
	itoa( x2, text_x2, 10 );
	itoa( dx, text_dx, 10 );
	itoa( y1, text_y1, 10 );
	itoa( y2, text_y2, 10 );
	itoa( dy, text_dy, 10 );

	pState->pWidgets[53].text = text_x1;
	pState->pWidgets[54].text = text_x2;
	pState->pWidgets[55].text = text_dx;
	pState->pWidgets[56].text = text_y1;
	pState->pWidgets[57].text = text_y2;
	pState->pWidgets[58].text = text_dy;

	widget_clear( &pState->pWidgets[53], 0xF7BE );
	widget_draw( &pState->pWidgets[53] );
	widget_clear( &pState->pWidgets[54], 0xF7BE );
	widget_draw( &pState->pWidgets[54] );
	widget_clear( &pState->pWidgets[55], 0xF7BE );
	widget_draw( &pState->pWidgets[55] );
	widget_clear( &pState->pWidgets[56], 0xF7BE );
	widget_draw( &pState->pWidgets[56] );
	widget_clear( &pState->pWidgets[57], 0xF7BE );
	widget_draw( &pState->pWidgets[57] );
	widget_clear( &pState->pWidgets[58], 0xF7BE );
	widget_draw( &pState->pWidgets[58] );
}

tRectangle get_scope_rect( void )
{
	/*
0 TOGGLE #149#;#150#
1 COMBOBOX Auto;Normal;Single
2 TOGGLE #040#
3 TOGGLE #041#
4 TOGGLE #126#
5 TOGGLE #160#
6 TOGGLE #048#
7 TOGGLE #068#
	 */
	tRectangle rect = { 0, 20, 320, 200 };
	if( widgets[2].value == 1
	 || widgets[3].value == 1
	 || widgets[4].value == 1
	 || widgets[5].value == 1
	 || widgets[6].value == 1 )
	{
		rect.width = 320-80;
		rect.height = 200;
	}
	else if( widgets[7].value == 1 )
	{
		rect.width = 320;
		rect.height = 200-80;
	}
	else
	{
		rect.width = 320;
		rect.height = 200;
	}


	return rect;
}

void task_dso( void const * argument )
{
	static int16_t buffer1[320];
	static int16_t buffer2[320];

	tQueueAdcRequest q_adc_data;
	extern osMessageQId q_adcHandle;
	extern osMessageQId q_uiHandle;
	extern osMessageQId q_selHandle;
	extern osMessageQId q_dso_adcHandle;

	extern osSemaphoreId s_widgetsHandle;
	osEvent os_event;

	const TickType_t xFrequency = 10;
	TickType_t xLastWakeTime;

	for( int i = 0 ; i < 320 ; i++ )
	{
		buffer1[i] = 2048;
		buffer2[i] = 2048;
	}

	tDsoState state =
	{
		.pWidgets = widgets,
		.buffer = buffer1,
		.rect = { 0, 20, 320, 200 },
		.run = 0,
		.trigger_repeat = TRIGGER_REPEAT_AUTO,
		.trigger_mode = TRIGGER_MODE_AUTO,
		.cursor_a = 0,
		.cursor_b = 0,
		.cursor_selected = 0,
		.cursors_enabled = 0,
		.measurements_enabled = 0,
		.cursor_color = COLOR_YELLOW,
		.signal_color = COLOR_GREEN,

		.trigger_position = 160,
		.trigger_color = COLOR_GREEN,

		.ax = 1024,
		.bx = 0,
		.ay = (-200*1024)/4096,
		.by = 200*1024,
	};

	osDelay( 10 );
	osSemaphoreWait( s_widgetsHandle, osWaitForever );

	state.pWidgets[33].value = 0;
	state.pWidgets[34].value = 1;
	state.pWidgets[35].value = 2;
	state.pWidgets[36].value = 3;
	state.pWidgets[37].value = 4;
	state.pWidgets[72].value = 5;

	state.sample_freq = arr_table[ widgets[17].value ];
	state.trigger_level = (widgets[30].value&0xFFFF);
	state.trigger_mode = (widgets[1].value==0)?TRIGGER_MODE_AUTO:TRIGGER_MODE_UP;

	//draw_scope( state.rect, state.buffer, state.trigger_level, state.cursor_a, state.cursor_b );
	draw_scope( &state );
	osSemaphoreRelease( s_widgetsHandle );

	xLastWakeTime = xTaskGetTickCount();
	while( 1 )
	{
		os_event = osMessageGet( q_uiHandle, 0 );
		if( os_event.status == osEventMessage )
		{
			// ui callbacks
			osSemaphoreWait( s_widgetsHandle, osWaitForever );
			switch( os_event.value.v )
			{
				case 0: // run, stop
					// request first
					if( state.run == 0 && widgets[0].value == 1 )
					{
						q_adc_data.sample_freq = state.sample_freq;
						q_adc_data.trigger_level = state.trigger_level;
						q_adc_data.trigger_mode = state.trigger_mode;
						q_adc_data.buffer = (state.buffer==buffer1)?buffer2:buffer1;
						osMessagePut( q_dso_adcHandle, (uint32_t)&q_adc_data, osWaitForever );
						state.run = 1;
					}
					if( state.run == 1 && widgets[0].value == 0 )
					{
						state.run = 0;
					}
					break;
				case 1: // mode
					if( widgets[1].value == TRIGGER_REPEAT_AUTO )
					{
						state.trigger_repeat = TRIGGER_REPEAT_AUTO;
						state.trigger_mode = TRIGGER_MODE_AUTO;
					}
					else if( widgets[1].value == TRIGGER_REPEAT_NORMAL )
					{
						state.trigger_repeat = TRIGGER_REPEAT_NORMAL;
						state.trigger_mode = TRIGGER_MODE_UP;
					}
					else if( widgets[1].value == TRIGGER_REPEAT_SINGLE )
					{
						state.trigger_repeat = TRIGGER_REPEAT_SINGLE;
						state.trigger_mode = TRIGGER_MODE_UP;
					}
					break;
				case 5:
					state.measurements_enabled = widgets[5].value;
					if( state.measurements_enabled )
					{
						update_measurements( &state );
					}
				case 6:
					state.cursors_enabled = widgets[6].value;
					if( state.cursors_enabled )
					{
						update_cursors( &state );
					}
					break;
				case 17:
					state.sample_freq = arr_table[ widgets[17].value ];
					widgets[9].text = sample_freqs[ widgets[17].value ];
					widget_clear( &widgets[9], 0xF7BE );
					widget_draw( &widgets[9] );
					break;
				case 30:
					state.trigger_level = widgets[30].value&0xFFFF;
					draw_scope3( &state, 1 );
					break;
				case 45:
					if( state.cursors_enabled )
					{
						if( state.cursor_selected == 0 )
						{
							state.cursor_a = (widgets[45].value&0xFFFF)/16;
						}
						else
						{
							state.cursor_b = (widgets[45].value&0xFFFF)/16;
						}

						draw_scope3( &state, 2 );

						update_cursors( &state );
					}
					break;
				case 46:
					state.cursor_selected = widgets[46].value;
					if( state.cursor_selected == 0 )
					{
						state.pWidgets[45].value = state.cursor_a*16;
						widget_draw( &widgets[45] );
					}
					else
					{
						state.pWidgets[45].value = state.cursor_b*16;
						widget_draw( &widgets[45] );
					}
					break;
				default:
					break;
			}

			osSemaphoreRelease( s_widgetsHandle );

		}

		os_event = osMessageGet( q_selHandle, 0 );
		if( os_event.status == osEventMessage )
		{
			state.path = os_event.value.v;
			osSemaphoreWait( s_widgetsHandle, osWaitForever );
			state.pWidgets[8].text = signal_paths[state.path];
			widget_draw( &state.pWidgets[8] );
			osSemaphoreRelease( s_widgetsHandle );
		}

		os_event = osMessageGet( q_adcHandle, 0 );
		if( os_event.status == osEventMessage )
		{
			osSemaphoreWait( s_widgetsHandle, osWaitForever );

			// get data
			state.buffer = (state.buffer==buffer1)?buffer2:buffer1;

			// single
			if( state.trigger_repeat == TRIGGER_REPEAT_SINGLE )
			{
				state.run = 0;
				widgets[0].value = 0;
				widget_draw( &widgets[0] );
			}

			// request new data
			if( state.run == 1 )
			{
				q_adc_data.sample_freq = state.sample_freq;
				q_adc_data.trigger_level = state.trigger_level;
				q_adc_data.trigger_mode = state.trigger_mode;
				q_adc_data.buffer = (state.buffer==buffer1)?buffer2:buffer1;
				osMessagePut( q_dso_adcHandle, (uint32_t)&q_adc_data, osWaitForever );
			}

			// draw
			state.rect = get_scope_rect();
			//draw_scope( state.rect, state.buffer, state.trigger_level, state.cursor_a, state.cursor_b );
			draw_scope( &state );

			state.measurements_enabled = widgets[5].value;
			state.cursors_enabled = widgets[6].value;
			if( state.measurements_enabled )
			{
				update_measurements( &state );
			}
			if( state.cursors_enabled )
			{
				update_cursors( &state );
			}

			osSemaphoreRelease( s_widgetsHandle );
		}

		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		//osDelay( 20 );
	}
}

