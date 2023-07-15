#include "imgui_draw_prim.h"

#include "ili9341.h"

extern tILI9341 ili9341;

void draw_pixel( int16_t x, int16_t y, tColor color )
{
	ili9341_draw_pixel_fast( &ili9341, x, y, color );
}

void draw_rect( int16_t x, int16_t y, int16_t width, int16_t height, tColor color )
{
	ili9341_draw_rect_fast( &ili9341, x, y, width, height, color );
}
