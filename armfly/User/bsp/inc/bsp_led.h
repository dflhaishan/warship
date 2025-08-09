/*
*********************************************************************************************************
*
*	模块名称 : led指示灯驱动模块
*	文件名称 : bsp_led.h
*	说    明 : 头文件
*
*
*********************************************************************************************************
*/

#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#ifdef __cplusplus
extern "C" {
#endif

void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);
void bsp_LedToggle(uint8_t _no);

#ifdef __cplusplus
}
#endif

#endif