
#ifndef TASK_ADC_H_
#define TASK_ADC_H_

#include <stdint.h>
#include "adc.h"
#include "tim.h"

enum eTriggerMode
{
	TRIGGER_MODE_AUTO = 0,
	TRIGGER_MODE_UP,
	TRIGGER_MODE_DOWN,
	TRIGGER_MODE_MAX
};
typedef enum eTriggerMode tTriggerMode;

struct sQueueAdcRequest
{
	uint16_t sample_freq;
	int16_t trigger_level;
	tTriggerMode trigger_mode;
	int16_t *buffer;
};
typedef struct sQueueAdcRequest tQueueAdcRequest;

void task_adc( void const * argument );

#endif /* TASK_ADC_H_ */
