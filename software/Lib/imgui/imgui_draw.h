/*
 * imgui_draw.h
 *
 *  Created on: Apr 26, 2020
 *      Author: jose
 */

#ifndef IMGUI_DRAW_H_
#define IMGUI_DRAW_H_

#include "imgui.h"

void window_draw( tWidget *pWidgets, uint8_t len, uint8_t focus_window );
void window_clear( tWidget *pWidgets, uint8_t len, uint8_t focus_window, tColor color );

void widget_draw( tWidget *pThis );
void widget_clear( tWidget *pThis, tColor color );

void widget_button_draw( tWidget *pThis );
void widget_toggle_draw( tWidget *pThis );
void widget_slider_draw( tWidget *pThis );
void widget_checkbox_draw( tWidget *pThis );
void widget_combobox_draw( tWidget *pThis );

void widget_label_draw( tWidget *pThis );
void widget_progressbar_draw( tWidget *pThis );
void widget_statusbar_draw( tWidget *pThis );
void widget_window_draw( tWidget *pThis );


void draw_text_no_align( tRectangle rect, char *text, tColor color );
void draw_text( tRectangle rect, char *text, tColor color );

#endif /* IMGUI_DRAW_H_ */
