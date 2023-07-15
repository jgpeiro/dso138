
#include "ticks_cpu.h"
#include "stm32f1xx_hal.h"

void ticks_cpu_enable( void )
{
    if( !( DWT->CTRL & DWT_CTRL_CYCCNTENA_Msk ) )
    {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
        DWT->CYCCNT = 0;
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    }
}

uint32_t ticks_cpu( void )
{
    return DWT->CYCCNT;
}
