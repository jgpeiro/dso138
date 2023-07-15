/*
 * ili9341.c
 *
 *  Created on: Apr 5, 2020
 *      Author: jgarcia
 */
#include "ili9341.h"

void ili9341_reset( tILI9341 *pThis )
{
	HAL_GPIO_WritePin( pThis->nRST_port, pThis->nRST_pin, GPIO_PIN_RESET );
	HAL_Delay( 5 );
	HAL_GPIO_WritePin( pThis->nRST_port, pThis->nRST_pin, GPIO_PIN_SET );
	HAL_Delay( 100 );
}

void ili9341_enable( tILI9341 *pThis )
{
	HAL_GPIO_WritePin( pThis->nCS_port, pThis->nCS_pin, GPIO_PIN_RESET );
}

void ili9341_disable( tILI9341 *pThis )
{
	HAL_GPIO_WritePin( pThis->nCS_port, pThis->nCS_pin, GPIO_PIN_SET );
}

void ili9341_write_command( tILI9341 *pThis, uint8_t command )
{
	// nCS, nWR, nRD, DnC
	// L    LH   H    L
	HAL_GPIO_WritePin( pThis->DnC_port, pThis->DnC_pin, GPIO_PIN_RESET );

	pThis->DB07_port->ODR = (pThis->DB07_port->ODR & 0xFFFFFF00) | command;

	HAL_GPIO_WritePin( pThis->nWR_port, pThis->nWR_pin, GPIO_PIN_RESET );
	HAL_GPIO_WritePin( pThis->nWR_port, pThis->nWR_pin, GPIO_PIN_SET );
}

void ili9341_write_data( tILI9341 *pThis, uint8_t data )
{
	// nCS, nWR, nRD, DnC
	// L    LH   H    H
	HAL_GPIO_WritePin( pThis->DnC_port, pThis->DnC_pin, GPIO_PIN_SET );

	pThis->DB07_port->ODR = (pThis->DB07_port->ODR & 0xFFFFFF00) | data;

	HAL_GPIO_WritePin( pThis->nWR_port, pThis->nWR_pin, GPIO_PIN_RESET );
	HAL_GPIO_WritePin( pThis->nWR_port, pThis->nWR_pin, GPIO_PIN_SET );
}

void ili9341_init( tILI9341 *pThis )
{
	HAL_GPIO_WritePin( pThis->nRST_port,pThis->nRST_pin,GPIO_PIN_RESET );
	HAL_GPIO_WritePin( pThis->nCS_port, pThis->nCS_pin, GPIO_PIN_SET );
	HAL_GPIO_WritePin( pThis->nWR_port, pThis->nWR_pin, GPIO_PIN_SET );
	HAL_GPIO_WritePin( pThis->nRD_port, pThis->nRD_pin, GPIO_PIN_SET );
	HAL_GPIO_WritePin( pThis->DnC_port, pThis->DnC_pin, GPIO_PIN_SET );
	pThis->DB07_port->ODR &= 0xFFFFFF00;

	ili9341_reset( pThis );

	ili9341_enable( pThis );

	ili9341_write_command( pThis, ILI9341_SOFTWARE_RESET );
	HAL_Delay( 100 );

	ili9341_write_command( pThis, ILI9341_POWER_CONTROL_A );
	ili9341_write_data( pThis, 0x39 );
	ili9341_write_data( pThis, 0x2C );
	ili9341_write_data( pThis, 0x00 );
	ili9341_write_data( pThis, 0x34 );
	ili9341_write_data( pThis, 0x02 );

	ili9341_write_command( pThis, ILI9341_POWER_CONTROL_B );
	ili9341_write_data( pThis, 0x00 );
	ili9341_write_data( pThis, 0xC1 );
	ili9341_write_data( pThis, 0x30 );

	ili9341_write_command( pThis, ILI9341_DRIVER_TIMING_CONTROL_A );
	ili9341_write_data( pThis, 0x85 );
	ili9341_write_data( pThis, 0x00 );
	ili9341_write_data( pThis, 0x78 );

	ili9341_write_command( pThis, ILI9341_DRIVER_TIMING_CONTROL_B );
	ili9341_write_data( pThis, 0x00 );
	ili9341_write_data( pThis, 0x00 );

	ili9341_write_command( pThis, ILI9341_POWER_ON_SEQUENCE_CONTROL );
	ili9341_write_data( pThis, 0x64 );
	ili9341_write_data( pThis, 0x03 );
	ili9341_write_data( pThis, 0x12 );
	ili9341_write_data( pThis, 0x81 );

	ili9341_write_command( pThis, ILI9341_PUMP_RATIO_CONTROL );
	ili9341_write_data( pThis, 0x20 );

	ili9341_write_command( pThis, ILI9341_POWER_CONTROL_1 );
	ili9341_write_data( pThis, 0x23 );

	ili9341_write_command( pThis, ILI9341_POWER_CONTROL_2 );
	ili9341_write_data( pThis, 0x10 );

	ili9341_write_command( pThis, ILI9341_VCM_CONTROL_1 );
	ili9341_write_data( pThis, 0x3E );
	ili9341_write_data( pThis, 0x28 );

	ili9341_write_command( pThis, ILI9341_VCM_CONTROL_2 );
	ili9341_write_data( pThis, 0x86 );

	ili9341_write_command( pThis, ILI9341_MEMORY_ACCESS_CONTROL );
	//ili9341_write_data( pThis, 0x88 );
	ili9341_write_data( pThis, 0xC8 );

	ili9341_write_command( pThis, ILI9341_PIXEL_FORMAT );
	ili9341_write_data( pThis, 0x55 );

	ili9341_write_command( pThis, ILI9341_FRAME_RATIO_CONTROL );
	ili9341_write_data( pThis, 0x00 );
	ili9341_write_data( pThis, 0x18 );

	ili9341_write_command( pThis, ILI9341_DISPLAY_FUNCTION_CONTROL );
	ili9341_write_data( pThis, 0x08 );
	ili9341_write_data( pThis, 0x82 );
	ili9341_write_data( pThis, 0x27 );

	ili9341_write_command( pThis, ILI9341_EXIT_SLEEP );
	HAL_Delay( 100 );

	ili9341_clear( pThis, 0x0000 );

	ili9341_enable( pThis ); // lcd was disabled on ili9341_clear
	ili9341_write_command( pThis, ILI9341_TURN_ON_DISPLAY );

	ili9341_disable( pThis );
}

void ili9341_set_address_window( tILI9341 *pThis, int16_t x, int16_t y, int16_t w, int16_t h )
{
	// ili9341_enable( pThis );

	int16_t x2, y2;

	x2 = x + w - 1;
	y2 = y + h - 1;

	ili9341_write_command( pThis, ILI9341_PAGE_ADDRESS_SET );
	ili9341_write_data( pThis, x >> 8 );
	ili9341_write_data( pThis, x );
	ili9341_write_data( pThis, x2 >> 8 );
	ili9341_write_data( pThis, x2 );

	ili9341_write_command( pThis, ILI9341_COLUMN_ADDRESS_SET );
	ili9341_write_data( pThis, y >> 8 );
	ili9341_write_data( pThis, y );
	ili9341_write_data( pThis, y2 >> 8 );
	ili9341_write_data( pThis, y2 );

	// ili9341_disable( pThis );
}

void ili9341_draw_pixel( tILI9341 *pThis, int16_t x, int16_t y, uint16_t color )
{
	if( !( 0 <= x && x < ILI9341_WIDTH ) )
	{
		return;
	}
	if( !( 0 <= y && y < ILI9341_HEIGHT ) )
	{
		return;
	}

	ili9341_enable( pThis );

	ili9341_write_command( pThis, ILI9341_PAGE_ADDRESS_SET );
	ili9341_write_data( pThis, x >> 8 );
	ili9341_write_data( pThis, x );

	ili9341_write_command( pThis, ILI9341_COLUMN_ADDRESS_SET );
	ili9341_write_data( pThis, y >> 8 );
	ili9341_write_data( pThis, y );

	ili9341_write_command( pThis, ILI9341_MEMORY_WRITE );
	ili9341_write_data( pThis, color >> 8 );
	ili9341_write_data( pThis, color & 0xFF );

    ili9341_disable( pThis );
}

#include "main.h"

void ili9341_draw_pixel_fast( tILI9341 *pThis, int16_t x, int16_t y, uint16_t color )
{
	if( !( 0 <= x && x < ILI9341_WIDTH ) )
	{
		return;
	}
	if( !( 0 <= y && y < ILI9341_HEIGHT ) )
	{
		return;
	}

	uint32_t ORDh = GPIOB->ODR & 0xFFFFFF00;


	//ili9341_enable( pThis );
	GPIOC->BSRR = (uint32_t)LCD_nCS_Pin << 16u;

	//ili9341_write_command( pThis, ILI9341_PAGE_ADDRESS_SET );
	GPIOC->BSRR = (uint32_t)LCD_DnC_Pin << 16u;
	GPIOB->ODR =  ORDh | ILI9341_PAGE_ADDRESS_SET;
	GPIOC->BSRR = (uint32_t)GPIO_PIN_15 << 16u;;
	GPIOC->BSRR = GPIO_PIN_15;

	//ili9341_write_data( pThis, x >> 8 );
	GPIOC->BSRR = LCD_DnC_Pin;
	GPIOB->ODR = ORDh | (x>>8);
	GPIOC->BSRR = (uint32_t)LCD_nWR_Pin << 16u;;
	GPIOC->BSRR = LCD_nWR_Pin;

	//ili9341_write_data( pThis, x );
	GPIOC->BSRR = LCD_DnC_Pin;
	GPIOB->ODR = ORDh | (x&0xFF);
	GPIOC->BSRR = (uint32_t)LCD_nWR_Pin << 16u;;
	GPIOC->BSRR = LCD_nWR_Pin;

	//ili9341_write_command( pThis, ILI9341_COLUMN_ADDRESS_SET );
	GPIOC->BSRR = (uint32_t)LCD_DnC_Pin << 16u;
	GPIOB->ODR = ORDh | ILI9341_COLUMN_ADDRESS_SET;
	GPIOC->BSRR = (uint32_t)LCD_nWR_Pin << 16u;;
	GPIOC->BSRR = LCD_nWR_Pin;

	//ili9341_write_data( pThis, y >> 8 );
	GPIOC->BSRR = LCD_DnC_Pin;
	GPIOB->ODR = ORDh | (y>>8);
	GPIOC->BSRR = (uint32_t)LCD_nWR_Pin << 16u;;
	GPIOC->BSRR = LCD_nWR_Pin;

	//ili9341_write_data( pThis, y );
	GPIOC->BSRR = LCD_DnC_Pin;
	GPIOB->ODR = ORDh | (y&0xFF);
	GPIOC->BSRR = (uint32_t)LCD_nWR_Pin << 16u;;
	GPIOC->BSRR = LCD_nWR_Pin;

	//ili9341_write_command( pThis, ILI9341_MEMORY_WRITE );
	GPIOC->BSRR = (uint32_t)LCD_DnC_Pin << 16u;
	GPIOB->ODR = ORDh | ILI9341_MEMORY_WRITE;
	GPIOC->BSRR = (uint32_t)LCD_nWR_Pin << 16u;;
	GPIOC->BSRR = LCD_nWR_Pin;

	//ili9341_write_data( pThis, color >> 8 );
	GPIOC->BSRR = LCD_DnC_Pin;
	GPIOB->ODR = ORDh | (color>>8);
	GPIOC->BSRR = (uint32_t)LCD_nWR_Pin << 16u;;
	GPIOC->BSRR = LCD_nWR_Pin;

	//ili9341_write_data( pThis, color & 0xFF );
	GPIOC->BSRR = LCD_DnC_Pin;
	GPIOB->ODR = ORDh | (color&0xFF);
	GPIOC->BSRR = (uint32_t)LCD_nWR_Pin << 16u;;
	GPIOC->BSRR = LCD_nWR_Pin;

    //ili9341_disable( pThis );
	GPIOC->BSRR = LCD_nCS_Pin;
}

void ili9341_draw_rect( tILI9341 *pThis, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color )
{
	uint32_t i;

	if( w == 0 || h == 0 )
	{
		return;
	}

	if( w > ILI9341_WIDTH )
	{
		w = ILI9341_WIDTH;
	}
	if( h > ILI9341_HEIGHT )
	{
		h = ILI9341_HEIGHT;
	}

	ili9341_enable( pThis );

	ili9341_set_address_window( pThis, x, y, w, h );

	ili9341_write_command( pThis, ILI9341_MEMORY_WRITE );

	HAL_GPIO_WritePin( pThis->DnC_port, pThis->DnC_pin, GPIO_PIN_SET );

	for( i = 0 ; i < w*h ; i++ )
	{
		ili9341_write_data( pThis, color >> 8 );
		ili9341_write_data( pThis, color );
	}

	ili9341_set_address_window( pThis, 0, 0, ILI9341_WIDTH, ILI9341_HEIGHT );

    ili9341_disable( pThis );
}

void ili9341_draw_rect_fast( tILI9341 *pThis, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color )
{
	uint32_t i;

	__IO uint32_t *ODR = &pThis->DB07_port->ODR;
	uint32_t valueh = (*ODR & 0xFFFFFF00) | ((color>>8)&0xFF); // retain current ODR values. (0xFFFFFF00)
	uint32_t valuel = (*ODR & 0xFFFFFF00) | ((color>>0)&0xFF);

	if( w == 0 || h == 0 )
	{
		return;
	}

	if( w > ILI9341_WIDTH )
	{
		w = ILI9341_WIDTH;
	}
	if( h > ILI9341_HEIGHT )
	{
		h = ILI9341_HEIGHT;
	}

	ili9341_enable( pThis );
	ili9341_set_address_window( pThis, x, y, w, h );
	ili9341_write_command( pThis, ILI9341_MEMORY_WRITE );

	GPIOC->BSRR = LCD_DnC_Pin;
	for( i = 0 ; i < w*h ; i++ )
	{
		GPIOB->ODR = valueh;
		GPIOC->BSRR = (uint32_t)LCD_nWR_Pin << 16u;
		GPIOC->BSRR = LCD_nWR_Pin;

		GPIOB->ODR = valuel;
		GPIOC->BSRR = (uint32_t)LCD_nWR_Pin << 16u;
		GPIOC->BSRR = LCD_nWR_Pin;
	}

	ili9341_set_address_window( pThis, 0, 0, ILI9341_WIDTH, ILI9341_HEIGHT );
    ili9341_disable( pThis );
}

void ili9341_clear( tILI9341 *pThis, uint16_t color )
{
	ili9341_draw_rect( pThis, 0, 0, ILI9341_WIDTH, ILI9341_HEIGHT, color );
}
