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
#include "lvgl.h"

#define START_TASK_PRIO     1
#define START_STK_SIZE      128
#define LED_TASK_PRIO       2
#define LED_STK_SIZE        128
#define LVGL_TASK_PRIO      2
#define LVGL_STK_SIZE       1024

TaskHandle_t StartTask_Handler;
void AppTaskStart(void *argument);

TaskHandle_t LEDTask_Handler;
void AppTaskLED(void *argument);
TaskHandle_t LVGLTask_Handler;
void AppTaskLVGL(void *argument);

static void AppTaskCreate(void);



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
    xTaskCreate(AppTaskLED, "AppTaskLED", LED_STK_SIZE, NULL, LED_TASK_PRIO, &LEDTask_Handler);
    xTaskCreate(AppTaskLVGL, "AppTaskLVGL", LVGL_STK_SIZE, NULL, LVGL_STK_SIZE, &LVGLTask_Handler);
}

void AppTaskLED(void *pvParameters)
{
    while (1)
    {
        bsp_LedToggle(1);
        bsp_LedToggle(2);
        printf("led toggle\r\n");
        vTaskDelay(1000);
    }
}

void AppTaskLVGL(void *pvParameters)
{
    lv_init();
    lv_tick_set_cb(xTaskGetTickCount);
    lv_port_disp_init();
    lv_user_gui_init();
    while (1)
    {
        lv_timer_handler();
        vTaskDelay(10);
    }
}

