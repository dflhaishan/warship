/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "includes.h"
#include "bsp.h"

#define START_TASK_PRIO     1
#define START_STK_SIZE      128
#define LED0_TASK_PRIO      2
#define LED0_STK_SIZE       128
#define LED1_TASK_PRIO      2
#define LED1_STK_SIZE       128

TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);

TaskHandle_t LED0Task_Handler;
void LED0Task(void *pvParameters);

TaskHandle_t LED1Task_Handler;
void LED1Task(void *pvParameters);

void led_init(void);


static void AppTaskCreate(void);
void AppTaskLED(void *argument);
void AppTaskStart(void *argument);

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* HAL库，时钟等系统初始化 */
    System_Init();

    xTaskCreate(AppTaskStart, "AppTaskStart", START_STK_SIZE, NULL, START_TASK_PRIO, &StartTask_Handler);

    vTaskStartScheduler();
    while (1)
    {
    }
}

/*
*********************************************************************************************************
*	函 数 名: AppTaskStart
*	功能说明: 启动任务，这里用作BSP驱动包处理。
*	形    参: 无
*	返 回 值: 无
*   优 先 级: osPriorityNormal6  
*********************************************************************************************************
*/
void AppTaskStart(void *argument)
{	
	/* 初始化外设 */
	bsp_Init();

	/* 创建任务 */
	AppTaskCreate();

	vTaskDelete(StartTask_Handler);
}

void AppTaskCreate()
{
    xTaskCreate(LED0Task, "LED0Task", LED0_STK_SIZE, NULL, LED0_TASK_PRIO, &LED0Task_Handler);
    xTaskCreate(LED1Task, "LED1Task", LED1_STK_SIZE, NULL, LED1_TASK_PRIO, &LED1Task_Handler);
}

void LED0Task(void *pvParameters)
{
    while (1)
    {
        bsp_LedToggle(1);
        printf("led 1 toggle\r\n");
        vTaskDelay(1000);
    }
}

void LED1Task(void *pvParameters)
{
    while (1)
    {
        bsp_LedToggle(2);
        printf("led 2 toggle\r\n");
        vTaskDelay(1000);
    }
}
