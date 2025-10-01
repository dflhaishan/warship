#include "hal.h"
#include "tftlcd4_3_id5510.h"

#define DMA_MAX_SIZE        (0xFFFF)

static HAL::Display_CallbackFunc_t Disp_Callback = nullptr;

static TFTLcd4_3_id5510 screen(480, 800);

static DMA_HandleTypeDef Disp_DMA_HandleStruct;

static uint16_t* Disp_DMA_TargetPoint = nullptr;
static uint16_t* Disp_DMA_CurrentPoint = nullptr;

static void Display_DMA_Send(const void* buf, uint32_t size)
{
    if (size > DMA_MAX_SIZE)
    {
        if(Disp_DMA_TargetPoint == NULL)
        {
            Disp_DMA_TargetPoint = (uint16_t*)buf + size;
        }
        Disp_DMA_CurrentPoint = (uint16_t*)buf + DMA_MAX_SIZE;
        size = DMA_MAX_SIZE;
    }
    else
    {
        Disp_DMA_CurrentPoint = nullptr;
        Disp_DMA_TargetPoint = nullptr;
    }
    
    HAL_DMA_Start_IT(&Disp_DMA_HandleStruct, (uint32_t)buf, (uint32_t)(FSMC_BANK1_4 | (1 << 11)), size);
}

static void Display_DMA_xferCpltCallback(DMA_HandleTypeDef* hdma)
{
    if (Disp_DMA_CurrentPoint < Disp_DMA_TargetPoint)
    {
        Display_DMA_Send(Disp_DMA_CurrentPoint, Disp_DMA_TargetPoint - Disp_DMA_CurrentPoint);
    }
    else
    {
        if (Disp_Callback)
        {
            Disp_Callback();
        }
    }
}

static void Display_DMA_Init(void)
{
    __HAL_RCC_DMA1_CLK_ENABLE();

    Disp_DMA_HandleStruct.Instance = DMA1_Channel1;
    Disp_DMA_HandleStruct.Init.Direction = DMA_MEMORY_TO_MEMORY;
    Disp_DMA_HandleStruct.Init.PeriphInc = DMA_PINC_ENABLE;
    Disp_DMA_HandleStruct.Init.MemInc = DMA_MINC_DISABLE;
    Disp_DMA_HandleStruct.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    Disp_DMA_HandleStruct.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    Disp_DMA_HandleStruct.Init.Mode = DMA_NORMAL;
    Disp_DMA_HandleStruct.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    Disp_DMA_HandleStruct.XferCpltCallback = Display_DMA_xferCpltCallback;
    HAL_DMA_Init(&Disp_DMA_HandleStruct);

    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

extern "C" void DMA1_Channel1_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&Disp_DMA_HandleStruct);
}

void HAL::Display_Init()
{
    Serial.print("Display: init...");
    screen.begin();
    screen.fillScreen(screen.White);
    screen.setCursor(0, 0);

    Display_DMA_Init();
    Serial.println("success");
}

void HAL::Display_DumpCrashInfo(const char* info)
{
    Serial.printf("%s\r\n", info);
}

void HAL::Display_SetAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    screen.setAddrWindow(x0, y0, x1, y1);
}

#if 0
void HAL::Display_SendPixels(int16_t x, int16_t y, uint16_t color)
{
    screen.drawPixel(x, y, color);
}
#else
void HAL::Display_SendPixels(uint16_t* pixels, uint32_t len)
{
    *(uint16_t *)(FSMC_BANK1_4) = 0x2C00;
    Display_DMA_Send(pixels, len);
}
#endif

void HAL::Display_SetSendFinishCallback(Display_CallbackFunc_t func)
{
    Disp_Callback = func;
}
