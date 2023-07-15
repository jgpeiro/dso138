/*
 * imgui_focus.c
 *
 *  Created on: Apr 30, 2020
 *      Author: jose
 */
#include "imgui_focus.h"

uint8_t widget_is_focusable( tWidget *pWidget, uint8_t active_window );

uint8_t widget_is_focusable( tWidget *pWidget, uint8_t active_window )
{
	if( pWidget->anchor == active_window )
	{
		if( pWidget->type == WIDGET_TYPE_BUTTON
	     || pWidget->type == WIDGET_TYPE_TOGGLE
	     || pWidget->type == WIDGET_TYPE_SLIDER
	     || pWidget->type == WIDGET_TYPE_CHECKBOX
	     || pWidget->type == WIDGET_TYPE_COMBOBOX )
		{
			return 1;
		}
	}
	return 0;
}

void next_widget( tImguiState *pState )
{
	tWidget *pWidgets = pState->pWidgets;
	uint8_t len = pState->len;
	uint8_t focus = pState->focus;

	uint8_t focus_window;

	focus_window = pWidgets[focus].anchor;

	focus = (focus==len-1)? 0 : focus+1;
    while( !widget_is_focusable( &pWidgets[focus], focus_window ) )
    {
        focus = (focus==len-1)? 0 : focus+1;
    }

    pState->focus = focus;
}

void next_widget_on_window( tImguiState *pState )
{
	tWidget *pWidgets = pState->pWidgets;
	uint8_t len = pState->len;
	uint8_t focus_window = pState->focus_window;

	uint8_t focus = 0;

	focus = (focus==len-1)? 0 : focus+1;
    while( !widget_is_focusable( &pWidgets[focus], focus_window ) )
    {
        focus = (focus==len-1)? 0 : focus+1;
    }

    pState->focus = focus;
}

void prev_widget( tImguiState *pState )
{
	tWidget *pWidgets = pState->pWidgets;
	uint8_t len = pState->len;
	uint8_t focus = pState->focus;

	uint8_t focus_window;

	focus_window = pWidgets[focus].anchor;

	focus = (focus==0)? len-1 : focus-1;
    while( !widget_is_focusable( &pWidgets[focus], focus_window ) )
    {
    	focus = (focus==0)? len-1 : focus-1;
    }

    pState->focus = focus;
}

void restore_window( tImguiState *pState )
{
	tWidget *widgets = pState->pWidgets;
	uint8_t focus = pState->focus;
	uint8_t focus_bck = pState->focus_bck;
	uint8_t focus_window = pState->focus_window;

	widget_process( &widgets[focus], WIDGET_EVENT_FOCUS_OUT );
	window_clear( widgets, WIDGETS_MAX, focus_window, 0x0000 );
	focus = focus_bck;
	widgets[focus].value = 0;
    focus_window = 0;
    widget_process( &widgets[focus], WIDGET_EVENT_FOCUS_IN );
    window_draw( widgets, WIDGETS_MAX, focus_window );

    pState->focus = focus;
    pState->focus_bck = focus_bck;
    pState->focus_window = focus_window;
}

void change_window( tImguiState *pState  )
{
	uint8_t i;
	const uint8_t focus_in_widget_table[ 6 ] = {2,3,4,5,6,7};
	const uint8_t focus_out_window_table[ 6 ] = {1,2,3,4,5,6};

	tWidget *widgets = pState->pWidgets;
	uint8_t focus = pState->focus;
	uint8_t focus_bck = pState->focus_bck;
	uint8_t focus_window = pState->focus_window;

    for( i = 0 ; i < 6 ; i++ )
    {
    	if( focus == focus_in_widget_table[i] )
    	{
    		widget_process( &widgets[focus], WIDGET_EVENT_FOCUS_OUT );
			focus_window = focus_out_window_table[i];
			focus_bck = focus;
            //focus = next_widget_on_window( widgets, WIDGETS_MAX, focus_window );
			pState->focus_window = focus_window;
			pState->focus_bck = focus_bck;
			next_widget_on_window( pState );
			focus = pState->focus;
			widget_process( &widgets[focus], WIDGET_EVENT_FOCUS_IN );
			window_draw( widgets, WIDGETS_MAX, focus_window );
			break;
    	}
    }

    pState->focus = focus;
    pState->focus_bck = focus_bck;
    pState->focus_window = focus_window;
}
