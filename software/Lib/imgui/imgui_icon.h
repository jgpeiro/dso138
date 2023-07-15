/*
 * imgui_icon.h
 *
 *  Created on: Apr 28, 2020
 *      Author: jose
 */

#ifndef IMGUI_IMGUI_ICON_H_
#define IMGUI_IMGUI_ICON_H_

#include <stdint.h>
#include "imgui.h"

#define ICON_MAX_ICONS			200
#define ICON_SIZE				16
#define ICON_DATA_ELEMENTS   	( ICON_SIZE*ICON_SIZE/32 )
#define ICONS_LEN 				( ICON_MAX_ICONS*ICON_DATA_ELEMENTS )

extern const uint32_t icons[ ICONS_LEN ];

void draw_icon( tRectangle rect, uint8_t icon, tColor color );
tRectangle get_icon_size( uint8_t icon );

#endif /* IMGUI_IMGUI_ICON_H_ */
