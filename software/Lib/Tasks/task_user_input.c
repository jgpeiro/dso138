/*
 * task_user_input.c
 *
 *  Created on: May 1, 2020
 *      Author: jose
 */


#include "task_user_input.h"

#include "cmsis_os.h"
#include "main.h"
#include "adc.h"

#include "imgui.h"
#include "button.h"
#include "selector.h"

static tButton button_ok;
static tButton button_plus;
static tButton button_minus;
static tButton button_sel;

tSelector selector_sense1;
tSelector selector_sense2;
tSelector selector_coupling;

tWidgetEvent get_buttons_event( void )
{
    if( button_get_state( &button_plus )
     && button_get_state( &button_minus ) )
    {
    	return WIDGET_EVENT_NONE;
    }

    if( button_get_state( &button_sel )
     && ( button_get_state( &button_ok )
       || button_get_state( &button_plus )
	   || button_get_state( &button_minus ) ) )
    {
    	return WIDGET_EVENT_NONE;
    }

    if( button_get_on_press( &button_ok ) )
    {
        return WIDGET_EVENT_PRESS;
    }
    if( button_get_on_release( &button_ok ) )
    {
        return WIDGET_EVENT_RELEASE;
    }

	if( button_get_on_press( &button_sel ) )
	{
		return WIDGET_EVENT_FOCUS_OUT;
	}
	if( button_get_on_release( &button_sel ) )
	{
		return WIDGET_EVENT_FOCUS_IN;
	}

    if( button_get_state( &button_ok ) )
    {
        if( button_get_on_press( &button_plus ) )
        {
            return WIDGET_EVENT_INCREMENT_PRESSED;
        }
        if( button_get_state( &button_plus ) )
        {
            return WIDGET_EVENT_INCREMENT;
        }

        if( button_get_on_press( &button_minus ) )
        {
            return WIDGET_EVENT_DECREMENT_PRESSED;
        }
        if( button_get_state( &button_minus ) )
        {
            return WIDGET_EVENT_DECREMENT;
        }
    }
    else
    {
		if( button_get_on_press( &button_plus ) )
		{
			return WIDGET_EVENT_FOCUS_OUT;
		}

		if( button_get_on_release( &button_plus ) )
		{
			return WIDGET_EVENT_FOCUS_IN_PREV;
		}

		if( button_get_on_press( &button_minus ) )
		{
			return WIDGET_EVENT_FOCUS_OUT;
		}

		if( button_get_on_release( &button_minus ) )
		{
			return WIDGET_EVENT_FOCUS_IN_NEXT;
		}
    }

    return WIDGET_EVENT_NONE;
}


uint8_t get_selectors_event( void )
{
	if( selector_get_on_change( &selector_sense1 )
	 || selector_get_on_change( &selector_sense2 )
	 || selector_get_on_change( &selector_coupling ) )
	{
		return selector_get_state( &selector_sense1 )*1
			+ selector_get_state( &selector_sense2 )*3
			+ selector_get_state( &selector_coupling )*9;
	}
	return (uint8_t)-1;
}

void buttons_init( void )
{
	button_init( &button_ok, BTN1_GPIO_Port, BTN1_Pin, GPIO_PIN_RESET );
	button_init( &button_plus, BTN2_GPIO_Port, BTN2_Pin, GPIO_PIN_RESET );
	button_init( &button_minus, BTN3_GPIO_Port, BTN3_Pin, GPIO_PIN_RESET );
	button_init( &button_sel, BTN4_GPIO_Port, BTN4_Pin, GPIO_PIN_RESET );
}

void buttons_process( void )
{
    button_process( &button_ok );
    button_process( &button_plus );
    button_process( &button_minus );
    button_process( &button_sel );
}

void selectors_init( void )
{
	selector_init( &selector_sense1, &hadc2, ADC_CHANNEL_2 );
	selector_init( &selector_sense2, &hadc2, ADC_CHANNEL_1 );
	selector_init( &selector_coupling, &hadc2, ADC_CHANNEL_3 );
}

void selectors_process( void )
{
	selector_process( &selector_sense1 );
	selector_process( &selector_sense2 );
	selector_process( &selector_coupling );
}

void task_user_input( void const * argument )
{
	extern osMessageQId q_btnHandle;
	extern osMessageQId q_selHandle;

	tWidgetEvent event;
	uint8_t sel_event;

	const TickType_t xFrequency = 10;
	TickType_t xLastWakeTime;

	buttons_init();
	selectors_init();

	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		buttons_process();
		event = get_buttons_event();
		if( event != WIDGET_EVENT_NONE )
		{
			osMessagePut( q_btnHandle, event, osWaitForever );
		}

		selectors_process();
		sel_event = get_selectors_event();
		if( sel_event != (uint8_t)-1 )
		{
			osMessagePut( q_selHandle, sel_event, osWaitForever );
		}

		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}
