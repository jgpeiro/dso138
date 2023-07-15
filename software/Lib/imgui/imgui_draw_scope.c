/*
 * imgui_draw_scope.c
 *
 *  Created on: May 3, 2020
 *      Author: jose
 */

#include <stdlib.h> // itoa
#include "imgui_draw_scope.h"

#define	ICON_116_CENTER_X	7
#define ICON_116_CENTER_Y	6
#define	ICON_48_CENTER_X	7
#define ICON_48_CENTER_Y	7
#define	ICON_64_CENTER_X	7
#define ICON_64_CENTER_Y	7

#include "cmsis_os.h"

void draw_grid2( tRectangle rect, uint16_t color1, uint16_t color2 )
{

	static TickType_t xLastWakeTime = 0;
	TickType_t xCurrentTime;

	xCurrentTime = xTaskGetTickCount();
	if( xCurrentTime - xLastWakeTime < 10  )
	{
		return;
	}
	xLastWakeTime = xCurrentTime;

	static int16_t i0 = 1;
	static int16_t i1 = 1;
	static int16_t i2 = 0;
	static int16_t i3 = 0;

	int16_t i;
	int16_t x_divs = 16;
	int16_t y_divs = 10;//6;

	int16_t x;
	int16_t y;
	int16_t w;
	int16_t h;

	x = rect.x;
	y = rect.y;
	w = rect.width;
	h = rect.height;

	int w2 = 320;
	int h2 = 200;
	//for( i = 1 ; i < x_divs ; i++ )
	i = i0;
	if( i < x_divs )
	{
		if( x + (i*w2)/x_divs > x + w )
		//	break;
		{
			i = 1;
		}
		else
		{
			draw_rect( x + (i*w2)/x_divs, y, 1, h, ((i&0x01)==0)?color1:color2 );//(i==x_divs/2)?color1:color2 )
			i++;
		}
	}
	else
	{
		i = 1;
	}
	i0 = i;

	//for( i = 1 ; i < y_divs ; i++ )
	i = i1;
	if( i < y_divs )
	{
		if( y + (i*h2)/y_divs > y + h )
		//	break;
		{
			i = 1;
		}
		else
		{
			draw_rect( x, y + (i*h2)/y_divs, w, 1, ((i&0x01)==1)?color1:color2 );//(i==y_divs/2)?color1:color2 );
			i++;
		}
	}
	else
	{
		i = 1;
	}
	i1 = i;

	//for( i = 0 ; i < w ; i += 4 )
	i = i2;
	if( i < w )
	{

		for( int j = 0 ; j < 5 && i < w ; j++ )
		{
			draw_pixel( x + i, y + h2/2 - 1, color1 );
			draw_pixel( x + i, y + h2/2 + 1, color1 );
			i += 4;
		}
	}
	else
	{
		i = 0;
	}
	i2 = i;

	/*for( i = 0 ; i < h ; i += 4 )
	{
		draw_pixel( x + w2/2 - 1, y + i, color1 );
		draw_pixel( x + w2/2 + 1, y + i, color1 );
	}*/

	i = i3;
	if( i < h )
	{
		for( int j = 0 ; j < 6 && i < h ; j++ )
		{
			draw_pixel( x + w2/2 - 1, y + i, color1 );
			draw_pixel( x + w2/2 + 1, y + i, color1 );
			i += 4;
		}
	}
	else
	{
		i = 0;
	}
	i3 = i;
}

void draw_grid( tRectangle rect, uint16_t color1, uint16_t color2 )
{

	static TickType_t xLastWakeTime = 0;
	TickType_t xCurrentTime;

	xCurrentTime = xTaskGetTickCount();
	if( xCurrentTime - xLastWakeTime < 100  )
	{
		return;
	}
	xLastWakeTime = xCurrentTime;

	int16_t i;
	int16_t x_divs = 16;
	int16_t y_divs = 10;//6;

	int16_t x;
	int16_t y;
	int16_t w;
	int16_t h;

	x = rect.x;
	y = rect.y;
	w = rect.width;
	h = rect.height;

	int w2 = 320;
	int h2 = 200;
	for( i = 1 ; i < x_divs ; i++ )
	{
		if( x + (i*w2)/x_divs > x + w )
			break;
		draw_rect( x + (i*w2)/x_divs, y, 1, h, ((i&0x01)==0)?color1:color2 );//(i==x_divs/2)?color1:color2 )
	}

	for( i = 1 ; i < y_divs ; i++ )
	{
		if( y + (i*h2)/y_divs > y + h )
			break;
		draw_rect( x, y + (i*h2)/y_divs, w, 1, ((i&0x01)==1)?color1:color2 );//(i==y_divs/2)?color1:color2 );
	}

	for( i = 0 ; i < w ; i += 4 )
	{
		draw_pixel( x + i, y + h2/2 - 1, color1 );
		draw_pixel( x + i, y + h2/2 + 1, color1 );
	}

	for( i = 0 ; i < h ; i += 4 )
	{
		draw_pixel( x + w2/2 - 1, y + i, color1 );
		draw_pixel( x + w2/2 + 1, y + i, color1 );
	}
}


void draw_trigger( tDsoState *pState )
{
	//rect, 160, trigger_level, 1024, 0, (-200*1024)/4096, 200*1024, COLOR_GREEN

	tRectangle rect = pState->rect;
	int16_t position = pState->trigger_position;
	int16_t level = pState->trigger_level;
	int32_t ax = pState->ax;
	int32_t bx = pState->bx;
	int32_t ay = pState->ay;
	int32_t by = pState->by;
	uint16_t color = pState->trigger_color;

	static int16_t x_bck = 0;
	static int16_t y_bck = 0;
	tRectangle rect_icon = {  0,  0, ICON_SIZE, ICON_SIZE };
	uint8_t icon = 64;

	if( x_bck != 0 && y_bck != 0 )
	{
		rect_icon.x = x_bck;
		rect_icon.y = y_bck;
		draw_icon( rect_icon, icon, COLOR_BLACK );
	}

	rect_icon.x = rect.x + (position*ax)/1024 + bx/1024 - ICON_64_CENTER_X;
	rect_icon.y = rect.y + (level*ay)/1024 + by/1024 - ICON_64_CENTER_Y;
	draw_icon( rect_icon, icon, color );
	x_bck = rect_icon.x;
	y_bck = rect_icon.y;
}

#define ICON_115_CENTER_X	6
#define ICON_115_CENTER_Y	8
void draw_signal( tRectangle rect, int16_t *buffer, int32_t ax, int32_t bx, int32_t ay, int32_t by )
{
	static int16_t buffer_bck[320] = {0};
	static int16_t y_bck = 0;
	uint8_t icon = 115;
	tRectangle rect_icon = {  0,  0, ICON_SIZE, ICON_SIZE };

	/*rect_icon.x = rect.x - ICON_115_CENTER_X;
	rect_icon.y = rect.y + (y_bck*ay)/1024 + by/1024 - ICON_64_CENTER_Y;
	draw_icon( rect_icon, icon, COLOR_BLACK );

	rect_icon.x = rect.x - ICON_115_CENTER_X;
	rect_icon.y = rect.y + (2048*ay)/1024 + by/1024 - ICON_64_CENTER_Y;
	draw_icon( rect_icon, icon, COLOR_GREEN );
	y_bck = 2048;*/

	int i, /*x,*/ y;
	for( i = 0 ; i < rect.width ; i++ )
	{
		//x = (i*ax)/1024 + bx/1024;
		//x = (x<0)?0:(x>rect.width-1)?rect.width-1:y;
		y = (buffer[i]*ay)/1024 + by/1024;
		y = (y<0)?0:((y>rect.height-1)?rect.height-1:y);

		draw_pixel( rect.x + i, rect.y + buffer_bck[i], COLOR_BLACK );
		draw_pixel( rect.x + i, rect.y + y, COLOR_GREEN );
		buffer_bck[i] = y;
	}
}

void draw_signal_slice( tRectangle rect, int16_t *buffer, int32_t ax, int32_t bx, int32_t ay, int32_t by, int16_t x0, int16_t x1 )
{
	static int16_t buffer_bck[320] = {0};
	int i, /*x,*/ y;
	for( i = x0 ; i < rect.width && i < x1; i++ )
	{
		//x = (i*ax)/1024 + bx/1024;
		//x = (x<0)?0:(x>rect.width-1)?rect.width-1:y;
		y = (buffer[i]*ay)/1024 + by/1024;
		y = (y<0)?0:((y>rect.height-1)?rect.height-1:y);

		draw_pixel( rect.x + i, rect.y + buffer_bck[i], COLOR_BLACK );
		draw_pixel( rect.x + i, rect.y + y, COLOR_GREEN );
		buffer_bck[i] = y;
	}
}

void draw_cursor( tRectangle rect, tPoint point_icon, tPoint point_icon_bck, uint16_t color )
{
	uint8_t icon_top = 116;
	uint8_t icon_signal = 48;
	tRectangle rect_icon = {  0,  0, ICON_SIZE, ICON_SIZE };

	rect_icon.x = rect.x + point_icon_bck.x - ICON_116_CENTER_X;
	rect_icon.y = rect.y - ICON_116_CENTER_Y;
	draw_icon( rect_icon, icon_top, COLOR_BLACK );

	rect_icon.x = rect.x + point_icon.x - ICON_116_CENTER_X;
	rect_icon.y = rect.y - ICON_116_CENTER_Y;
	draw_icon( rect_icon, icon_top, color );

	rect_icon.x = rect.x + point_icon_bck.x - ICON_48_CENTER_X;
	rect_icon.y = rect.y + point_icon_bck.y - ICON_48_CENTER_Y;
	draw_icon( rect_icon, icon_signal, COLOR_BLACK );

	rect_icon.x = rect.x + point_icon.x - ICON_48_CENTER_X;
	rect_icon.y = rect.y + point_icon.y - ICON_48_CENTER_Y;
	draw_icon( rect_icon, icon_signal, color );

	return;
}

#define TEXT_WIDTH 40
#define TEXT_HEIGHT 20
void draw_cursor_label( tRectangle rect, tPoint point_icon, tPoint point_icon_bck, int16_t c, int16_t c_bck, int16_t y, int16_t y_bck, uint16_t color )
{
	char text1[16] = "x = 0000";
	char text1_bck[16] = "x = 0000";
	char text2[16] = "y = 0000";
	char text2_bck[16] = "y = 0000";
	tRectangle rect_text = {  0,  0, ICON_SIZE, ICON_SIZE };

	itoa( c, &text1[4], 10 );
	itoa( c_bck, &text1_bck[4], 10 );

	rect_text.x = rect.x + point_icon_bck.x - ICON_116_CENTER_X + ICON_SIZE;// + TEXT_WIDTH/2;
	rect_text.y = rect.y - ICON_116_CENTER_Y + 3;// + TEXT_HEIGHT/2;
	draw_text_no_align( rect_text, text1_bck, COLOR_BLACK );

	rect_text.x = rect.x + point_icon.x - ICON_116_CENTER_X + ICON_SIZE;// + TEXT_WIDTH/2;
	rect_text.y = rect.y - ICON_116_CENTER_Y + 3;// + TEXT_HEIGHT/2;
	draw_text_no_align( rect_text, text1, color );

	//text[0] = 'y';
	itoa( y, &text2[4], 10 );
	itoa( y_bck, &text2_bck[4], 10 );

	rect_text.x = rect.x + point_icon_bck.x - ICON_116_CENTER_X + ICON_SIZE;// + TEXT_WIDTH/2;
	rect_text.y = rect.y - ICON_116_CENTER_Y + 3 + TEXT_HEIGHT/2;
	draw_text_no_align( rect_text, text2_bck, COLOR_BLACK );

	rect_text.x = rect.x + point_icon.x - ICON_116_CENTER_X + ICON_SIZE;// + TEXT_WIDTH/2;
	rect_text.y = rect.y - ICON_116_CENTER_Y + 3 + TEXT_HEIGHT/2;
	draw_text_no_align( rect_text, text2, color );
}

void draw_cursors( tDsoState *pState )
{
	tRectangle rect = pState->rect;
	int16_t *buffer = pState->buffer;
	int16_t c1 = pState->cursor_a;
	int16_t c2 = pState->cursor_b;
	int32_t ax = pState->ax;
	int32_t bx = pState->bx;
	int32_t ay = pState->ay;
	int32_t by = pState->by;
	uint16_t color = pState->cursor_color;

	tPoint point_icon1;
	tPoint point_icon2;
	static tPoint point_icon1_bck = {0};
	static tPoint point_icon2_bck = {0};
	//static int16_t c1b_bck = 0;
	//static int16_t c2b_bck = 0;
	//static int16_t c1_bck = 0;
	//static int16_t c2_bck = 0;

	point_icon1.x = (c1*ax)/1024 + bx/1024;
	point_icon1.y = (buffer[c1]*ay)/1024 + by/1024;
	if( point_icon1_bck.x == 0 && point_icon1_bck.y == 0 )
	{
		point_icon1_bck = point_icon1;
		//c1b_bck = buffer[c1];
	}
	draw_cursor( rect, point_icon1, point_icon1_bck, color );
	//draw_cursor_label( rect, point_icon1, point_icon1_bck, c1, c1_bck, buffer[c1], c1b_bck, color );
	point_icon1_bck = point_icon1;
	//c1b_bck = buffer[c1];
	//c1_bck = c1;


	point_icon2.x = (c2*ax)/1024 + bx/1024;
	point_icon2.y = (buffer[c2]*ay)/1024 + by/1024;
	if( point_icon2_bck.x == 0 && point_icon2_bck.y == 0 )
	{
		point_icon2_bck = point_icon2;
		//c2b_bck = buffer[c2];
	}
	draw_cursor( rect, point_icon2, point_icon2_bck, color );
	//draw_cursor_label( rect, point_icon2, point_icon2_bck, c2, c2_bck, buffer[c2], c2b_bck, color );
	point_icon2_bck = point_icon2;
	//c2b_bck = buffer[c2];
	//c2_bck = c2;
}
/*
void draw_scope2( tRectangle rect, int16_t *buffer, int16_t trigger_level, int16_t cursor_a, int16_t cursor_b )
{
	draw_trigger( rect, 160, trigger_level, 1024, 0, (-200*1024)/4096, 200*1024, COLOR_GREEN );
	draw_cursors( rect, buffer, cursor_a, cursor_b, 1024, 0, (-200*1024)/4096, 200*1024, COLOR_YELLOW );
}
*/
void draw_scope3( tDsoState *pState, int mode )
{
	tRectangle rect = pState->rect;
	int16_t *buffer = pState->buffer;
	int16_t trigger_level = pState->trigger_level;
	int16_t cursor_a = pState->cursor_a;
	int16_t cursor_b = pState->cursor_b;

	if( mode == 1 )
	{
		draw_trigger( pState );
		//draw_signal_slice( rect, buffer, 1024, 0, (-200*1024)/4096, 200*1024 );
	}

	if( mode == 2)
	{
		if( pState->run == 0 )
		{
			int ax = 1024;
			int bx = 0;
			int ay = (-200*1024)/4096;
			int by = 200*1024;
			int point_icon1_x = (cursor_a*ax)/1024 + bx/1024;
			int rect_icon1_x = rect.x + point_icon1_x - ICON_116_CENTER_X;
			draw_signal_slice( rect, buffer, 1024, 0, (-200*1024)/4096, 200*1024, rect_icon1_x-20, rect_icon1_x+20 );
			int point_icon2_x = (cursor_b*ax)/1024 + bx/1024;
			int rect_icon2_x = rect.x + point_icon2_x - ICON_116_CENTER_X;
			draw_signal_slice( rect, buffer, 1024, 0, (-200*1024)/4096, 200*1024, rect_icon2_x-20, rect_icon2_x+20 );
		}

		draw_cursors( pState );
	}
}

void draw_scope( tDsoState *pState )
{
	static TickType_t xLastWakeTime = 0;
	TickType_t xCurrentTime;

	xCurrentTime = xTaskGetTickCount();
	if( xCurrentTime - xLastWakeTime < 10  )
	{
		return;
	}
	xLastWakeTime = xCurrentTime;

	tRectangle rect = pState->rect;
	int16_t *buffer = pState->buffer;
	int16_t trigger_level = pState->trigger_level;
	int16_t cursor_a = pState->cursor_a;
	int16_t cursor_b = pState->cursor_b;

	static uint8_t init = 0;
	if( init == 0 )
	{
		for( uint8_t i = 0 ; i < 16 ; i++ )
		{
			draw_grid2( rect, COLOR_LGRAY, COLOR_GRAY );
			osDelay(10);
		}
		init = 1;
	}
	draw_grid2( rect, COLOR_LGRAY, COLOR_GRAY );
	draw_signal( rect, buffer, 1024, 0, (-200*1024)/4096, 200*1024 );
	draw_trigger( pState );
	draw_cursors( pState );
}
