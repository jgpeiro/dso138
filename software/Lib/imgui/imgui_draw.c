
#include <string.h>  //srtncpy

#include "imgui_draw.h"
#include "imgui_draw_prim.h"

void widget_draw( tWidget *pThis )
{
    switch( pThis->type )
    {
		case WIDGET_TYPE_LABEL:
			widget_label_draw( pThis );
			break;
		case WIDGET_TYPE_PROGRESSBAR:
			widget_progressbar_draw( pThis );
			break;
		case WIDGET_TYPE_STATUSBAR:
			widget_statusbar_draw( pThis );
			break;
		case WIDGET_TYPE_WINDOW:
			widget_window_draw( pThis );
			break;

        case WIDGET_TYPE_BUTTON:
            widget_button_draw( pThis );
            break;
        case WIDGET_TYPE_TOGGLE:
            widget_toggle_draw( pThis );
            break;
        case WIDGET_TYPE_SLIDER:
            widget_slider_draw( pThis );
            break;
        case WIDGET_TYPE_CHECKBOX:
            widget_checkbox_draw( pThis );
            break;
        case WIDGET_TYPE_COMBOBOX:
            widget_combobox_draw( pThis );
            break;

        default:
            break;
    }
}

void widget_clear( tWidget *pThis, tColor color )
{
    draw_rect( pThis->rect.x, pThis->rect.y, pThis->rect.width, pThis->rect.height, color );
}


void window_draw( tWidget *pWidgets, uint8_t len, uint8_t focus_window )
{
    uint8_t i;
    for( i = 0 ; i < len ; i++ )
    {
        if( pWidgets[i].anchor == focus_window )
        {
            widget_draw( &pWidgets[i] );
        }
    }
}

void window_clear( tWidget *pWidgets, uint8_t len, uint8_t focus_window, tColor color )
{
	tRectangle rect;
	uint8_t i;
    for( i = 0 ; i < len ; i++ )
    {
    	if( pWidgets[i].type == WIDGET_TYPE_WINDOW
    	 && pWidgets[i].anchor == focus_window )
    	{
    		rect = pWidgets[i].rect;
    		draw_rect( rect.x, rect.y, rect.width, rect.height, color );
    	}
    }
}

uint8_t get_items_count( char *text );
uint8_t get_item_value( char *text, uint8_t cnt, uint8_t *pStart, uint8_t *pLen );

void draw_box( tRectangle rect, int8_t border_width, tColor color )
{
    draw_rect(
        rect.x,
        rect.y,
        rect.width,
        border_width,
        color
    );

    draw_rect(
        rect.x,
        rect.y + border_width,
        border_width,
        rect.height - 2*border_width,
        color
    );

    draw_rect(
        rect.x + rect.width - border_width,
        rect.y + border_width,
        border_width,
        rect.height - 2*border_width,
        color
    );

    draw_rect(
        rect.x,
        rect.y + rect.height - border_width,
        rect.width,
        border_width,
        color
    );
}


uint8_t get_icon( char *text )
{
	uint8_t icon = 0;
	uint8_t i = 0;

	// '#', [0..9]+, '#'
	if( text[i] == '#' )
	{
		i++;
		if( '0' <= text[i] && text[i] <= '9' )
		{
			icon = text[i]-'0';
			i++;
			while( '0' <= text[i] && text[i] <= '9' )
			{
				icon = icon*10 + text[i]-'0';
				i++;
			}
		}
		if( text[i] == '#' )
		{
			return icon;
		}
	}
	return 0;
}

void draw_text_no_align( tRectangle rect, char *text, tColor color )
{
    int16_t i;
    int16_t dwx = 0;
    tRectangle rect_text;
    tRectangle rect_icon;
    uint8_t icon;

    icon = get_icon( text );
    if( icon )
    {
    	text += 5; //#000#
    	rect_icon = get_icon_size( icon );
		rect_text = get_text_rect( pFont_def, text );

		rect_icon.x = rect.x;// + rect.width/2 - (rect_icon.width + rect_text.width)/2;
		rect_icon.y = rect.y;// + rect.height/2 - rect_icon.height/2;

		rect_text.x = rect_icon.x + rect_icon.width;
		rect_text.y = rect.y;// + rect.height/2 - rect_text.height/2;

    	draw_icon( rect_icon, icon, color );
    }
    else
    {
		//rect_text = get_text_rect( pFont_def, text );
		rect_text.x = rect.x;// + rect.width/2 - rect_text.width/2;
		rect_text.y = rect.y;// + rect.height/2 - rect_text.height/2;
    }

    for( i = 0 ; text[i] != '\0' ; i++ )
    {
        draw_char( pFont_def, rect_text.x+dwx, rect_text.y, text[i], color );
        dwx += get_char_rect( pFont_def, text[i] ).width;
    }
}
// Align support?
void draw_text( tRectangle rect, char *text, tColor color )
{
    int16_t i;
    int16_t dwx = 0;
    tRectangle rect_text;
    tRectangle rect_icon;
    uint8_t icon;

    icon = get_icon( text );
    if( icon )
    {
    	text += 5; //#000#
    	rect_icon = get_icon_size( icon );
		rect_text = get_text_rect( pFont_def, text );

		rect_icon.x = rect.x + rect.width/2 - (rect_icon.width + rect_text.width)/2;
		rect_icon.y = rect.y + rect.height/2 - rect_icon.height/2;

		rect_text.x = rect_icon.x + rect_icon.width;
		rect_text.y = rect.y + rect.height/2 - rect_text.height/2;

    	draw_icon( rect_icon, icon, color );
    }
    else
    {
		rect_text = get_text_rect( pFont_def, text );
		rect_text.x = rect.x + rect.width/2 - rect_text.width/2;
		rect_text.y = rect.y + rect.height/2 - rect_text.height/2;
    }

    for( i = 0 ; text[i] != '\0' ; i++ )
    {
        draw_char( pFont_def, rect_text.x+dwx, rect_text.y, text[i], color );
        dwx += get_char_rect( pFont_def, text[i] ).width;
    }
}

void widget_button_draw( tWidget *pThis )
{
    uint8_t border_width = 2;

    draw_box(
        pThis->rect,
        border_width,
        get_style( pThis, WIDGET_PROPERTY_BORDER )
    );

    draw_rect(
        pThis->rect.x + border_width,
        pThis->rect.y + border_width,
        pThis->rect.width - 2*border_width,
        pThis->rect.height- 2*border_width,
		//get_style_value( pThis, WIDGET_PROPERTY_BASE )
		get_style( pThis, WIDGET_PROPERTY_BASE )
    );

    draw_text(
        pThis->rect,
        pThis->text,
        get_style( pThis, WIDGET_PROPERTY_TEXT )
    );

}

#include <string.h>

void widget_toggle_draw( tWidget *pThis )
{
    uint8_t border_width = 2;

    tColor color_border;
    tColor color_base;
    tColor color_text;


	uint8_t result, start, len;
	char text[16];

	start = 0;
	len = 0;
	result = get_item_value( pThis->text, pThis->value, &start, &len );
	if( result )
	{
		strncpy( text, pThis->text + start, len );
		text[len] = '\0';
	}
	else
	{
		text[0] = 0;
	}

    if( pThis->value )
    {	// Todo: Add new function for get correct style
    	color_border=style[ WIDGET_STATE_PRESSED*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_BORDER ];
    	color_base = style[ WIDGET_STATE_PRESSED*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_BASE ];
    	color_text = style[ WIDGET_STATE_PRESSED*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_TEXT ];
    }
    else
    {
        color_border=get_style( pThis, WIDGET_PROPERTY_BORDER );
        color_base = get_style( pThis, WIDGET_PROPERTY_BASE);
        color_text = get_style( pThis, WIDGET_PROPERTY_TEXT );
    }

    /*
    color_border=get_style( pThis, WIDGET_PROPERTY_BORDER );
    color_base = get_style_value( pThis, WIDGET_PROPERTY_BASE);
    color_text = get_style( pThis, WIDGET_PROPERTY_TEXT );
     */
    draw_box(
		pThis->rect,
		border_width,
		color_border
	);

	draw_rect(
		pThis->rect.x + border_width,
		pThis->rect.y + border_width,
		pThis->rect.width - 2*border_width,
		pThis->rect.height- 2*border_width,
		color_base
	);

	draw_text(
		pThis->rect,
		text,
		color_text
	);
}

void widget_slider_draw( tWidget *pThis )
{
	uint8_t border_width = 2;
	int16_t width_base;
	int16_t split;
	tColor color1, color2;

	if( pThis->state == WIDGET_STATE_NORMAL )
	{
		color1 = style[ WIDGET_STATE_PRESSED*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_BASE ];
	}
	else
	{
		color1 = style[ WIDGET_STATE_FOCUSED*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_BASE ];
	}
	color2 = style[ WIDGET_STATE_NORMAL*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_BASE ];


	width_base = pThis->rect.width - 2*border_width;

	//int32_t a;
	//int32_t v;
	int32_t p;

	//a = 1;
	//v = pThis->value >> 16;
	p = pThis->value & 0xFFFF ;

	split = (width_base*p)/4095;
	split = (split<0)?0:split;
	split = (split>width_base)?width_base:split;

    draw_box(
        pThis->rect,
        border_width,
        get_style( pThis, WIDGET_PROPERTY_BORDER )
    );

    draw_rect(
        pThis->rect.x + border_width,
        pThis->rect.y + border_width,
		split,
        pThis->rect.height- 2*border_width,
		color1
    );

    draw_rect(
        pThis->rect.x + border_width + split,
        pThis->rect.y + border_width,
		width_base - split,
        pThis->rect.height- 2*border_width,
		color2
    );

    draw_text(
        pThis->rect,
        pThis->text,
        get_style( pThis, WIDGET_PROPERTY_TEXT )
    );
}


void widget_checkbox_draw( tWidget *pThis )
{
    uint8_t border_width = 2;
    tRectangle rect_text;

    tColor color_border;
    tColor color_base;
    tColor color_text;

    if( pThis->value )
    {	// Todo: Add new function for get correct style
    	color_border=style[ WIDGET_STATE_PRESSED*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_BORDER ];
    	color_base = style[ WIDGET_STATE_PRESSED*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_BASE ];
    	color_text = style[ WIDGET_STATE_PRESSED*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_TEXT ];
    }
    else
    {
        color_border=get_style( pThis, WIDGET_PROPERTY_BORDER );
        color_base = get_style( pThis, WIDGET_PROPERTY_BASE);
        color_text = get_style( pThis, WIDGET_PROPERTY_TEXT );
    }

    draw_box(
		pThis->rect,
		border_width,
		color_border
	);

	draw_rect(
		pThis->rect.x + border_width,
		pThis->rect.y + border_width,
		pThis->rect.width - 2*border_width,
		pThis->rect.height- 2*border_width,
		color_base
	);

	rect_text = get_text_rect( pFont_def, pThis->text );
	rect_text.x = pThis->rect.x + pThis->rect.width + 1;
	rect_text.y = pThis->rect.y;

	draw_text(
		rect_text,
		pThis->text,
		color_text
	);
}


void widget_combobox_draw( tWidget *pThis )
{
	uint8_t result, start, len;
	char text[16];

	start = 0;
	len = 0;
	result = get_item_value( pThis->text, pThis->value, &start, &len );
	if( result )
	{
		strncpy( text, pThis->text + start, len );
		text[len] = '\0';
	}
	else
	{
		text[0] = 0;
	}

    uint8_t border_width = 2;

    tColor color_border;
    tColor color_base;
    tColor color_text;

    if( pThis->value )
    {	// Todo: Add new function for get correct style
    	color_border=style[ WIDGET_STATE_PRESSED*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_BORDER ];
    	color_base = style[ WIDGET_STATE_PRESSED*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_BASE ];
    	color_text = style[ WIDGET_STATE_PRESSED*WIDGET_PROPERTY_MAX + WIDGET_PROPERTY_TEXT ];
    }
    else
    {
        color_border=get_style( pThis, WIDGET_PROPERTY_BORDER );
        color_base = get_style( pThis, WIDGET_PROPERTY_BASE);
        color_text = get_style( pThis, WIDGET_PROPERTY_TEXT );
    }

    draw_box(
		pThis->rect,
		border_width,
		color_border
	);

	draw_rect(
		pThis->rect.x + border_width,
		pThis->rect.y + border_width,
		pThis->rect.width - 2*border_width,
		pThis->rect.height- 2*border_width,
		color_base
	);

	draw_text(
		pThis->rect,
		text,
		color_text
	);
}

void widget_label_draw( tWidget *pThis )
{
	draw_text(
		pThis->rect,
		pThis->text,
		get_style( pThis, WIDGET_PROPERTY_TEXT )
	);
}

void widget_progressbar_draw( tWidget *pThis )
{
	widget_slider_draw( pThis);
}

void widget_statusbar_draw( tWidget *pThis )
{
	widget_button_draw( pThis );
}

void widget_window_draw( tWidget *pThis )
{
    uint8_t border_width = 2;

    draw_box(
        pThis->rect,
        border_width,
        get_style( pThis, WIDGET_PROPERTY_BORDER )
    );

    draw_rect(
        pThis->rect.x + border_width,
        pThis->rect.y + border_width,
        pThis->rect.width - 2*border_width,
        pThis->rect.height- 2*border_width,
		0xF7BE//get_style( pThis, WIDGET_PROPERTY_BASE )
    );

    tRectangle rect = pThis->rect;
    rect.height = 20;
    draw_box(
    	rect,
        border_width,
        get_style( pThis, WIDGET_PROPERTY_BORDER )
    );

    draw_rect(
        rect.x + border_width,
        rect.y + border_width,
        rect.width - 2*border_width,
        rect.height- 2*border_width,
        get_style( pThis, WIDGET_PROPERTY_BASE )
    );

    draw_text(
    	rect,
        pThis->text,
        get_style( pThis, WIDGET_PROPERTY_TEXT )
    );
}
