/*
 * imgui_process.c
 *
 *  Created on: Apr 26, 2020
 *      Author: jose
 */

#include "imgui_process.h"

void widget_process( tWidget *pThis, tWidgetEvent event )
{
    switch( pThis->type )
    {
		case WIDGET_TYPE_LABEL:
			break;
		case WIDGET_TYPE_PROGRESSBAR:
			break;
		case WIDGET_TYPE_STATUSBAR:
			break;
		case WIDGET_TYPE_WINDOW:
			break;

        case WIDGET_TYPE_BUTTON:
            widget_button_process( pThis, event );
            break;
        case WIDGET_TYPE_TOGGLE:
            widget_toggle_process( pThis, event );
            break;
        case WIDGET_TYPE_SLIDER:
            widget_slider_process( pThis, event );
            break;
        case WIDGET_TYPE_CHECKBOX:
        	widget_checkbox_process( pThis, event );
            break;
        case WIDGET_TYPE_COMBOBOX:
            widget_combobox_process( pThis, event );
            break;
        default:
            break;
    }
}

void widget_button_process( tWidget *pThis, tWidgetEvent event )
{
    pThis->value = 0;

    switch( pThis->state )
    {
        case WIDGET_STATE_NORMAL:
            if( event == WIDGET_EVENT_FOCUS_IN )
            {
                pThis->state = WIDGET_STATE_FOCUSED;
            }
            break;

        case WIDGET_STATE_FOCUSED:
            if( event == WIDGET_EVENT_PRESS )
            {
                pThis->state = WIDGET_STATE_PRESSED;
                pThis->value = 1;
            }
            if( event == WIDGET_EVENT_FOCUS_OUT )
            {
                pThis->state = WIDGET_STATE_NORMAL;
            }
            break;

        case WIDGET_STATE_PRESSED:
            if( event == WIDGET_EVENT_RELEASE )
            {
                pThis->state = WIDGET_STATE_FOCUSED;
            }
            if( event == WIDGET_EVENT_FOCUS_OUT )
            {
                pThis->state = WIDGET_STATE_NORMAL;
            }
            break;

        default:
            break;
    }

}

void widget_toggle_process( tWidget *pThis, tWidgetEvent event )
{
	switch( pThis->state )
    {
        case WIDGET_STATE_NORMAL:
            if( event == WIDGET_EVENT_FOCUS_IN )
            {
                pThis->state = WIDGET_STATE_FOCUSED;
            }
            break;

        case WIDGET_STATE_FOCUSED:
            if( event == WIDGET_EVENT_PRESS )
            {
                pThis->state = WIDGET_STATE_PRESSED;
                pThis->value = !pThis->value;
            }
            if( event == WIDGET_EVENT_FOCUS_OUT )
            {
                pThis->state = WIDGET_STATE_NORMAL;
            }
            break;

        case WIDGET_STATE_PRESSED:
            if( event == WIDGET_EVENT_RELEASE )
            {
                pThis->state = WIDGET_STATE_FOCUSED;
            }
            if( event == WIDGET_EVENT_FOCUS_OUT )
            {
                pThis->state = WIDGET_STATE_NORMAL;
            }
            break;

        default:
            break;
    }
}

void widget_slider_process( tWidget *pThis, tWidgetEvent event )
{
	int32_t a, p, v;

    switch( pThis->state )
    {
        case WIDGET_STATE_NORMAL:
            if( event == WIDGET_EVENT_FOCUS_IN )
            {
                pThis->state = WIDGET_STATE_FOCUSED;
            }
            break;

        case WIDGET_STATE_FOCUSED:
            if( event == WIDGET_EVENT_PRESS )
            {
            	a = 0;
            	v = pThis->value >> 16;
            	p = pThis->value & 0xFFFF ;

            	v = 0;

            	pThis->value = (v << 16) | p;

            	pThis->state = WIDGET_STATE_PRESSED;
            }
            if( event == WIDGET_EVENT_FOCUS_OUT )
            {
                pThis->state = WIDGET_STATE_NORMAL;
            }
            break;

        case WIDGET_STATE_PRESSED:
            if( event == WIDGET_EVENT_RELEASE )
            {
                pThis->state = WIDGET_STATE_FOCUSED;
            }
            if( event == WIDGET_EVENT_FOCUS_OUT )
            {
                pThis->state = WIDGET_STATE_NORMAL;
            }

            if( event == WIDGET_EVENT_INCREMENT )
            {
            	a = 4;
            	v = pThis->value >> 16;
            	p = pThis->value & 0xFFFF ;

            	v = ( v < 0 )? 0 : v;
            	v = ( v+a > 999 )? 999 : v+a;
            	p = ( p+v/16 > 4095 )? 4095 : p+v/16;

            	pThis->value = (v << 16) | p;

            	//pThis->value = (pThis->value==99)?99:pThis->value+1;
            }
            else if( event == WIDGET_EVENT_DECREMENT )
            {
            	a = -4;
            	v = pThis->value >> 16;
            	p = pThis->value & 0xFFFF ;

            	v = ( v > 0 )? 0 : v;
            	v = ( v+a < -999 )? -999 : v+a;
            	p = ( p+v/16 < 0 )? 0 : p+v/16;

            	pThis->value = (v << 16) | p;
            	//pThis->value = (pThis->value==0)?0:pThis->value-1;
            }
            else
            {
            	a = 0;
            	v = pThis->value >> 16;
            	p = pThis->value & 0xFFFF ;

            	v = 0;

            	pThis->value = (v << 16) | p;
            }

            break;

        default:
            break;
    }
}

void widget_checkbox_process( tWidget *pThis, tWidgetEvent event )
{
	widget_toggle_process( pThis, event );
}

/*
uint8_t get_items_count( char *text )
{
    uint8_t i;
    uint8_t cnt = 0;
    uint8_t sep = ';';

    for( i = 0 ; text[i] != '\0' ; i++ )
    {
        if(  text[i] == sep )
        {
            cnt += 1;
        }
    }
    return cnt + 1; // 1;2;3
}*/


uint8_t get_items_count( char *text )
{
    uint8_t cnt = 1;
    while( *text )
    {
        if( *text == ';' )
        {
            cnt++;
        }
        text++;
    }

    return cnt; // 1;2;3
}

uint8_t get_item_value( char *text, uint8_t cnt, uint8_t *pStart, uint8_t *pLen )
{
    uint8_t i = 0;
    uint8_t sep = ';';
    uint8_t cnt2 = 0;

    *pStart = 0;
    *pLen = 0;
    for( i = 0 ; text[i] != '\0' && cnt != cnt2 ; i++ )
    {
        if( text[i] == sep )
        {
            cnt2 += 1;
        }
    }

    if( cnt != cnt2 )
    {
        return 0;
    }

    *pStart = i;

    for(  ; text[i] != '\0' && cnt + 1 != cnt2 ; i++ ) // i = i
    {
        if( text[i] == sep )
        {
            cnt2 += 1;
        }
    }

    if( cnt + 1 != cnt2 )
    {
        *pLen = i - *pStart;
    }
    else
    {
        *pLen = i - *pStart - 1;
    }

    return 1;
}
/*
int16_t text_count( char *text, char pattern )
{
	int16_t i;
	int16_t count = 0;
	for( i = 0 ; text[i] != '\0' ; i++ )
	{
		if( text[i] == pattern )
		{
			count += 1;
		}
	}
	return count;
}

int16_t text_find_idx( char *text, char pattern, int16_t idx )
{
	int16_t i;
	int16_t count = 0;
	for( i = 0 ; text[i] != '\0' ; i++ )
	{
		if( text[i] == pattern )
		{
			if( count == idx )
			{
				return i;
			}
			count += 1;
		}
	}
	return -1;
}
*/
void widget_combobox_process( tWidget *pThis, tWidgetEvent event )
{
	int16_t value_max = get_items_count( pThis->text )-1;

    switch( pThis->state )
    {
        case WIDGET_STATE_NORMAL:
            if( event == WIDGET_EVENT_FOCUS_IN )
            {
                pThis->state = WIDGET_STATE_FOCUSED;
            }
            break;

        case WIDGET_STATE_FOCUSED:
            if( event == WIDGET_EVENT_PRESS )
            {
                pThis->state = WIDGET_STATE_PRESSED;
            }
            if( event == WIDGET_EVENT_FOCUS_OUT )
            {
                pThis->state = WIDGET_STATE_NORMAL;
            }
            break;

        case WIDGET_STATE_PRESSED:
            if( event == WIDGET_EVENT_RELEASE )
            {
                pThis->state = WIDGET_STATE_FOCUSED;
            }
            if( event == WIDGET_EVENT_FOCUS_OUT )
            {
                pThis->state = WIDGET_STATE_NORMAL;
            }

            if( event == WIDGET_EVENT_INCREMENT_PRESSED )
            {
            	pThis->value = (pThis->value==value_max)?value_max:pThis->value+1;
            }
            if( event == WIDGET_EVENT_DECREMENT_PRESSED )
            {
            	pThis->value = (pThis->value==0)?0:pThis->value-1;
            }
            break;

        default:
            break;
    }
}
