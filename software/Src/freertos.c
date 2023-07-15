/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "task_adc.h"
#include "task_dso.h"
#include "task_imgui.h"
#include "task_user_input.h"
#include "task_power_supply.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;

osThreadId adcHandle;
osThreadId dsoHandle;
osThreadId uiHandle;
osThreadId btnHandle;
osThreadId psuHandle;

osMessageQId q_adcHandle;
osMessageQId q_dso_adcHandle;
osMessageQId q_uiHandle;
osMessageQId q_dso_uiHandle;
osMessageQId q_btnHandle;
osMessageQId q_selHandle;

osSemaphoreId s_widgetsHandle;
osSemaphoreId s_bufferHandle;
osSemaphoreId s_lcdHandle;
osSemaphoreId s_adc2Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
/*extern void task_adc(void const * argument);
extern void task_imgui(void const * argument);
extern void task_user_input(void const * argument);
extern void task_dso(void const * argument);
extern void task_power_supply(void const * argument);
*/

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of sem_adc_done */
  osSemaphoreDef(s_widgets);
  s_widgetsHandle = osSemaphoreCreate(osSemaphore(s_widgets), 1);
  osSemaphoreDef(s_buffer);
  s_bufferHandle = osSemaphoreCreate(osSemaphore(s_buffer), 1);
  osSemaphoreDef(s_lcd);
  s_lcdHandle = osSemaphoreCreate(osSemaphore(s_lcd), 1);
  osSemaphoreDef(s_adc2);
  s_adc2Handle = osSemaphoreCreate(osSemaphore(s_adc2), 1);
  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */

  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of queue_adc_request */
  osMessageQDef( q_adc, 1, uint32_t );
  q_adcHandle = osMessageCreate(osMessageQ(q_adc), NULL);
  osMessageQDef( q_dso_adc, 1, uint32_t );
  q_dso_adcHandle = osMessageCreate(osMessageQ(q_dso_adc), NULL);
  osMessageQDef( q_ui, 4, uint32_t );
  q_uiHandle = osMessageCreate(osMessageQ(q_ui), NULL);
  osMessageQDef( q_dso_ui, 4, uint32_t );
  q_dso_uiHandle = osMessageCreate(osMessageQ(q_dso_ui), NULL);
  osMessageQDef( q_btn, 4, uint32_t );
  q_btnHandle = osMessageCreate(osMessageQ(q_btn), NULL);
  osMessageQDef( q_sel, 4, uint32_t );
  q_selHandle = osMessageCreate(osMessageQ(q_sel), NULL);
  /* definition and creation of queue_buttons_event */


  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of adc */
  osThreadDef(adc, task_adc, osPriorityHigh, 0, 128+64);
  adcHandle = osThreadCreate(osThread(adc), NULL);

  /* definition and creation of imgui */
  osThreadDef(ui, task_imgui, osPriorityLow, 0, 128);
  uiHandle = osThreadCreate(osThread(ui), NULL);

  /* definition and creation of user_input */
  osThreadDef(btn, task_user_input, osPriorityLow, 0, 128);
  btnHandle = osThreadCreate(osThread(btn), NULL);

  /* definition and creation of dso */
  osThreadDef(dso, task_dso, osPriorityNormal, 0, 128);
  dsoHandle = osThreadCreate(osThread(dso), NULL);

  /* definition and creation of psu */
  osThreadDef(psu, task_psu, osPriorityHigh, 0, 128);
  psuHandle = osThreadCreate(osThread(psu), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
    
    
    
    
    
    

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
