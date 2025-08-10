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
#include "lv_port.h"
#include "xtrack_app.h"
#include "cm_backtrace.h"
#include "version.h"
/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* HAL库，时钟等系统初始化 */
    System_Init();

    bsp_Init();

    cm_backtrace_init(VERSION_FIRMWARE_NAME, VERSION_HARDWARE, VERSION_SOFTWARE);
    
    lv_init();
    lv_port_init();
    
    xtrack_app_init();
    while (1)
    {
        xtrack_app_update();
        lv_task_handler();
    }
}