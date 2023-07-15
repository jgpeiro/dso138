/*
 * trace.c
 *
 *  Created on: Apr 12, 2020
 *      Author: jgarcia
 */

#include "trace.h"
#include "ticks_cpu.h"
#include "uart_printf.h"

//static uint8_t trace_buff_data[256];
//static uint32_t trace_buff_time[256];
//static uint16_t trace_buff_cnt;

void trace_init( tTrace *pThis )
{
	ticks_cpu_enable();
	trace_reset( pThis );
}

void trace_reset( tTrace *pThis )
{
	uint32_t i = 0;
	for( i = 0 ; i < TRACE_BUFFER_LEN ; i++ )
	{
		pThis->event[i] = TRACE_EVENT_NONE;
		pThis->time[i] = 0;
	}
	pThis->count = 0;
}

void trace_add( tTrace *pThis, tTraceEvent event )
{
	if( pThis->count < TRACE_BUFFER_LEN )
	{
		pThis->time[ pThis->count ] = ticks_cpu();
		pThis->event[ pThis->count ] = event;
		pThis->count += 1;
	}
}

void trace_dump( tTrace *pThis, UART_HandleTypeDef *huart )
{
	uint32_t i;
	uint32_t t0 = pThis->time[0];

	uart_printf( huart, "trace_dump\r\n" );
	for( i = 0 ; i < pThis->count ; i++ )
	{
		uart_printf( huart, "%x %x %x\r\n", i, pThis->time[i]-t0, pThis->event[i] );
	}
	pThis->count = 0;
}
/*
void trace_enable()
{
	ticks_cpu_enable();
}

void trace_reset()
{
	uint16_t i;

	uart_printf( &huart1, "trace_reset\r\n" );
	for( i = 0 ; i < 256 ; i++ )
	{
		trace_buff_time[i] = 0;
		trace_buff_data[i] = 0;
	}
	trace_buff_cnt = 0;
}

void trace_add( uint8_t event )
{
	if( trace_buff_cnt < 256 )
	{
		trace_buff_time[trace_buff_cnt] = ticks_cpu();
		trace_buff_data[trace_buff_cnt] = event;
		trace_buff_cnt++;
	}
}

void trace_dump()
{
	uint16_t i;

	uart_printf( &huart1, "trace_dump\r\n" );
	for( i = 0 ; i < trace_buff_cnt ; i++ )
	{
		uart_printf( &huart1, "%x %x %x\r\n", i, trace_buff_time[i], trace_buff_data[i] );
		trace_buff_time[i] = 0;
		trace_buff_data[i] = 0;
	}
	trace_buff_cnt = 0;
}
*/
