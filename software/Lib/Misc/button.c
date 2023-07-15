/*
 * button.c
 *
 *  Created on: Apr 10, 2020
 *      Author: jgarcia
 */

#include "button.h"

#define BUTTON_DEBOUNCE_COUNT_MAX	2

void button_init( tButton *pThis, GPIO_TypeDef *port, uint16_t pin, GPIO_PinState enable_state )
{
	pThis->port = port;
	pThis->pin = pin;

	pThis->debounce_count = 0;

	pThis->enable_state = enable_state;
	pThis->state_bck = 0;
	pThis->state = 0;

	pThis->on_press = 0;
	pThis->on_release = 0;
}

void button_reset( tButton *pThis )
{
	pThis->debounce_count = 0;

	pThis->state_bck = 0;
	pThis->state = 0;

	pThis->on_press = 0;
	pThis->on_release = 0;
}

void button_process( tButton *pThis )
{
	if( pThis->enable_state == HAL_GPIO_ReadPin( pThis->port, pThis->pin ) )
	{
		if( pThis->debounce_count < BUTTON_DEBOUNCE_COUNT_MAX )
		{
			pThis->debounce_count += 1;
		}
	}
	else
	{
		if( pThis->debounce_count > -BUTTON_DEBOUNCE_COUNT_MAX )
		{
			pThis->debounce_count -= 1;
		}
	}

	pThis->state_bck = pThis->state;
	if( pThis->debounce_count == BUTTON_DEBOUNCE_COUNT_MAX )
	{
		pThis->state = 1;
	}
	else if( pThis->debounce_count == -BUTTON_DEBOUNCE_COUNT_MAX )
	{
		pThis->state = 0;
	}


	if( pThis->state == 1 && pThis->state_bck == 0 )
	{
		pThis->on_press = 1;
	}
	else
	{
		pThis->on_press = 0;
	}

	if( pThis->state == 0 && pThis->state_bck == 1 )
	{
		pThis->on_release = 1;
	}
	else
	{
		pThis->on_release = 0;
	}
}

uint8_t button_get_state( tButton *pThis )
{
	return pThis->state;
}


uint8_t button_get_on_press( tButton *pThis )
{
	return pThis->on_press;
}

uint8_t button_get_on_release( tButton *pThis )
{
	return pThis->on_release;
}
