
#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include "stm32f1xx_hal.h"

struct sButton
{
	GPIO_TypeDef *port;
	uint16_t pin;

	int8_t debounce_count;
	int8_t debounce_count_max;

	GPIO_PinState enable_state;
	uint8_t state_bck;
	uint8_t state;

	uint8_t on_press;
	uint8_t on_release;
};

typedef struct sButton tButton;

void button_init( tButton *pThis, GPIO_TypeDef *port, uint16_t pin, GPIO_PinState enable_state );
void button_reset( tButton *pThis );
void button_process( tButton *pThis );
uint8_t button_get_state( tButton *pThis );
uint8_t button_get_on_press( tButton *pThis );
uint8_t button_get_on_release( tButton *pThis );

#endif // BUTTON_H

