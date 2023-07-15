/*
 * imgui_app.c
 *
 *  Created on: Apr 27, 2020
 *      Author: jose
 */


#include "imgui_layout.h"

tWidget widgets[ WIDGETS_MAX ] =
{
	{	.type = WIDGET_TYPE_TOGGLE,	.rect = {  0,  0, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "#149#;#150#"	},
	{	.type = WIDGET_TYPE_COMBOBOX,.rect= { 40,  0, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "Auto;Normal;Single"	},
	{	.type = WIDGET_TYPE_TOGGLE,	.rect = { 80,  0, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "#040#;#040#"	},
	{	.type = WIDGET_TYPE_TOGGLE,	.rect = {120,  0, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "#041#;#041#"	},
	{	.type = WIDGET_TYPE_TOGGLE,	.rect = {160,  0, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "#126#;#126#"	},
	{	.type = WIDGET_TYPE_TOGGLE,	.rect = {200,  0, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "#160#;#160#"	},
	{	.type = WIDGET_TYPE_TOGGLE,	.rect = {240,  0, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "#048#;#048#"	},
	{	.type = WIDGET_TYPE_TOGGLE,	.rect = {280,  0, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "#191#;#191#"	},
	//{	.type = WIDGET_TYPE_PLOT,	.rect = {  0, 20,320,200},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = ""	},
	//{	.type = WIDGET_TYPE_PLOT,	.rect = {  0, 20,320,120},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = ""	},
	//{	.type = WIDGET_TYPE_PLOT,	.rect = {  0, 20,240,200},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = ""	},
	{	.type = WIDGET_TYPE_STATUSBAR,.rect={  0,220, 80, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "10mV"	},
	{	.type = WIDGET_TYPE_STATUSBAR,.rect={ 80,220, 80, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "1mS"	},
	{	.type = WIDGET_TYPE_STATUSBAR,.rect={160,220, 80, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "Status1"	},
	{	.type = WIDGET_TYPE_STATUSBAR,.rect={240,220, 80, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 0,	.value = 0,	.text = "Status2"	},

	{	.type = WIDGET_TYPE_WINDOW,	.rect = {240,  0, 80,240},	.state = WIDGET_STATE_NORMAL,	.anchor = 1,	.value = 0,	.text = "#040#Horizontal"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {250, 25, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 1,	.value = 0,	.text = "Position"	},
	{	.type = WIDGET_TYPE_SLIDER,	.rect = {260, 40, 40, 40},	.state = WIDGET_STATE_NORMAL,	.anchor = 1,	.value = 0,	.text = "#120#"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {250,120, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 1,	.value = 0,	.text = "Dump"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {250,175, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 1,	.value = 0,	.text = "#040#Scale"	},
	{	.type = WIDGET_TYPE_COMBOBOX,.rect = {260,190, 40, 40},	.state = WIDGET_STATE_NORMAL,	.anchor = 1,	.value = 0,
		.text = "1 uS;2 uS;5 uS;"
				"10 uS;20 uS;50 uS;"
				"100 uS;200 uS;500 uS;"
				"1 mS;2 mS;5 mS;"
				"10 mS;20 mS;50 mS;"
				"100 mS;200 mS;500 mS"	},

	{	.type = WIDGET_TYPE_WINDOW,	.rect = {240,  0, 80,240},	.state = WIDGET_STATE_NORMAL,	.anchor = 2,	.value = 0,	.text = "#041#Vertical"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {250, 25, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 2,	.value = 0,	.text = "Position"	},
	{	.type = WIDGET_TYPE_SLIDER,	.rect = {260, 40, 40, 40},	.state = WIDGET_STATE_NORMAL,	.anchor = 2,	.value = 0,	.text = "#119#"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {250, 90, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 2,	.value = 0,	.text = "#127#"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {250,110, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 2,	.value = 0,	.text = "#123#"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {250,130, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 2,	.value = 0,	.text = "Ref"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {250,150, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 2,	.value = 0,	.text = "FFT"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {250,175, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 2,	.value = 0,	.text = "#041#Scale"	},
	{	.type = WIDGET_TYPE_COMBOBOX,	.rect = {260,190, 40, 40},	.state = WIDGET_STATE_NORMAL,	.anchor = 2,	.value = 0,
		.text = "1 mV;2 mV; 5 mV;"
				"10 mV;20 mV;50 mV;"
				"100 mV;200 mV;500 mV;"
				"1 V;2 V;5 V"},

	{	.type = WIDGET_TYPE_WINDOW,	.rect = {240,  0, 80,240},	.state = WIDGET_STATE_NORMAL,	.anchor = 3,	.value = 0,	.text = "#126#Trigger"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {250, 50, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 3,	.value = 0,	.text = "Menu"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {250, 95, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 3,	.value = 0,	.text = "Level"	},
	{	.type = WIDGET_TYPE_SLIDER,	.rect = {260,110, 40, 40},	.state = WIDGET_STATE_NORMAL,	.anchor = 3,	.value = 0,	.text = "#118#"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {250,200, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 3,	.value = 0,	.text = "Force"	},

	{	.type = WIDGET_TYPE_WINDOW,	.rect = {240,  0, 80,140},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "#160#Measure"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {240, 20, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "max"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {240, 40, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "min"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {240, 60, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "avg"	},

	{	.type = WIDGET_TYPE_LABEL,	.rect = {240,100, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "freq"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {240,120, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "duty"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {280, 20, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "0.0mV"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {280, 40, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "0.0mV"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {280, 60, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "0.0mV"	},

	{	.type = WIDGET_TYPE_LABEL,	.rect = {280,100, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "0.0mV"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {280,120, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "0.0mV"	},

	{	.type = WIDGET_TYPE_WINDOW,	.rect = {240,  0, 80,240},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = "#048#Cursors"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {250,140, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = "Position"	},
	{	.type = WIDGET_TYPE_SLIDER,	.rect = {260,165, 40, 40},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = "#76#"	},
	{	.type = WIDGET_TYPE_TOGGLE,	.rect = {250,210, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = "cursor a;cursor b"	},

	{	.type = WIDGET_TYPE_LABEL,	.rect = {240, 20, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = "x1"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {240, 40, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = "x2"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {240, 60, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = "dx"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {240, 80, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = "y1"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {240,100, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = "y2"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {240,120, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = "dy"	},

	{	.type = WIDGET_TYPE_LABEL,	.rect = {280, 20, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = ""	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {280, 40, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = ""	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {280, 60, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = ""	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {280, 80, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = ""	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {280,100, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = ""	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {280,120, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 5,	.value = 0,	.text = ""	},
/*
	{	.type = WIDGET_TYPE_WINDOW,	.rect = {  0,140,320,100},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "#191#Navigation"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = { 50,160, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Multi"	},
	{	.type = WIDGET_TYPE_SLIDER,	.rect = { 50,180, 40, 40},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "#076#"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {110,175, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "#052#"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {180,175, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "#042#"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {250,175, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Measure"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {110,205, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Left"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {180,205, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Set/Clear"	},
	{	.type = WIDGET_TYPE_BUTTON,	.rect = {250,205, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Right"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = { -5,160, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Cursors"	},
	{	.type = WIDGET_TYPE_CHECKBOX,.rect= { 10,175, 20, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = ""	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {-10,190, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Fine"	},
	{	.type = WIDGET_TYPE_CHECKBOX,.rect= { 10,205, 20, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = ""	},
*/

		{	.type = WIDGET_TYPE_WINDOW,	.rect = {  0,140,320,100},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "#191#Navigation"	},
		{	.type = WIDGET_TYPE_LABEL,	.rect = { 50,160, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Multi"	},
		{	.type = WIDGET_TYPE_SLIDER,	.rect = { 50,180, 40, 40},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "#076#"	},
		{	.type = WIDGET_TYPE_LABEL,	.rect = {110,175, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "#052#"	},
		{	.type = WIDGET_TYPE_LABEL,	.rect = {180,175, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "#042#"	},
		{	.type = WIDGET_TYPE_LABEL,	.rect = {250,175, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Measure"	},
		{	.type = WIDGET_TYPE_LABEL,	.rect = {110,205, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Left"	},
		{	.type = WIDGET_TYPE_LABEL,	.rect = {180,205, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Set/Clear"	},
		{	.type = WIDGET_TYPE_LABEL,	.rect = {250,205, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Right"	},
		{	.type = WIDGET_TYPE_LABEL,	.rect = { -5,160, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Cursors"	},
		{	.type = WIDGET_TYPE_CHECKBOX,.rect= { 10,175, 20, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = ""	},
		{	.type = WIDGET_TYPE_LABEL,	.rect = {-10,190, 60, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = "Fine"	},
		{	.type = WIDGET_TYPE_CHECKBOX,.rect= { 10,205, 20, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 6,	.value = 0,	.text = ""	},


	{	.type = WIDGET_TYPE_LABEL,	.rect = {240, 80, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "amp"	},
	{	.type = WIDGET_TYPE_LABEL,	.rect = {280, 80, 40, 20},	.state = WIDGET_STATE_NORMAL,	.anchor = 4,	.value = 0,	.text = "0.0mV"	},
};
