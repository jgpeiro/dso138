/*
 * pid.c
 *
 *  Created on: May 13, 2020
 *      Author: jose
 */

#include "pid.h"

void pid_init( tPid *pThis, int32_t kp, int32_t ki, int32_t kd, int32_t omin, int32_t omax )
{
	pThis->kp = kp;
	pThis->ki = ki;
	pThis->kd = kd;

	pThis->omin = omin;
	pThis->omax = omax;

	pThis->ie = 0;
	pThis->de = 0;
}

void pid_reset( tPid *pThis )
{
	pThis->ie = 0;
	pThis->de = 0;
}

void pid_process( tPid *pThis, int32_t e )
{
	int32_t de = e-pThis->de;
	pThis->output = pThis->kp*e + pThis->ki*pThis->ie + pThis->kd*de;

	if( pThis->output < pThis->omin )
	{
		pThis->output = pThis->omin;
	}
	else if( pThis->output > pThis->omax )
	{
		pThis->output = pThis->omax;
	}
	else
	{
		pThis->ie += e;
	}
	pThis->de = e;
}

int32_t get_output( tPid *pThis )
{
	return pThis->output;
}

