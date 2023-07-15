
#include "task_adc.h"
#include "cmsis_os.h"
#include <string.h>

#include "main.h"

static int16_t buffer_0[2][160];
static int16_t buffer_1[4][160];

static int16_t trigger_level;
static tTriggerMode trigger_mode;
static int16_t trigger_time;

static uint8_t fsm_state;

void conversion_process( uint8_t is_cmplt )
{
	static uint8_t counter = 0;
	uint8_t i;
	int16_t *pSrc = NULL;
	int16_t *pDst = NULL;

	uint8_t counter_bck = counter;

	if( 1 <= fsm_state && fsm_state < 7 )
	{
		pSrc = buffer_0[ is_cmplt ];
		pDst = buffer_1[ counter&0x03 ];
		memcpy( pDst, pSrc, sizeof(buffer_0[0]) );
		counter++;
	}

	switch( fsm_state )
	{
		case 0:
			break;
		case 1:
			fsm_state = 3;
			break;
		case 2:
			fsm_state = 3;
			break;
		case 3:
			if( trigger_mode == TRIGGER_MODE_AUTO || trigger_mode == TRIGGER_MODE_UP )
			{
				for( i = 0 ; i < 160 ; i++ )
				{
					if( *pDst < trigger_level )
					{
						fsm_state = 4;
						pDst++;
						for( i = i+1 ; i < 160 ; i++ )
						{
							if( *pDst >= trigger_level )
							{
								HAL_GPIO_TogglePin( LED_GPIO_Port, LED_Pin );
								trigger_time = (counter_bck&0x03)*160+i;
								fsm_state = 5;
								break;
							}
							pDst++;
						}
						break;
					}
					pDst++;
				}
				if( trigger_mode == TRIGGER_MODE_AUTO && fsm_state == 3 )
				{
					trigger_time = (counter_bck&0x03)*160;
					fsm_state = 5;
				}
			}
			else if( trigger_mode == TRIGGER_MODE_DOWN )
			{
				for( i = 0 ; i < 160 ; i++ )
				{
					if( *pDst > trigger_level )
					{
						fsm_state = 4;
						pDst++;
						for( i = i+1 ; i < 160 ; i++ )
						{
							if( *pDst <= trigger_level )
							{
								trigger_time = (counter_bck&0x03)*160+i;
								fsm_state = 5;
								break;
							}
							pDst++;
						}
						break;
					}
					pDst++;
				}
			}
			else
			{
				trigger_time = (counter_bck&0x03)*160;
				fsm_state = 5;
			}

			break;
		case 4:
			if( trigger_mode == TRIGGER_MODE_AUTO || trigger_mode == TRIGGER_MODE_UP )
			{
				for( i = 0 ; i < 160 ; i++ )
				{
					if( *pDst >= trigger_level )
					{
						HAL_GPIO_TogglePin( LED_GPIO_Port, LED_Pin );
						trigger_time = (counter_bck&0x03)*160+i;
						fsm_state = 5;
						break;
					}
					pDst++;
				}
				if( trigger_mode == TRIGGER_MODE_AUTO && fsm_state == 4 )
				{
					trigger_time = (counter_bck&0x03)*160;
					fsm_state = 5;
				}
			}
			else if( trigger_mode == TRIGGER_MODE_DOWN )
			{
				for( i = 0 ; i < 160 ; i++ )
				{
					if( *pDst <= trigger_level )
					{
						trigger_time = (counter_bck&0x03)*160+i;
						fsm_state = 5;
						break;
					}
					pDst++;
				}
			}
			else
			{
				fsm_state = 5;
			}
			break;
		case 5:
			fsm_state = 6;
			break;
		case 6:
			fsm_state = 7;
			counter = 0;
			HAL_ADC_Stop_DMA( &hadc1 );
			break;
		case 7:
			break;
		default:
			break;
	}
}

void HAL_ADC_ConvHalfCpltCallback (ADC_HandleTypeDef *hadc )
{
	if( hadc == &hadc1 ){
		conversion_process( 0 );
	}
}

void HAL_ADC_ConvCpltCallback( ADC_HandleTypeDef *hadc )
{
	if( hadc == &hadc1 ){
		conversion_process( 1 );
	}
}

void task_adc( void const * argument )
{
	int16_t i, j;
	extern osMessageQId q_dso_adcHandle;
	extern osMessageQId q_adcHandle;
	tQueueAdcRequest adc_request;

	//osSemaphoreWait( sem_adc_doneHandle, osWaitForever );

	while( 1 )
	{
		osDelay( 1 );
		osEvent event = osMessageGet( q_dso_adcHandle, osWaitForever );
		if( event.status == osEventMessage )
		{
			adc_request = *(tQueueAdcRequest*)event.value.p;
			trigger_mode = adc_request.trigger_mode;
			trigger_level = adc_request.trigger_level;

			fsm_state = 1;
			//adc_request.sample_freq = 1999; // solve( 0.001 = ((35+1)*(arr+1))/72e6, arr )
			__HAL_TIM_SET_AUTORELOAD( &htim2, adc_request.sample_freq );
			HAL_ADC_Start_DMA( &hadc1, (uint32_t*)buffer_0, 320 );

			while( fsm_state != 7 )
			{
				osDelay( 1 );
			}

			for( i = 0 ; i < 320 ; i++ )
			{
				j = i + trigger_time - 160;

				if( j < 0 )
				{
					j += 160*4;
				}
				else if( j >= 160*4 )
				{
					j -= 160*4;
				}

				adc_request.buffer[i] = buffer_1[0][j];
			}

			//osSemaphoreRelease( q_adcHandle );
			osMessagePut( q_adcHandle, 0, osWaitForever );
		}

	}
}
