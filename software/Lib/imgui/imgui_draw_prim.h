/*
 * imgui_draw_prim.h
 *
 *  Created on: Apr 26, 2020
 *      Author: jose
 */

#ifndef IMGUI_DRAW_PRIM_H_
#define IMGUI_DRAW_PRIM_H_

#include "imgui.h"

void draw_pixel( int16_t x, int16_t y, tColor color );
void draw_rect( int16_t x, int16_t y, int16_t width, int16_t height, tColor color );

#endif /* IMGUI_DRAW_PRIM_H_ */
