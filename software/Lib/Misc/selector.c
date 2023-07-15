/*
 * selector.c
 *
 *  Created on: Apr 10, 2020
 *      Author: jgarcia
 */


#include "selector.h"
#include "cmsis_os.h"

#define SELECTOR_DEBOUNCE_COUNT_MAX	10
#define SELECTOR_VALUE_1			4096
#define SELECTOR_VALUE_2			1600
#define SELECTOR_VALUE_3			0
#define SELECTOR_VALUE_THRESHOLD	100

static uint16_t adc_convert( ADC_HandleTypeDef* hadc, uint32_t channel );

static uint16_t adc_convert( ADC_HandleTypeDef* hadc, uint32_t channel )
{
	extern osSemaphoreId s_adc2Handle;

	osSemaphoreWait( s_adc2Handle, osWaitForever );

    uint16_t value;
	ADC_ChannelConfTypeDef sConfig = { 0 };

	sConfig.Channel = channel;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	HAL_ADC_ConfigChannel( hadc, &sConfig );

	HAL_ADC_Start( hadc );
	HAL_ADC_PollForConversion( hadc, HAL_MAX_DELAY );
	value = HAL_ADC_GetValue( hadc );
	HAL_ADC_Stop( hadc );

	osSemaphoreRelease( s_adc2Handle );

	return value;
}

void selector_init( tSelector *pThis, ADC_HandleTypeDef* hadc, uint32_t channel )
{
	pThis->hadc = hadc;
	pThis->channel = channel;

	pThis->debounce_count_1 = 0;
	pThis->debounce_count_2 = 0;
	pThis->debounce_count_3 = 0;

	pThis->state_bck = 0;
	pThis->state = 0;

	pThis->on_change = 0;
}

void selector_reset( tSelector *pThis )
{
	pThis->debounce_count_1 = 0;
	pThis->debounce_count_2 = 0;
	pThis->debounce_count_3 = 0;

	pThis->state_bck = 0;
	pThis->state = 0;

	pThis->on_change = 0;
}

void selector_process( tSelector *pThis )
{
	uint16_t value;

	value = adc_convert( pThis->hadc, pThis->channel );

	if( SELECTOR_VALUE_1 - SELECTOR_VALUE_THRESHOLD <= value && value < SELECTOR_VALUE_1 + SELECTOR_VALUE_THRESHOLD )
	{
		if( pThis->debounce_count_1 < SELECTOR_DEBOUNCE_COUNT_MAX )
		{
			pThis->debounce_count_1 += 1;
		}
	}
	else
	{
		if( pThis->debounce_count_1 > -SELECTOR_DEBOUNCE_COUNT_MAX )
		{
			pThis->debounce_count_1 -= 1;
		}
	}

	if( SELECTOR_VALUE_2 - SELECTOR_VALUE_THRESHOLD <= value && value < SELECTOR_VALUE_2 + SELECTOR_VALUE_THRESHOLD )
	{
		if( pThis->debounce_count_2 < SELECTOR_DEBOUNCE_COUNT_MAX )
		{
			pThis->debounce_count_2 += 1;
		}
	}
	else
	{
		if( pThis->debounce_count_2 > -SELECTOR_DEBOUNCE_COUNT_MAX )
		{
			pThis->debounce_count_2 -= 1;
		}
	}

	if( SELECTOR_VALUE_3 - SELECTOR_VALUE_THRESHOLD <= value && value < SELECTOR_VALUE_3 + SELECTOR_VALUE_THRESHOLD )
	{
		if( pThis->debounce_count_3 < SELECTOR_DEBOUNCE_COUNT_MAX )
		{
			pThis->debounce_count_3 += 1;
		}
	}
	else
	{
		if( pThis->debounce_count_3 > -SELECTOR_DEBOUNCE_COUNT_MAX )
		{
			pThis->debounce_count_3 -= 1;
		}
	}

	pThis->state_bck = pThis->state;
	if( pThis->debounce_count_1 == SELECTOR_DEBOUNCE_COUNT_MAX && pThis->debounce_count_2 == -SELECTOR_DEBOUNCE_COUNT_MAX && pThis->debounce_count_3 == -SELECTOR_DEBOUNCE_COUNT_MAX )
	{
		pThis->state = 0;
	}
	else if( pThis->debounce_count_1 == -SELECTOR_DEBOUNCE_COUNT_MAX && pThis->debounce_count_2 == SELECTOR_DEBOUNCE_COUNT_MAX && pThis->debounce_count_3 == -SELECTOR_DEBOUNCE_COUNT_MAX )
	{
		pThis->state = 1;
	}
	else if( pThis->debounce_count_1 == -SELECTOR_DEBOUNCE_COUNT_MAX && pThis->debounce_count_2 == -SELECTOR_DEBOUNCE_COUNT_MAX && pThis->debounce_count_3 == SELECTOR_DEBOUNCE_COUNT_MAX )
	{
		pThis->state = 2;
	}

	if( pThis->state != pThis->state_bck )
	{
		pThis->on_change = 1;
	}
	else
	{
		pThis->on_change = 0;
	}
}

uint8_t selector_get_state( tSelector *pThis )
{
	return pThis->state;
}

uint8_t selector_get_on_change( tSelector *pThis )
{
	return pThis->on_change;
}
