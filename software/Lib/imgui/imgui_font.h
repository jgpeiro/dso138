/*
 * imgui_fonts.h
 *
 *  Created on: Apr 26, 2020
 *      Author: jose
 */

#ifndef IMGUI_IMGUI_FONTS_H_
#define IMGUI_IMGUI_FONTS_H_

#include "imgui.h"

extern const tFont *pFont_def;

void draw_char( const tFont *pFont, int16_t x0, int16_t y0, uint8_t c, tColor color );
tRectangle get_char_rect( const tFont *pFont, uint8_t c );
tRectangle get_text_rect( const tFont *pFont, char *pString );

#endif /* IMGUI_IMGUI_FONTS_H_ */
