#include "hal.h"
#include "tftlcd4_3_id5510.h"

static TFTLcd4_3_id5510 screen(480, 800);

void HAL::Display_Init()
{
    Serial.print("Display: init...");
    screen.begin();
    screen.fillScreen(screen.White);
    screen.setCursor(0, 0);
    Serial.println("success");
}

void HAL::Display_DumpCrashInfo(const char* info)
{

}

void HAL::Display_SetAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{

}

void HAL::Display_SendPixels(int16_t x, int16_t y, uint16_t color)
{
    screen.drawPixel(x, y, color);
}