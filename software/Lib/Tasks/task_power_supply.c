/*
 * task_power_supply.c
 *
 *  Created on: May 12, 2020
 *      Author: jose
 */

#include "task_power_supply.h"
#include "cmsis_os.h"
#include "main.h"
#include "adc.h"
#include "tim.h"

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


void task_psu( void const * argument )
{
	const TickType_t xFrequency = 10;
	TickType_t xLastWakeTime;
	//VMON	ADC2 IN6
	//VGEN	TIM4 CH4 2, 3600 = 10k

	int32_t control = 0;
	int32_t vo_mv = 0;
	int32_t r_mv = -8000;

	int32_t vcc_mv = 3300;
	int32_t r1_kohm = 1;
	int32_t r2_kohm = 10;
	int32_t value = 0;
	int32_t vadc_mv = 0;
	int32_t i_ua = 0;

	// htim4.Init.Prescaler = 2-1;
	// htim4.Init.Period = 360-1;
	HAL_TIM_PWM_Start( &htim4, TIM_CHANNEL_4 ); // VGEN

	xLastWakeTime = xTaskGetTickCount();
	while( 1 )
	{
		value = adc_convert( &hadc2, ADC_CHANNEL_6 );
		vadc_mv = (value*vcc_mv)/4096;
		i_ua = (vcc_mv - vadc_mv)/r1_kohm;
		vo_mv = vcc_mv - i_ua*(r1_kohm+r2_kohm);

		if( vo_mv > r_mv )
		{
			control += 1;
		}
		else
		{
			control -= 1;
		}

	    if( control > 3600*0.2 )
	    {
	    	control = 3600*0.2;
	    }
	    if( control < 0 )
	    {
	    	control = 0;
	    }

	    __HAL_TIM_SET_COMPARE( &htim4, TIM_CHANNEL_4, control );

		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}

