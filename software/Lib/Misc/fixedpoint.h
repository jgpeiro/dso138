//******************************************************************//
// Project:	OptomicLEO
// Autor:	Jose Antonio Garcia Peiro
// Date:	Junio-2011
//******************************************************************//

#ifndef		FIXED_POINT_H
#define 	FIXED_POINT_H	1

#include <stdint.h>

typedef int16_t fixed;

#define fracBits	15
#define fxdAdd( x, y )	((fixed)((x)+(y)))
#define fxdSub( x, y )	((fixed)((x)-(y)))
#define fxdMul( x, y )	((fixed)(((int)(x) * (int)(y)) >> fracBits))
#define fxdDiv( x, y )	((fixed)(((int)(x) << fracBits)/(y)))
#define fxd2flt( x )	((float)(x) / (0x1<<fracBits))
#define flt2fxd( x )	((fixed)((x) * (0x1<<fracBits)))

#endif	//#ifndef		FIXED_POINT_H
