/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_nCS_Pin GPIO_PIN_13
#define LCD_nCS_GPIO_Port GPIOC
#define LCD_DnC_Pin GPIO_PIN_14
#define LCD_DnC_GPIO_Port GPIOC
#define LCD_nWR_Pin GPIO_PIN_15
#define LCD_nWR_GPIO_Port GPIOC
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOD
#define OSC_OUT_Pin GPIO_PIN_1
#define OSC_OUT_GPIO_Port GPIOD
#define ADC_IN_Pin GPIO_PIN_0
#define ADC_IN_GPIO_Port GPIOA
#define VSENSEL2_Pin GPIO_PIN_1
#define VSENSEL2_GPIO_Port GPIOA
#define VSENSEL1_Pin GPIO_PIN_2
#define VSENSEL1_GPIO_Port GPIOA
#define CPLSEL_Pin GPIO_PIN_3
#define CPLSEL_GPIO_Port GPIOA
#define VMON_Pin GPIO_PIN_6
#define VMON_GPIO_Port GPIOA
#define TESTSIG_Pin GPIO_PIN_7
#define TESTSIG_GPIO_Port GPIOA
#define LCD_DB0_Pin GPIO_PIN_0
#define LCD_DB0_GPIO_Port GPIOB
#define LCD_DB1_Pin GPIO_PIN_1
#define LCD_DB1_GPIO_Port GPIOB
#define LCD_DB2_Pin GPIO_PIN_2
#define LCD_DB2_GPIO_Port GPIOB
#define LCD_nRD_Pin GPIO_PIN_10
#define LCD_nRD_GPIO_Port GPIOB
#define LCD_nRST_Pin GPIO_PIN_11
#define LCD_nRST_GPIO_Port GPIOB
#define BTN4_Pin GPIO_PIN_12
#define BTN4_GPIO_Port GPIOB
#define BTN3_Pin GPIO_PIN_13
#define BTN3_GPIO_Port GPIOB
#define BTN2_Pin GPIO_PIN_14
#define BTN2_GPIO_Port GPIOB
#define BTN1_Pin GPIO_PIN_15
#define BTN1_GPIO_Port GPIOB
#define TRIG_Pin GPIO_PIN_8
#define TRIG_GPIO_Port GPIOA
#define TRIG_EXTI_IRQn EXTI9_5_IRQn
#define TX1_Pin GPIO_PIN_9
#define TX1_GPIO_Port GPIOA
#define RX1_Pin GPIO_PIN_10
#define RX1_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_15
#define LED_GPIO_Port GPIOA
#define LCD_DB3_Pin GPIO_PIN_3
#define LCD_DB3_GPIO_Port GPIOB
#define LCD_DB4_Pin GPIO_PIN_4
#define LCD_DB4_GPIO_Port GPIOB
#define LCD_DB5_Pin GPIO_PIN_5
#define LCD_DB5_GPIO_Port GPIOB
#define LCD_DB6_Pin GPIO_PIN_6
#define LCD_DB6_GPIO_Port GPIOB
#define LCD_DB7_Pin GPIO_PIN_7
#define LCD_DB7_GPIO_Port GPIOB
#define TL_PWM_Pin GPIO_PIN_8
#define TL_PWM_GPIO_Port GPIOB
#define VGEN_Pin GPIO_PIN_9
#define VGEN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
