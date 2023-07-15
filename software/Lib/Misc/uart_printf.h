

#include <stdint.h>
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart1;

void uart_putchar( UART_HandleTypeDef *huart, uint8_t value );
void uart_printf( UART_HandleTypeDef *huart, char *pFmt, ... );
