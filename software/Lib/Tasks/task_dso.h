/*
 * task_dso.h
 *
 *  Created on: May 2, 2020
 *      Author: jose
 */

#ifndef TASKS_TASK_DSO_H_
#define TASKS_TASK_DSO_H_

#include "imgui.h"
#include "task_adc.h"

enum eTriggerRepeat
{
	TRIGGER_REPEAT_AUTO = 0,
	TRIGGER_REPEAT_NORMAL,
	TRIGGER_REPEAT_SINGLE,
	TRIGGER_REPEAT_MAX
};
typedef enum eTriggerRepeat tTriggerRepeat;

enum eCursorMode
{
	CUSOR_MODE_HORIZONTAL = 0,
	CUSOR_MODE_VERTICAL,
	CUSOR_MODE_MAX,
};
typedef enum eCursorMode tCursorMode;

enum eMeasurementMode
{
	MEASUREMENT_MODE_VMIN = 0,
	MEASUREMENT_MODE_VMAX,
	MEASUREMENT_MODE_VMEAN,
	MEASUREMENT_MODE_VAMP,
	MEASUREMENT_MODE_FREQ,
	MEASUREMENT_MODE_DUTY,
	MEASUREMENT_MODE_MAX,
};
typedef enum eMeasurementMode tMeasurementMode;

struct sDsoState
{
	tWidget *pWidgets;

	uint8_t run;
	tTriggerRepeat trigger_repeat;

	uint16_t sample_freq;
	int16_t trigger_level;
	int16_t trigger_position;
	int16_t trigger_color;

	tTriggerMode trigger_mode;
	int16_t *buffer;
	uint16_t signal_color;

	tRectangle rect;

	uint8_t cursors_enabled;
	int16_t cursor_a;
	int16_t cursor_b;
	int8_t cursor_selected;
	tCursorMode cursor_mode;
	uint16_t cursor_color;

	uint8_t measurements_enabled;
	tMeasurementMode measurement_mode[6];

	uint8_t path;

	int32_t ax;
	int32_t bx;
	int32_t ay;
	int32_t by;
	// time gain, offset
	// voltage gain, offset
	// buffer: freq, gain
	// calibration values: paths gains and offsets
};
typedef struct sDsoState tDsoState;

void task_dso( void const * argument );

#endif /* TASKS_TASK_DSO_H_ */
