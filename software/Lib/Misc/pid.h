/*
 * pid.h
 *
 *  Created on: May 13, 2020
 *      Author: jose
 */

#ifndef PID_H_
#define PID_H_

#include <stdint.h>

struct sPid
{
	int32_t kp;
	int32_t ki;
	int32_t kd;

	int32_t output;
	int32_t omin;
	int32_t omax;

	int32_t ie;
	int32_t de;
};
typedef struct sPid tPid;

void pid_init( tPid *pThis, int32_t kp, int32_t ki, int32_t kd, int32_t omin, int32_t omax );
void pid_reset( tPid *pThis );
void pid_process( tPid *pThis, int32_t e );
int32_t get_output( tPid *pThis );

#endif /* MISC_PID_H_ */
