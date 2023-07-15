
#include <stdint.h>
#include "stm32f1xx_hal.h"

#define TRACE_BUFFER_LEN	1

enum eTraceEvent
{
	TRACE_EVENT_NONE = 0,
	TRACE_EVENT_ADC_HALF_ENTER,
	TRACE_EVENT_ADC_HALF_EXIT,
	TRACE_EVENT_ADC_COMP_ENTER,
	TRACE_EVENT_ADC_COMP_EXIT,
	TRACE_EVENT_EXTI_ENTER,
	TRACE_EVENT_EXTI_EXIT,
	TRACE_EVENT_TASK_START,
	TRACE_EVENT_TASK_STOP,
};
typedef enum eTraceEvent tTraceEvent;

struct sTrace
{
	tTraceEvent event[TRACE_BUFFER_LEN];
	uint32_t time[TRACE_BUFFER_LEN];
	uint32_t count;
};

typedef struct sTrace tTrace;

void trace_init( tTrace *pThis );
void trace_reset( tTrace *pThis );
void trace_add( tTrace *pThis, tTraceEvent event );
void trace_dump( tTrace *pThis, UART_HandleTypeDef *huart );
