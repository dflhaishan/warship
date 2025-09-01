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

#include "xtrack_app.h"
#include "lvgl.h"
#include "hw_config.h"

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    hw_config_init();
    // bsp_InitLcd();
    xtrack_app_init();
    while (1)
    {
        xtrack_app_update();
    }
}