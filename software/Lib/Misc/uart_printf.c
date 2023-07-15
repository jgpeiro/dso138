
#include "uart_printf.h"
#include <stdarg.h>

void uart_putchar( UART_HandleTypeDef *huart, uint8_t value )
{
	HAL_UART_Transmit( huart, (uint8_t*)&value, 1, HAL_MAX_DELAY );
}

void uart_printf( UART_HandleTypeDef *huart, char *pFmt, ... )
{
	uint8_t i, j;
	uint32_t value;
	va_list args;

	va_start( args, pFmt );

	for( i = 0 ; pFmt[i] != '\0' ; i++ ) {
		if( pFmt[i] == '%' )
		{
			i += 1;
			if( pFmt[i] == 'x' )
			{
				value = (uint32_t) va_arg( args, uint32_t );
				uart_putchar( huart, '0' );
				uart_putchar( huart, 'x' );
				for( j = 0 ; j < 8 ; j++ )
				{
					uint8_t digit;
					digit = (value >> (4*(8-j-1))) & 0xF;
					if( digit < 10 )
					{
						uart_putchar( huart, '0' + digit );
					}
					else
					{
						uart_putchar( huart, 'A' + digit - 10 );
					}
				}
			}
		}
		else
		{
			uart_putchar( huart, pFmt[i] );
		}
	}

	va_end(args);
}

