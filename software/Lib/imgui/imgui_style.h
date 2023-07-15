/*
 * imgui_style.h
 *
 *  Created on: Apr 26, 2020
 *      Author: jose
 */

#ifndef IMGUI_IMGUI_STYLE_H_
#define IMGUI_IMGUI_STYLE_H_

#include "imgui.h"

enum eWidgetProperty
{
	WIDGET_PROPERTY_BORDER = 0,
	WIDGET_PROPERTY_BASE,
	WIDGET_PROPERTY_TEXT,

	WIDGET_PROPERTY_MAX,
};
typedef enum eWidgetProperty tWidgetProperty;

extern const int16_t style[ WIDGET_PROPERTY_MAX * WIDGET_STATE_MAX ];

uint16_t get_style( tWidget *pWidget, tWidgetProperty propierty );

#endif /* IMGUI_IMGUI_STYLE_H_ */
