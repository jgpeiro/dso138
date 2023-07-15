/*
 * imgui_focus.h
 *
 *  Created on: Apr 30, 2020
 *      Author: jose
 */

#ifndef IMGUI_IMGUI_FOCUS_H_
#define IMGUI_IMGUI_FOCUS_H_

#include "imgui.h"

void next_widget( tImguiState *pState );
void next_widget_on_window( tImguiState *pState );
void prev_widget( tImguiState *pState );

void restore_window( tImguiState *pState );
void change_window( tImguiState *pState );

#endif /* IMGUI_IMGUI_FOCUS_H_ */
