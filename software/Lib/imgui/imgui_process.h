/*
 * imgui_process.h
 *
 *  Created on: Apr 26, 2020
 *      Author: jose
 */

#include "imgui.h"

void widget_process( tWidget *pThis, tWidgetEvent event );

void widget_button_process( tWidget *pThis, tWidgetEvent event );
void widget_toggle_process( tWidget *pThis, tWidgetEvent event );
void widget_slider_process( tWidget *pThis, tWidgetEvent event );
void widget_checkbox_process( tWidget *pThis, tWidgetEvent event );
void widget_combobox_process( tWidget *pThis, tWidgetEvent event );
