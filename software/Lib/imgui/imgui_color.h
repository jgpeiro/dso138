/*
 * imgui_colors.h
 *
 *  Created on: Apr 26, 2020
 *      Author: jose
 */

#ifndef IMGUI_IMGUI_COLORS_H_
#define IMGUI_IMGUI_COLORS_H_

#include "imgui.h"

#define COLOR_BLACK 	0x0000
#define COLOR_WHITE 	0xFFFF

#define COLOR_RED 		0xF800
#define COLOR_GREEN 	0x07E0
#define COLOR_BLUE		0x001F

#define COLOR_YELLOW 	0xFFE0
#define COLOR_CYAN 		0x07FF
#define COLOR_MAGENTA 	0xF81F

#define COLOR_GRAY 		0x7BEF
#define COLOR_LGRAY 	0xC618
#define COLOR_AQUA 		0x5D1C
#define COLOR_LIME 		0x87E0
#define COLOR_DCYAN 	0x03EF
#define COLOR_ORANGE 	0xFCA0
#define COLOR_PINK 		0xF97F
#define COLOR_BROWN 	0x8200
#define COLOR_VIOLET 	0x9199
#define COLOR_SILVER 	0xA510
#define COLOR_GOLD 		0xA508
#define COLOR_NAVY 		0x000F
#define COLOR_MAROON 	0x7800
#define COLOR_PURPLE	0x780F
#define COLOR_OLIVE 	0x7BE0

tColor rgb_to_color( tRgb rgb );
tRgb color_to_rgb( tColor color );

#endif /* IMGUI_IMGUI_COLORS_H_ */
