/*
 * imgui_draw_geom.c
 *
 *  Created on: May 1, 2020
 *      Author: jose
 */

#include "imgui_draw_geom.h"
#include "imgui_draw_prim.h"

void draw_circle_points( int16_t xc, int16_t yc, int16_t x, int16_t y, tColor color )
{
	int16_t x1 = xc + x;
	int16_t x2 = xc - x;
	int16_t y1 = yc + y;
	int16_t y2 = yc - y;

    draw_pixel( x1, y1, color );
    draw_pixel( x2, y1, color );
    draw_pixel( x1, y2, color );
    draw_pixel( x2, y2, color );
    draw_pixel( x1, y1, color );
    draw_pixel( x2, y1, color );
    draw_pixel( x1, y2, color );
    draw_pixel( x2, y2, color );
}

void draw_circle( int16_t xc, int16_t yc, int16_t r, tColor color )
{
	int16_t x = 0;
	int16_t y = r;
	int16_t d = 3 - 2 * r;

    draw_circle_points( xc, yc, x, y, color );

    while (y >= x)
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
        draw_circle_points( xc, yc, x, y, color );
    }
}
