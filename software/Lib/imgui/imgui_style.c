/*
 * imgui_style.c
 *
 *  Created on: Apr 26, 2020
 *      Author: jose
 */

#include "imgui_style.h"


#define RGB2COLOR(r, g, b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3)))

const int16_t style[ WIDGET_PROPERTY_MAX*WIDGET_STATE_MAX ] =
{
		/*
		WIDGET_PROPERTY_BORDER = 0,
			WIDGET_PROPERTY_BASE,
				WIDGET_PROPERTY_TEXT,
		WIDGET_STATE_NORMAL = 0,
		WIDGET_STATE_FOCUSED,
		WIDGET_STATE_PRESSED,
		*/
		//RGB2COLOR( 131, 131, 131 ), RGB2COLOR( 201, 201, 201 ), RGB2COLOR( 104, 104, 104 ),
		//RGB2COLOR(   3, 146, 199 ), RGB2COLOR( 200/*151*/, 255/*232*/, 255 ), RGB2COLOR(  51, 139, 175 ),
		//RGB2COLOR(  91, 178, 217 ), RGB2COLOR( 199, 239, 254 ), RGB2COLOR( 108, 155, 188 ),

		RGB2COLOR( 131, 131, 131 ), RGB2COLOR( 201, 201, 201 ), RGB2COLOR( 104, 104, 104 ),
		RGB2COLOR(  91, 178, 217 ), RGB2COLOR( 199, 239, 254 ), RGB2COLOR( 108, 155, 188 ),
		//RGB2COLOR(   3, 146, 199 ), RGB2COLOR( 151, 232, 255 ), RGB2COLOR(  51, 139, 175 ),
		RGB2COLOR(   3, 146, 199 ), RGB2COLOR( 130, 200, 255 ), RGB2COLOR(  51, 139, 175 ),

		//RGB2COLOR( 0, 0, 255 ), RGB2COLOR( 0, 0, 128 ), RGB2COLOR( 0, 0, 255 ),
		//RGB2COLOR( 0, 255, 0 ), RGB2COLOR( 0, 128, 0 ), RGB2COLOR( 0, 255, 0 ),
		//RGB2COLOR( 255, 0, 0 ), RGB2COLOR( 128, 0, 0 ), RGB2COLOR( 255, 0, 0 ),
};

uint16_t get_style( tWidget *pWidget, tWidgetProperty propierty )
{
    return style[ pWidget->state*WIDGET_PROPERTY_MAX + propierty ];
}

uint16_t get_style_value( tWidget *pWidget, tWidgetProperty propierty )
{
	int32_t value = pWidget->value;
	//value = (value<0)?0:(value>WIDGET_STATE_PRESSED)?WIDGET_STATE_PRESSED:value;
	value = (value==0)?0:2;
	return style[ value*WIDGET_PROPERTY_MAX + propierty ];
}
