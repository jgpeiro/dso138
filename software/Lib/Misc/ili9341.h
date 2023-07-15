
#ifndef ILI9341_H
#define ILI9341_H

#include <stdint.h>
#include "stm32f1xx_hal.h"
//#include "colors_565.h"

#define ILI9341_WIDTH	320
#define ILI9341_HEIGHT	240

#define	ILI9341_SOFTWARE_RESET				0x01
#define	ILI9341_POWER_CONTROL_A				0xCB
#define	ILI9341_POWER_CONTROL_B 			0xCF
#define	ILI9341_DRIVER_TIMING_CONTROL_A		0xE8
#define ILI9341_DRIVER_TIMING_CONTROL_B		0xEA
#define ILI9341_POWER_ON_SEQUENCE_CONTROL	0xED
#define ILI9341_PUMP_RATIO_CONTROL 			0xF7
#define ILI9341_POWER_CONTROL_1				0xC0
#define ILI9341_POWER_CONTROL_2				0xC1
#define ILI9341_VCM_CONTROL_1				0xC5
#define ILI9341_VCM_CONTROL_2				0xC7
#define ILI9341_MEMORY_ACCESS_CONTROL		0x36
#define ILI9341_PIXEL_FORMAT				0x3A
#define ILI9341_FRAME_RATIO_CONTROL			0xB1
#define ILI9341_DISPLAY_FUNCTION_CONTROL	0xB6
#define ILI9341_GAMMA_FUNCTION_DISABLE		0xF2
#define ILI9341_GAMMA_CURVE_SELECTED 		0x26
#define ILI9341_POSITIVE_GAMMA_CORRECTION	0xE0
#define ILI9341_NEGATIVE_GAMMA_CORRECTION	0xE1
#define ILI9341_EXIT_SLEEP					0x11
#define ILI9341_TURN_ON_DISPLAY				0x29

#define ILI9341_COLUMN_ADDRESS_SET			0x2A
#define ILI9341_PAGE_ADDRESS_SET			0x2B
#define ILI9341_MEMORY_WRITE				0x2C

struct sILI9341
{
	GPIO_TypeDef *nRST_port;
	GPIO_TypeDef *nCS_port;
	GPIO_TypeDef *nWR_port;
	GPIO_TypeDef *nRD_port;
	GPIO_TypeDef *DnC_port;
	GPIO_TypeDef *DB07_port;

	uint16_t nRST_pin;
	uint16_t nCS_pin;
	uint16_t nWR_pin;
	uint16_t nRD_pin;
	uint16_t DnC_pin;
};
typedef struct sILI9341 tILI9341;

void ili9341_reset( tILI9341 *pThis );
void ili9341_enable( tILI9341 *pThis );
void ili9341_disable( tILI9341 *pThis );
void ili9341_write_command( tILI9341 *pThis, uint8_t command );
void ili9341_write_data( tILI9341 *pThis, uint8_t data );

//void ili9341_write_buffer( tILI9341 *pThis, uint8_t *buffer, uint8_t len );
void ili9341_init( tILI9341 *pThis );
void ili9341_set_address_window( tILI9341 *pThis, int16_t x, int16_t y, int16_t w, int16_t h );
void ili9341_draw_pixel( tILI9341 *pThis, int16_t x, int16_t y, uint16_t color );
void ili9341_draw_rect( tILI9341 *pThis, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color );
void ili9341_draw_pixel_fast( tILI9341 *pThis, int16_t x, int16_t y, uint16_t color );
void ili9341_draw_rect_fast( tILI9341 *pThis, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color );
void ili9341_clear( tILI9341 *pThis, uint16_t color );

#endif
