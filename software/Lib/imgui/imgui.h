/*
 * imgui.h
 *
 *  Created on: Apr 26, 2020
 *      Author: jose
 */

#ifndef IMGUI_IMGUI_H_
#define IMGUI_IMGUI_H_

#include <stdint.h>

enum eWidgetType
{
	// Non interactive
	WIDGET_TYPE_LABEL = 0,
	WIDGET_TYPE_PROGRESSBAR,
	WIDGET_TYPE_STATUSBAR,
	WIDGET_TYPE_WINDOW,

	// Interactive
	WIDGET_TYPE_BUTTON,
	WIDGET_TYPE_TOGGLE,
	WIDGET_TYPE_SLIDER,
	WIDGET_TYPE_CHECKBOX,
	WIDGET_TYPE_COMBOBOX,

	WIDGET_TYPE_MAX,
};
typedef enum eWidgetType tWidgetType;

enum eWidgetState
{
    WIDGET_STATE_NORMAL = 0,
	WIDGET_STATE_FOCUSED,
	WIDGET_STATE_PRESSED,

	WIDGET_STATE_MAX,
};
typedef enum eWidgetState tWidgetState;

enum eWidgetEvent
{
	WIDGET_EVENT_NONE = 0,

	WIDGET_EVENT_FOCUS_IN,
	WIDGET_EVENT_FOCUS_IN_NEXT,
	WIDGET_EVENT_FOCUS_IN_PREV,
	WIDGET_EVENT_FOCUS_OUT,
	WIDGET_EVENT_PRESS,
	WIDGET_EVENT_RELEASE,
	WIDGET_EVENT_INCREMENT,
	WIDGET_EVENT_DECREMENT,
	WIDGET_EVENT_INCREMENT_PRESSED,
	WIDGET_EVENT_DECREMENT_PRESSED,

	WIDGET_EVENT_MAX,
};
typedef enum eWidgetEvent tWidgetEvent;


// shapes
struct sPoint
{
	int16_t x;
	int16_t y;
};
typedef struct sPoint tPoint;

struct sRectangle
{
	int16_t x;
	int16_t y;
	int16_t width;
	int16_t height;
};
typedef struct sRectangle tRectangle;

// Colors
struct sRgb
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};
typedef struct sRgb tRgb;

typedef uint16_t tColor;

// Fonts
struct sGlyph
{
    uint8_t dwidthx, dwidthy;
    int8_t bbxw, bbxh, bbxx, bbxy;
    const uint8_t *pBitmap;
};
typedef struct sGlyph tGlyph;

struct sFont
{
    char *pName;
    uint8_t start;
    uint8_t end;
    uint8_t ascent;
    uint8_t descent;
    int8_t bbxw, bbxh, bbxx, bbxy;
    const tGlyph* const *pGlyphs;
};
typedef struct sFont tFont;

// Widgets
struct sWidget
{
	tWidgetType type;
	tRectangle rect;
	tWidgetState state;
	uint8_t anchor;
	char *text;
	int32_t value;
};

typedef struct sWidget tWidget;

// imgui state
struct sImguiState
{
	tWidget *pWidgets;
	uint8_t len;
	tWidgetEvent event;

	uint8_t focus;
	uint8_t focus_bck;

	uint8_t focus_window;
	//uint8_t focus_window_bck;

	uint32_t value;
	uint32_t value_bck;

	uint8_t state;
	uint8_t state_bck;
};
typedef struct sImguiState tImguiState;

#include "imgui_color.h"
#include "imgui_draw_prim.h"
#include "imgui_draw.h"
//#include "imgui_draw_scope.h"
#include "imgui_focus.h"
#include "imgui_font.h"
#include "imgui_font_kyrou8.h"
#include "imgui_icon.h"
#include "imgui_layout.h"
#include "imgui_process.h"
#include "imgui_style.h"

#endif /* IMGUI_IMGUI_H_ */
