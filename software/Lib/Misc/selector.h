

#include <stdint.h>
#include "stm32f1xx_hal.h"

struct sSelector
{
	ADC_HandleTypeDef* hadc;
	uint32_t channel;

	int8_t debounce_count_1;
	int8_t debounce_count_2;
	int8_t debounce_count_3;

	uint8_t state_bck;
	uint8_t state;

	uint8_t on_change;
};

typedef struct sSelector tSelector;

void selector_init( tSelector *pThis, ADC_HandleTypeDef* hadc, uint32_t channel );
void selector_reset( tSelector *pThis );
void selector_process( tSelector *pThis );
uint8_t selector_get_state( tSelector *pThis );
uint8_t selector_get_on_change( tSelector *pThis );
