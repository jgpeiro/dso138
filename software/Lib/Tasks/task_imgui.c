
#include <stdint.h>

#include "task_imgui.h"
#include "task_user_input.h"
#include "imgui.h"

#include "cmsis_os.h"
#include "task_adc.h"

#include "ili9341.h"

tILI9341 ili9341 =
{
	.nRST_port= LCD_nRST_GPIO_Port,
	.nCS_port = LCD_nCS_GPIO_Port,
	.nWR_port = LCD_nWR_GPIO_Port,
	.nRD_port = LCD_nRD_GPIO_Port,
	.DnC_port = LCD_DnC_GPIO_Port,
	.DB07_port= LCD_DB0_GPIO_Port,

	.nRST_pin= LCD_nRST_Pin,
	.nCS_pin = LCD_nCS_Pin,
	.nWR_pin = LCD_nWR_Pin,
	.nRD_pin = LCD_nRD_Pin,
	.DnC_pin = LCD_DnC_Pin,
};

void process_focus( tImguiState *pState )
{
	if( pState->event == WIDGET_EVENT_FOCUS_IN
	 && pState->focus_window != 0 )
	{
		restore_window( pState );
		extern osMessageQId q_uiHandle;
		osMessagePut( q_uiHandle, pState->focus, osWaitForever );
	}
	if( pState->event == WIDGET_EVENT_FOCUS_IN_NEXT )
	{
		next_widget( pState );
		pState->event = WIDGET_EVENT_FOCUS_IN;
	}
	if( pState->event == WIDGET_EVENT_FOCUS_IN_PREV )
	{
		prev_widget( pState );
		pState->event = WIDGET_EVENT_FOCUS_IN;
	}
}

void process_widgets( tImguiState *pState )
{
	pState->state_bck = pState->pWidgets[pState->focus].state;
    pState->value_bck = pState->pWidgets[pState->focus].value;

    widget_process( &pState->pWidgets[pState->focus], pState->event );

    pState->state = pState->pWidgets[pState->focus].state;
    pState->value = pState->pWidgets[pState->focus].value;
}

void process_draw( tImguiState *pState )
{
    if( pState->state_bck != pState->state )
    {
        widget_draw( &pState->pWidgets[pState->focus] );
    }

    if( pState->pWidgets[pState->focus].type == WIDGET_TYPE_SLIDER
     && ( pState->event == WIDGET_EVENT_INCREMENT || pState->event == WIDGET_EVENT_DECREMENT ) )
    {
    	widget_draw( &pState->pWidgets[pState->focus] );
    }

    if( pState->pWidgets[pState->focus].type == WIDGET_TYPE_COMBOBOX
    	&& ( pState->event == WIDGET_EVENT_INCREMENT_PRESSED || pState->event == WIDGET_EVENT_DECREMENT_PRESSED ) )
    {
    	widget_draw( &pState->pWidgets[pState->focus] );
    }
}

uint8_t process_callbacks( tImguiState *pState )
{
	if( pState->value_bck != pState->value )
	{
		if( 2 <= pState->focus && pState->focus <= 7 ) // change window
		{
			extern osMessageQId q_uiHandle;
			osMessagePut( q_uiHandle, pState->focus, osWaitForever );
			if( pState->pWidgets[pState->focus].value == 1 ) // on_release
			{
				change_window( pState );
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

uint8_t process_btn_msg( tImguiState *pState )
{
	process_focus( pState );
	process_widgets( pState );
	process_draw( pState );
	return process_callbacks( pState );
}

void widgets_init( tImguiState *pState )
{
	pState->pWidgets[0].value = 0;			// stop
	pState->pWidgets[1].value = 0;			// auto
	pState->pWidgets[17].value = 1;			// 6 uS
	pState->pWidgets[30].value = 2048; 		// trigger value

    widget_process( &pState->pWidgets[pState->focus], WIDGET_EVENT_FOCUS_IN );
    window_draw( pState->pWidgets, pState->len, pState->focus_window );
}

void task_imgui( void const * argument )
{
	extern osMessageQId q_btnHandle;
	extern osSemaphoreId s_widgetsHandle;
	extern osMessageQId q_uiHandle;
	osEvent os_event;

    tImguiState state =
    {
    	.pWidgets = widgets,
    	.len = WIDGETS_MAX,
		.focus = 0,
		.focus_bck = 0,
		.focus_window = 0,
    };

    osSemaphoreRelease( s_widgetsHandle );
    while( 0 != osSemaphoreWait( s_widgetsHandle, 0 )  );
    ili9341_init( &ili9341 );
    widgets_init( &state );
    osSemaphoreRelease( s_widgetsHandle );

    while( 1 )
    {
    	os_event = osMessageGet( q_btnHandle, osWaitForever );
		if( os_event.status == osEventMessage )
		{
			state.event = (tWidgetEvent)os_event.value.v;

			osSemaphoreWait( s_widgetsHandle, osWaitForever  );
			if( process_btn_msg( &state ) )
			{
				osMessagePut( q_uiHandle, state.focus, osWaitForever );
			}
	        osSemaphoreRelease( s_widgetsHandle );
		}
    }

}
