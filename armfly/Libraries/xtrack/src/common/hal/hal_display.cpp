#include "hal.h"

static uint8_t* Disp_DMA_TragetPoint = nullptr;
static uint8_t* Disp_DMA_CurrentPoint = nullptr;
static HAL::Display_CallbackFunc_t Disp_Callback = nullptr;


void HAL::Display_Init()
{

}

void HAL::Display_DumpCrashInfo(const char* info)
{
    
}

void HAL::Display_SetAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{

}

void HAL::Display_SendPixels(uint16_t* pixels, uint32_t len)
{
}

void HAL::Display_SetSendFinishCallback(Display_CallbackFunc_t func)
{
    Disp_Callback = func;
}
