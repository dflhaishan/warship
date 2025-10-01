#ifndef _TFTLCD_4_3_ID5510_H
#define _TFTLCD_4_3_ID5510_H

#include <stdint.h>

class TFTLcd4_3_id5510
{
public:
    TFTLcd4_3_id5510(uint16_t w, uint16_t h);

    typedef enum
    {
        White = 0xFFFF,
        Black = 0x0000,
        Blue = 0x001F,
        Blue2 = 0x051F,
        Red = 0xF800,
        Magenta = 0xF81F,
        Green = 0x07E0,
        Cyan = 0x7FFF,
        Yellow = 0xFFE0
    } Color_Type;

    typedef struct 
    {
        uint16_t cmd;
        uint16_t val;
    }lcd_cmd_t;
    
    void begin();
    void writeCommand(uint16_t cmd) {};
    void writeData(uint16_t data) {};   
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void setAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    void setCursor(int16_t x, int16_t y);
    void setRotation(uint8_t r);
    void fillScreen(uint16_t color);

private:
    uint16_t width;
    uint16_t height;
    uint8_t rotation;
    uint32_t backlight_pin;
    uint16_t *cmd;
    uint16_t *data;
};

#endif