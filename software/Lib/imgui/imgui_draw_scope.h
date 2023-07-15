/*
 * imgui_draw_scope.h
 *
 *  Created on: May 3, 2020
 *      Author: jose
 */

#ifndef IMGUI_DRAW_SCOPE_H_
#define IMGUI_DRAW_SCOPE_H_

#include "imgui.h"
#include "task_dso.h"

void draw_grid( tRectangle rect, uint16_t color1, uint16_t color2 );
void draw_trigger( tDsoState *pState );
void draw_signal( tRectangle rect, int16_t *buffer, int32_t ax, int32_t bx, int32_t ay, int32_t by );
void draw_cursors( tDsoState *pState );
void draw_scope3( tDsoState *pState, int mode );
void draw_scope( tDsoState *pState );

#endif /* IMGUI_DRAW_SCOPE_H_ */
