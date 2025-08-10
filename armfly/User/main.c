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
#include "delay.h"

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* HAL库，时钟等系统初始化 */
    System_Init();

    bsp_Init();
    
    lv_init();
    lv_port_init();
    // lv_user_gui_init();

    xtrack_app_init();
    while (1)
    {
        xtrack_app_update();
        lv_task_handler();
    }
}