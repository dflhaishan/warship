/*
*********************************************************************************************************
*
*	模块名称 : TFT液晶显示器驱动模块
*	文件名称 : bsp_tft_lcd.c
*	版    本 : V4.2
*	说    明 : 支持3.0， 3.5， 4.3， 5.0， 7.0寸显示模块.
*			  3.0寸的支持的LCD内部驱动芯片型号有: SPFD5420A、OTM4001A、R61509V
*	修改记录 :
*		版本号  日期       作者    说明
*		v1.0    2024-09-17 jhs  ST固件库版本 V3.5.0版本。
*
*********************************************************************************************************
*/

#include "bsp.h"
#include "fonts.h"

static void InitHardLcd(void);
static void LCD_SetPwmBackLight(uint8_t _bright);

SRAM_HandleTypeDef TFTSRAM_Handler;
SRAM_HandleTypeDef SRAM_HandleStruct;

static struct lcd_ctrl_t lcd_ctrl = 
{
    .reg          = (uint16_t *)(FSMC_BANK1_4), 
    .ram          = (uint16_t *)(FSMC_BANK1_4 | (1 << 11)),
    .hight        = 800,
    .width        = 480,
    .brightness   = 10,
    .direction    = 0,
    .set_x_cmd    = 0x2A00,
    .set_y_cmd    = 0x2B00,
    .set_gram_cmd = 0x2C00,
};

const struct lcd_cmd_t lcd_cmd[] = 
{
    {0xF000, 0x55}, {0xF001, 0xAA}, {0xF002, 0x52}, {0xF003, 0x08}, {0xF004, 0x01}, 
    //AVDD Set AVDD 5.2V
    {0xB000, 0x0D}, {0xB001, 0x0D}, {0xB002, 0x0D}, 
    //AVDD ratio
    {0xB600, 0x34}, {0xB601, 0x34}, {0xB602, 0x34}, 
    //AVEE -5.2V
    {0xB100, 0x0D}, {0xB101, 0x0D}, {0xB102, 0x0D}, 
    //AVEE ratio
    {0xB700, 0x34}, {0xB701, 0x34}, {0xB702, 0x34}, 
    //VCL -2.5V
    {0xB200, 0x00}, {0xB201, 0x00}, {0xB202, 0x00}, 
    //VCL ratio
    {0xB800, 0x24}, {0xB801, 0x24}, {0xB802, 0x24}, 
    //VGH 15V (Free pump)
    {0xBF00, 0x01}, {0xB300, 0x0F}, {0xB301, 0x0F}, {0xB302, 0x0F}, 
    //VGH ratio
    {0xB900, 0x34}, {0xB901, 0x34}, {0xB902, 0x34}, 
    //VGL_REG -10V
    {0xB500, 0x08}, {0xB501, 0x08}, {0xB502, 0x08}, {0xC200, 0x03}, 
    //VGLX ratio
    {0xBA00, 0x24}, {0xBA01, 0x24}, {0xBA02, 0x24}, 
    //VGMP/VGSP 4.5V/0V
    {0xBC00, 0x00}, {0xBC01, 0x78}, {0xBC02, 0x00}, 
    //VGMN/VGSN -4.5V/0V
    {0xBD00, 0x00}, {0xBD01, 0x78}, {0xBD02, 0x00}, 
    //VCOM
    {0xBE00, 0x00}, {0xBE01, 0x64}, {0xD100, 0x00}, {0xD101, 0x33}, 
    {0xD102, 0x00}, {0xD103, 0x34}, {0xD104, 0x00}, {0xD105, 0x3A}, 
    {0xD106, 0x00}, {0xD107, 0x4A}, {0xD108, 0x00}, {0xD109, 0x5C}, 
    {0xD10A, 0x00}, {0xD10B, 0x81}, {0xD10C, 0x00}, {0xD10D, 0xA6}, 
    {0xD10E, 0x00}, {0xD10F, 0xE5}, {0xD110, 0x01}, {0xD111, 0x13}, 
    {0xD112, 0x01}, {0xD113, 0x54}, {0xD114, 0x01}, {0xD115, 0x82}, 
    {0xD116, 0x01}, {0xD117, 0xCA}, {0xD118, 0x02}, {0xD119, 0x00}, 
    {0xD11A, 0x02}, {0xD11B, 0x01}, {0xD11C, 0x02}, {0xD11D, 0x34}, 
    {0xD11E, 0x02}, {0xD11F, 0x67}, {0xD121, 0x84}, {0xD122, 0x02}, 
    {0xD123, 0xA4}, {0xD124, 0x02}, {0xD125, 0xB7}, {0xD126, 0x02}, 
    {0xD127, 0xCF}, {0xD128, 0x02}, {0xD129, 0xDE}, {0xD12A, 0x02}, 
    {0xD12B, 0xF2}, {0xD12C, 0x02}, {0xD12D, 0xFE}, {0xD12E, 0x03}, 
    {0xD12F, 0x10}, {0xD130, 0x03}, {0xD131, 0x33}, {0xD132, 0x03}, 
    {0xD133, 0x6D}, {0xD200, 0x00}, {0xD201, 0x33}, {0xD202, 0x00}, 
    {0xD203, 0x34}, {0xD204, 0x00}, {0xD205, 0x3A}, {0xD206, 0x00}, 
    {0xD207, 0x4A}, {0xD208, 0x00}, {0xD209, 0x5C}, {0xD20A, 0x00}, 
    {0xD20B, 0x81}, {0xD20C, 0x00}, {0xD20D, 0xA6}, {0xD20E, 0x00}, 
    {0xD20F, 0xE5}, {0xD210, 0x01}, {0xD211, 0x13}, {0xD212, 0x01}, 
    {0xD213, 0x54}, {0xD214, 0x01}, {0xD215, 0x82}, {0xD216, 0x01}, 
    {0xD217, 0xCA}, {0xD218, 0x02}, {0xD219, 0x00}, {0xD21A, 0x02}, 
    {0xD21B, 0x01}, {0xD21C, 0x02}, {0xD21D, 0x34}, {0xD21E, 0x02}, 
    {0xD21F, 0x67}, {0xD220, 0x02}, {0xD221, 0x84}, {0xD222, 0x02}, 
    {0xD223, 0xA4}, {0xD224, 0x02}, {0xD225, 0xB7}, {0xD226, 0x02}, 
    {0xD227, 0xCF}, {0xD228, 0x02}, {0xD229, 0xDE}, {0xD22A, 0x02}, 
    {0xD22B, 0xF2}, {0xD22C, 0x02}, {0xD22D, 0xFE}, {0xD22E, 0x03}, 
    {0xD22F, 0x10}, {0xD230, 0x03}, {0xD231, 0x33}, {0xD232, 0x03}, 
    {0xD233, 0x6D}, {0xD300, 0x00}, {0xD301, 0x33}, {0xD302, 0x00}, 
    {0xD303, 0x34}, {0xD304, 0x00}, {0xD305, 0x3A}, {0xD306, 0x00}, 
    {0xD307, 0x4A}, {0xD308, 0x00}, {0xD309, 0x5C}, {0xD30A, 0x00}, 
    {0xD30B, 0x81}, {0xD30C, 0x00}, {0xD30D, 0xA6}, {0xD30E, 0x00}, 
    {0xD30F, 0xE5}, {0xD310, 0x01}, {0xD311, 0x13}, {0xD312, 0x01}, 
    {0xD313, 0x54}, {0xD314, 0x01}, {0xD315, 0x82}, {0xD316, 0x01}, 
    {0xD317, 0xCA}, {0xD318, 0x02}, {0xD319, 0x00}, {0xD31A, 0x02}, 
    {0xD31B, 0x01}, {0xD31C, 0x02}, {0xD31D, 0x34}, {0xD31E, 0x02}, 
    {0xD31F, 0x67}, {0xD320, 0x02}, {0xD321, 0x84}, {0xD322, 0x02}, 
    {0xD323, 0xA4}, {0xD324, 0x02}, {0xD325, 0xB7}, {0xD326, 0x02}, 
    {0xD327, 0xCF}, {0xD328, 0x02}, {0xD329, 0xDE}, {0xD32A, 0x02}, 
    {0xD32B, 0xF2}, {0xD32C, 0x02}, {0xD32D, 0xFE}, {0xD32E, 0x03}, 
    {0xD32F, 0x10}, {0xD330, 0x03}, {0xD331, 0x33}, {0xD332, 0x03}, 
    {0xD333, 0x6D}, {0xD400, 0x00}, {0xD401, 0x33}, {0xD402, 0x00}, 
    {0xD403, 0x34}, {0xD404, 0x00}, {0xD405, 0x3A}, {0xD406, 0x00}, 
    {0xD407, 0x4A}, {0xD408, 0x00}, {0xD409, 0x5C}, {0xD40A, 0x00}, 
    {0xD40B, 0x81}, {0xD40C, 0x00}, {0xD40D, 0xA6}, {0xD40E, 0x00}, 
    {0xD40F, 0xE5}, {0xD410, 0x01}, {0xD411, 0x13}, {0xD412, 0x01}, 
    {0xD413, 0x54}, {0xD414, 0x01}, {0xD415, 0x82}, {0xD416, 0x01}, 
    {0xD417, 0xCA}, {0xD418, 0x02}, {0xD419, 0x00}, {0xD41A, 0x02}, 
    {0xD41B, 0x01}, {0xD41C, 0x02}, {0xD41D, 0x34}, {0xD41E, 0x02},
    {0xD41F, 0x67}, {0xD420, 0x02}, {0xD421, 0x84}, {0xD422, 0x02}, 
    {0xD423, 0xA4}, {0xD424, 0x02}, {0xD425, 0xB7}, {0xD426, 0x02}, 
    {0xD427, 0xCF}, {0xD428, 0x02}, {0xD429, 0xDE}, {0xD42A, 0x02}, 
    {0xD42B, 0xF2}, {0xD42C, 0x02}, {0xD42D, 0xFE}, {0xD42E, 0x03}, 
    {0xD42F, 0x10}, {0xD430, 0x03}, {0xD431, 0x33}, {0xD432, 0x03}, 
    {0xD433, 0x6D}, {0xD500, 0x00}, {0xD501, 0x33}, {0xD502, 0x00}, 
    {0xD503, 0x34}, {0xD504, 0x00}, {0xD505, 0x3A}, {0xD506, 0x00}, 
    {0xD507, 0x4A}, {0xD508, 0x00}, {0xD509, 0x5C}, {0xD50A, 0x00}, 
    {0xD50B, 0x81}, {0xD50C, 0x00}, {0xD50D, 0xA6}, {0xD50E, 0x00}, 
    {0xD50F, 0xE5}, {0xD510, 0x01}, {0xD511, 0x13}, {0xD512, 0x01}, 
    {0xD513, 0x54}, {0xD514, 0x01}, {0xD515, 0x82}, {0xD516, 0x01}, 
    {0xD517, 0xCA}, {0xD518, 0x02}, {0xD519, 0x00}, {0xD51A, 0x02}, 
    {0xD51B, 0x01}, {0xD51C, 0x02}, {0xD51D, 0x34}, {0xD51E, 0x02}, 
    {0xD51F, 0x67}, {0xD520, 0x02}, {0xD521, 0x84}, {0xD522, 0x02}, 
    {0xD523, 0xA4}, {0xD524, 0x02}, {0xD525, 0xB7}, {0xD526, 0x02}, 
    {0xD527, 0xCF}, {0xD528, 0x02}, {0xD529, 0xDE}, {0xD52A, 0x02}, 
    {0xD52B, 0xF2}, {0xD52C, 0x02}, {0xD52D, 0xFE}, {0xD52E, 0x03}, 
    {0xD52F, 0x10}, {0xD530, 0x03}, {0xD531, 0x33}, {0xD532, 0x03}, 
    {0xD533, 0x6D}, {0xD600, 0x00}, {0xD601, 0x33}, {0xD602, 0x00}, 
    {0xD603, 0x34}, {0xD604, 0x00}, {0xD605, 0x3A}, {0xD606, 0x00}, 
    {0xD607, 0x4A}, {0xD608, 0x00}, {0xD609, 0x5C}, {0xD60A, 0x00}, 
    {0xD60B, 0x81}, {0xD60C, 0x00}, {0xD60D, 0xA6}, {0xD60E, 0x00}, 
    {0xD60F, 0xE5}, {0xD610, 0x01}, {0xD611, 0x13}, {0xD612, 0x01}, 
    {0xD613, 0x54}, {0xD614, 0x01}, {0xD615, 0x82}, {0xD616, 0x01}, 
    {0xD617, 0xCA}, {0xD618, 0x02}, {0xD619, 0x00}, {0xD61A, 0x02}, 
    {0xD61B, 0x01}, {0xD61C, 0x02}, {0xD61D, 0x34}, {0xD61E, 0x02}, 
    {0xD61F, 0x67}, {0xD620, 0x02}, {0xD621, 0x84}, {0xD622, 0x02}, 
    {0xD623, 0xA4}, {0xD624, 0x02}, {0xD625, 0xB7}, {0xD626, 0x02}, 
    {0xD627, 0xCF}, {0xD628, 0x02}, {0xD629, 0xDE}, {0xD62A, 0x02}, 
    {0xD62B, 0xF2}, {0xD62C, 0x02}, {0xD62D, 0xFE}, {0xD62E, 0x03}, 
    {0xD62F, 0x10}, {0xD630, 0x03}, {0xD631, 0x33}, {0xD632, 0x03}, 
    {0xD633, 0x6D}, 
    //LV2 Page 0 enable
    {0xF000, 0x55}, {0xF001, 0xAA}, {0xF002, 0x52}, {0xF003, 0x08}, 
    {0xF004, 0x00}, 
    //Display control
    {0xB100,  0xCC}, {0xB101,  0x00}, 
    //Source hold time
    {0xB600, 0x05}, 
    //Gate EQ control
    {0xB700, 0x70}, {0xB701, 0x70}, 
    //Source EQ control (Mode 2)
    {0xB800, 0x01}, {0xB801, 0x03}, {0xB802, 0x03}, {0xB803, 0x03}, 
    //Inversion mode (2-dot)
    {0xBC00, 0x02}, {0xBC01, 0x00}, {0xBC02, 0x00}, 
    //Timing control 4H w/ 4-delay
    {0xC900, 0xD0}, {0xC901, 0x02}, {0xC902, 0x50}, {0xC903, 0x50}, 
    {0xC904, 0x50}, {0x3500, 0x00}, 
    //16-bit/pixel
    {0x3A00, 0x55},   
};


void LCD_SetDirection(uint8_t _dir)
{
    *lcd_ctrl.reg = 0x3600;     
    *lcd_ctrl.ram = _dir;
    *lcd_ctrl.reg = lcd_ctrl.set_x_cmd;
    *lcd_ctrl.ram = 0; 
    *lcd_ctrl.reg = lcd_ctrl.set_x_cmd + 1;
    *lcd_ctrl.ram = 0; 
    *lcd_ctrl.reg = lcd_ctrl.set_x_cmd + 2;
    *lcd_ctrl.ram = (lcd_ctrl.width - 1) >> 8; 
    *lcd_ctrl.reg = lcd_ctrl.set_x_cmd + 3;
    *lcd_ctrl.ram = (lcd_ctrl.width - 1) & 0XFF; 
    *lcd_ctrl.reg = lcd_ctrl.set_y_cmd;
    *lcd_ctrl.ram = 0; 
    *lcd_ctrl.reg = lcd_ctrl.set_y_cmd + 1;
    *lcd_ctrl.ram = 0; 
    *lcd_ctrl.reg = lcd_ctrl.set_y_cmd + 2;
    *lcd_ctrl.ram = (lcd_ctrl.hight - 1) >> 8; 
    *lcd_ctrl.reg = lcd_ctrl.set_y_cmd + 3;
    *lcd_ctrl.ram = (lcd_ctrl.hight - 1) & 0XFF;
}	

static void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    *lcd_ctrl.reg = lcd_ctrl.set_x_cmd;
    *lcd_ctrl.ram = Xpos >> 8; 		
    *lcd_ctrl.reg = lcd_ctrl.set_x_cmd + 1;
    *lcd_ctrl.ram = Xpos & 0XFF;			 
    *lcd_ctrl.reg = lcd_ctrl.set_y_cmd;
    *lcd_ctrl.ram = Ypos >> 8;  		
    *lcd_ctrl.reg = lcd_ctrl.set_y_cmd + 1;
    *lcd_ctrl.ram = Ypos & 0XFF;			
}

/*
*********************************************************************************************************
*	函 数 名: LCD_InitHard
*	功能说明: 初始化LCD
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitLcd(void)
{
    InitHardLcd();		/* 配置lcd的硬件参数 */
}

/*
*********************************************************************************************************
*	函 数 名: HAL_SRAM_MspInit
*	功能说明: 配置lcd的硬件参数
*	形    参: hsram
*	返 回 值: 无
*********************************************************************************************************
*/
void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_FSMC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |
                          GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
                          GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
                          GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_12;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

uint16_t id = 0;
/*
*********************************************************************************************************
*	函 数 名: InitHardLcd
*	功能说明: 配置lcd的硬件参数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void InitHardLcd(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    FSMC_NORSRAM_TimingTypeDef FSMC_R_Tim;
    FSMC_NORSRAM_TimingTypeDef FSMC_W_Tim;

	FONT_T tFont16;			/* 定义一个字体结构体变量，用于设置字体参数 */

	/* 设置字体参数 */
	{
		tFont16.FontCode = FC_ST_16;	/* 字体代码 16点阵 */
		tFont16.FrontColor = CL_BLACK;		/* 字体颜色 0 或 1 */
		tFont16.BackColor = CL_WHITE;	/* 文字背景颜色 */
		tFont16.Space = 0;			/* 文字间距，单位 = 像素 */
	}

    /* 背光灯 */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    SRAM_HandleStruct.Instance                  = FSMC_NORSRAM_DEVICE;              
    SRAM_HandleStruct.Extended                  = FSMC_NORSRAM_EXTENDED_DEVICE;     
    SRAM_HandleStruct.Init.NSBank               = FSMC_NORSRAM_BANK4;               //使用NE4
    SRAM_HandleStruct.Init.DataAddressMux       = FSMC_DATA_ADDRESS_MUX_DISABLE;    //地址/数据线不复用
    SRAM_HandleStruct.Init.MemoryType           = FSMC_MEMORY_TYPE_SRAM;            //SRAM
    SRAM_HandleStruct.Init.MemoryDataWidth      = FSMC_NORSRAM_MEM_BUS_WIDTH_16;    //16位数据宽度
    SRAM_HandleStruct.Init.BurstAccessMode      = FSMC_BURST_ACCESS_MODE_DISABLE;   //是否使能突发访问,仅对同步突发存储器有效,此处未用到
    SRAM_HandleStruct.Init.WaitSignalPolarity   = FSMC_WAIT_SIGNAL_POLARITY_LOW;    //等待信号的极性,仅在突发模式访问下有用
    SRAM_HandleStruct.Init.WaitSignalActive     = FSMC_WAIT_TIMING_BEFORE_WS;       //存储器是在等待周期之前的一个时钟周期还是等待周期期间使能NWAIT
    SRAM_HandleStruct.Init.WriteOperation       = FSMC_WRITE_OPERATION_ENABLE;      //存储器写使能
    SRAM_HandleStruct.Init.WaitSignal           = FSMC_WAIT_SIGNAL_DISABLE;         //等待使能位,此处未用到
    SRAM_HandleStruct.Init.ExtendedMode         = FSMC_EXTENDED_MODE_ENABLE;        //读写使用不同的时序
    SRAM_HandleStruct.Init.AsynchronousWait     = FSMC_ASYNCHRONOUS_WAIT_DISABLE;   //是否使能同步传输模式下的等待信号,此处未用到
    SRAM_HandleStruct.Init.WriteBurst           = FSMC_WRITE_BURST_DISABLE;         //禁止突发写

    FSMC_R_Tim.AddressSetupTime         = 0x06; //地址建立时间（ADDSET）为7个HCLK 13.8ns*7=96.6ns
    FSMC_R_Tim.AddressHoldTime          = 0;
    FSMC_R_Tim.DataSetupTime            = 26;   //数据保存时间为27个HCLK	=13.8*27=372.6ns
    FSMC_R_Tim.AccessMode               = FSMC_ACCESS_MODE_A;
    FSMC_W_Tim.BusTurnAroundDuration    = 0;    //总线周转阶段持续时间为0，此变量不赋值的话会莫名其妙的自动修改为4。导致程序运行正常
    FSMC_W_Tim.AddressSetupTime         = 3;    //地址建立时间（ADDSET）为4个HCLK =55.2ns 
    FSMC_W_Tim.AddressHoldTime          = 0;
    FSMC_W_Tim.DataSetupTime            = 0x06; //数据保存时间为13.8ns*7个HCLK=96.6ns
    FSMC_W_Tim.AccessMode               = FSMC_ACCESS_MODE_A;
    HAL_SRAM_Init(&SRAM_HandleStruct, &FSMC_R_Tim, &FSMC_W_Tim);

	HAL_Delay(50); // delay 50 ms 

    for (int i = 0; i < sizeof(lcd_cmd); i++)
    {
        *lcd_ctrl.reg = lcd_cmd[i].reg;
        *lcd_ctrl.ram = lcd_cmd[i].val;
    }
    *lcd_ctrl.reg = (0x1100);
    HAL_Delay(120);
    *lcd_ctrl.reg = (0x2900); 

    LCD_SetDirection(0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET);  //点亮背光
    LCD_ClrScr(CL_RED);
    LCD_DispStr(200, 400, "Touch Calibration", &tFont16);
}

/*
*********************************************************************************************************
*	函 数 名: LCD_SetPwmBackLight
*	功能说明: 初始化控制LCD背景光的GPIO,配置为PWM模式。
*			当关闭背光时，将CPU IO设置为浮动输入模式（推荐设置为推挽输出，并驱动到低电平)；将TIM3关闭 省电
*	形    参:  _bright 亮度，0是灭，255是最亮
*	返 回 值: 无
*********************************************************************************************************
*/
static void LCD_SetPwmBackLight(uint8_t _bright)
{
	/* 背光有CPU输出PWM控制，PB0/TIM3_CH3/TIM8_CH2 */
	// bsp_SetTIMOutPWM(GPIOB, GPIO_PIN_0, TIM3, 3, 20000, (_bright * 10000) /255);
}

/*
*********************************************************************************************************
*	函 数 名: LCD_SetBackLight
*	功能说明: 初始化控制LCD背景光的GPIO,配置为PWM模式。
*			当关闭背光时，将CPU IO设置为浮动输入模式（推荐设置为推挽输出，并驱动到低电平)；将TIM3关闭 省电
*	形    参: _bright 亮度，0是灭，255是最亮
*	返 回 值: 无
*********************************************************************************************************
*/
void LCD_SetBackLight(uint8_t _bright)
{
	lcd_ctrl.brightness =  _bright;	/* 保存背光值 */

	LCD_SetPwmBackLight(lcd_ctrl.brightness);
}

/*
*********************************************************************************************************
*	函 数 名: LCD_GetBackLight
*	功能说明: 获得背光亮度参数
*	形    参: 无
*	返 回 值: 背光亮度参数
*********************************************************************************************************
*/
uint8_t LCD_GetBackLight(void)
{
	return lcd_ctrl.brightness;
}

/*
*********************************************************************************************************
*	函 数 名: LCD_GetChipDescribe
*	功能说明: 读取LCD驱动芯片的描述符号，用于显示
*	形    参: char *_str : 描述符字符串填入此缓冲区
*	返 回 值: 无
*********************************************************************************************************
*/
void LCD_GetChipDescribe(char *_str)
{	
    _str = CHIP_STR_5510;
}

/*
*********************************************************************************************************
*	函 数 名: LCD_GetHeight
*	功能说明: 读取LCD分辨率之高度
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
uint16_t LCD_GetHeight(void)
{
	return g_LcdHeight;
}

/*
*********************************************************************************************************
*	函 数 名: LCD_GetWidth
*	功能说明: 读取LCD分辨率之宽度
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
uint16_t LCD_GetWidth(void)
{
	return g_LcdWidth;
}


/*
*********************************************************************************************************
*	函 数 名: LCD_DispOn
*	功能说明: 打开显示
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void LCD_DispOn(void)
{
	;
}

/*
*********************************************************************************************************
*	函 数 名: LCD_DispOff
*	功能说明: 关闭显示
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void LCD_DispOff(void)
{
	;
}

/*
*********************************************************************************************************
*	函 数 名: LCD_ClrScr
*	功能说明: 根据输入的颜色值清屏
*	形    参: _usColor : 背景色
*	返 回 值: 无
*********************************************************************************************************
*/
void LCD_ClrScr(uint16_t _usColor)
{
	uint32_t index = 0;
	LCD_SetCursor(0x00,0x0000);			//设置光标位置 
    *lcd_ctrl.reg = lcd_ctrl.set_gram_cmd; 	  
	for(index = 0; index < (lcd_ctrl.width * lcd_ctrl.hight); index++)
	{
        *lcd_ctrl.ram = _usColor;
	} 
}

/*
*********************************************************************************************************
*	函 数 名: LCD_PutPixel
*	功能说明: 画1个像素
*	形    参:
*			_usX,_usY : 像素坐标
*			_usColor  : 像素颜色
*	返 回 值: 无
*********************************************************************************************************
*/
void LCD_PutPixel(uint16_t _usX, uint16_t _usY, uint16_t _usColor)
{
    *lcd_ctrl.reg = lcd_ctrl.set_x_cmd;
    *lcd_ctrl.ram = _usX >> 8;  
    *lcd_ctrl.reg = lcd_ctrl.set_x_cmd +1;
    *lcd_ctrl.ram = _usX & 0XFF;	  
    *lcd_ctrl.reg = lcd_ctrl.set_y_cmd;
    *lcd_ctrl.ram = _usY >> 8;  
    *lcd_ctrl.reg = lcd_ctrl.set_y_cmd + 1;
    *lcd_ctrl.ram = _usY & 0XFF; 
	 
	*lcd_ctrl.reg = lcd_ctrl.set_gram_cmd;
    *lcd_ctrl.ram = _usColor; 
}

/*
*********************************************************************************************************
*	函 数 名: LCD_GetFontWidth
*	功能说明: 读取字体的宽度（像素单位)
*	形    参:
*		_tFont : 字体结构体，包含颜色、背景色(支持透明)、字体代码、文字间距等参数
*	返 回 值: 字体的宽度（像素单位)
*********************************************************************************************************
*/
uint16_t LCD_GetFontWidth(FONT_T *_tFont)
{
	uint16_t font_width = 16;

	switch (_tFont->FontCode)
	{
		case FC_ST_12:
			font_width = 12;
			break;

		case FC_ST_16:
			font_width = 16;
			break;
			
		case FC_ST_24:
			font_width = 24;
			break;
			
		case FC_ST_32:
			font_width = 32;
			break;			
	}
	return font_width;
}

/*
*********************************************************************************************************
*	函 数 名: LCD_GetFontHeight
*	功能说明: 读取字体的高度（像素单位)
*	形    参:
*		_tFont : 字体结构体，包含颜色、背景色(支持透明)、字体代码、文字间距等参数
*	返 回 值: 字体的宽度（像素单位)
*********************************************************************************************************
*/
uint16_t LCD_GetFontHeight(FONT_T *_tFont)
{
	uint16_t height = 16;

	switch (_tFont->FontCode)
	{
		case FC_ST_12:
			height = 12;
			break;

		case FC_ST_16:
			height = 16;
			break;
			
		case FC_ST_24:
			height = 24;
			break;
			
		case FC_ST_32:
			height = 32;
			break;			
	}
	return height;
}

/*
*********************************************************************************************************
*	函 数 名: LCD_GetStrWidth
*	功能说明: 计算字符串宽度(像素单位)
*	形    参:
*		_ptr  : 字符串指针
*		_tFont : 字体结构体，包含颜色、背景色(支持透明)、字体代码、文字间距等参数
*	返 回 值: 无
*********************************************************************************************************
*/
uint16_t LCD_GetStrWidth(char *_ptr, FONT_T *_tFont)
{
	char *p = _ptr;
	uint16_t width = 0;
	uint8_t code1, code2;
	uint16_t font_width;

	font_width = LCD_GetFontWidth(_tFont);

	while (*p != 0)
	{
		code1 = *p;	/* 读取字符串数据， 该数据可能是ascii代码，也可能汉字代码的高字节 */
		if (code1 < 0x80)	/* ASCII */
		{
			switch(_tFont->FontCode)
			{
				case FC_ST_12:
					font_width = 6;
					break;

				case FC_ST_16:		
					font_width = 8;
					break;
					
				case FC_ST_24:			
					font_width = 12;
					break;
					
				case FC_ST_32:
					font_width = 16;
					break;
				
				default:
					font_width = 8;
					break;					
			}
			
		}
		else	/* 汉字 */
		{
			code2 = *++p;
			if (code2 == 0)
			{
				break;
			}
			font_width = LCD_GetFontWidth(_tFont);
			
		}
		width += font_width;
		p++;
	}

	return width;
}

/*
*********************************************************************************************************
*	函 数 名: LCD_Fill_Rect
*	功能说明: 用一个颜色值填充一个矩形。【emWin 中有同名函数 LCD_FillRect，因此加了下划线区分】
*	形    参:
*			_usX,_usY: 矩形左上角的坐标
*			_usHeight : 矩形的高度
*			_usWidth  : 矩形的宽度
*	返 回 值: 无
*********************************************************************************************************
*/
void LCD_Fill_Rect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor)
{
	uint16_t height,width;
	uint16_t i,j; 
	width=_usWidth-_usX+1; 			//得到填充的宽度
	height=_usHeight -_usY+1;			//高度
	for(i=0;i<height;i++)
	{
		LCD_SetCursor(_usX,_usY+i);   	//设置光标位置 
		// LCD_WriteRAM_Prepare();     //开始写入GRAM
        *lcd_ctrl.reg = lcd_ctrl.set_gram_cmd;
		for(j=0;j<width;j++)
        {
            // LCD->LCD_RAM=color[i*width+j];//写入数据 
            *lcd_ctrl.ram = _usColor;
        }
	}     
}

/*
*********************************************************************************************************
*	函 数 名: _LCD_ReadAsciiDot
*	功能说明: 读取1个ASCII字符的点阵数据
*	形    参:
*		_code : ASCII字符的编码，1字节。1-128
*		_fontcode ：字体代码
*		_pBuf : 存放读出的字符点阵数据
*	返 回 值: 文字宽度
*********************************************************************************************************
*/
static void _LCD_ReadAsciiDot(uint8_t _code, uint8_t _fontcode, uint8_t *_pBuf)
{
	const uint8_t *pAscDot;
	uint8_t font_bytes = 0;

	pAscDot = 0;
	switch (_fontcode)
	{
		case FC_ST_12:		/* 12点阵 */
			font_bytes = 24;
			pAscDot = g_Ascii12;	
			break;
		
		case FC_ST_24:
		case FC_ST_32:
		case FC_ST_16:
			/* 缺省是16点阵 */
			font_bytes = 32;
			pAscDot = g_Ascii16;
			break;
		
		default:
			return;
	}	

	/* 将CPU内部Flash中的ascii字符点阵复制到buf */
	memcpy(_pBuf, &pAscDot[_code * (font_bytes / 2)], (font_bytes / 2));	
}

/*
*********************************************************************************************************
*	函 数 名: LCD_DispStrEx
*	功能说明: 在LCD指定坐标（左上角）显示一个字符串。 增强型函数。支持左\中\右对齐，支持定长清屏。
*	形    参:
*		_usX : X坐标
*		_usY : Y坐标
*		_ptr  : 字符串指针
*		_tFont : 字体结构体，包含颜色、背景色(支持透明)、字体代码、文字间距等参数。可以指定RA8875字库显示汉字
*		_Width : 字符串显示区域的宽度. 0 表示不处理留白区域，此时_Align无效
*		_Align :字符串在显示区域的对齐方式，
*				ALIGN_LEFT = 0,
*				ALIGN_CENTER = 1,
*				ALIGN_RIGHT = 2
*	返 回 值: 无
*********************************************************************************************************
*/
void LCD_DispStrEx(uint16_t _usX, uint16_t _usY, char *_ptr, FONT_T *_tFont, uint16_t _Width,
	uint8_t _Align)
{
	uint32_t i;
	uint8_t code1;
	uint8_t code2;
	uint8_t buf[32 * 32 / 8];	/* 最大支持24点阵汉字 */
	uint8_t width;
	uint16_t m;
	uint8_t font_width = 0;
	uint8_t font_height = 0;
	uint16_t x, y;
	uint16_t offset;
	uint16_t str_width;	/* 字符串实际宽度  */

	switch (_tFont->FontCode)
	{
		case FC_ST_12:		/* 12点阵 */
			font_height = 12;
			font_width = 12;
			break;
		
		case FC_ST_16:
			font_height = 16;
			font_width = 16;
			break;

		case FC_ST_24:
			font_height = 24;
			font_width = 24;
			break;
						
		case FC_ST_32:	
			font_height = 32;
			font_width = 32;
			break;	
		
		default:
			break;
	}
	
	str_width = LCD_GetStrWidth(_ptr, _tFont);	/* 计算字符串实际宽度(RA8875内部ASCII点阵宽度为变长 */
	offset = 0;
	if (_Width > str_width)
	{
		if (_Align == ALIGN_RIGHT)	/* 右对齐 */
		{
			offset = _Width - str_width;
		}
		else if (_Align == ALIGN_CENTER)	/* 左对齐 */
		{
			offset = (_Width - str_width) / 2;
		}
		else	/* 左对齐 ALIGN_LEFT */
		{
			;
		}
	}

	/* 左侧填背景色, 中间对齐和右边对齐  */
	if (offset > 0)
	{
		LCD_Fill_Rect(_usX, _usY, LCD_GetFontHeight(_tFont), offset,  _tFont->BackColor);
		_usX += offset;
	}
	
	/* 右侧填背景色 */
	if (_Width > str_width)
	{
		LCD_Fill_Rect(_usX + str_width, _usY, LCD_GetFontHeight(_tFont), _Width - str_width - offset,  _tFont->BackColor);
	}
	
	/* 使用CPU内部字库. 点阵信息由CPU读取 */
	{
		/* 开始循环处理字符 */
		while (*_ptr != 0)
		{
			code1 = *_ptr;	/* 读取字符串数据， 该数据可能是ascii代码，也可能汉字代码的高字节 */
			if (code1 < 0x80)
			{
				/* 将ascii字符点阵复制到buf */
				//memcpy(buf, &pAscDot[code1 * (font_bytes / 2)], (font_bytes / 2));
				_LCD_ReadAsciiDot(code1, _tFont->FontCode, buf);	/* 读取ASCII字符点阵 */
				width = font_width / 2;
			}
			else
			{
				code2 = *++_ptr;
				if (code2 == 0)
				{
					break;
				}
				/* 读1个汉字的点阵 */
				// _LCD_ReadHZDot(code1, code2, _tFont->FontCode, buf);
				width = font_width;
			}
	
			y = _usY;
			/* 开始刷LCD */
			for (m = 0; m < font_height; m++)	/* 字符高度 */
			{
				x = _usX;
				for (i = 0; i < width; i++)	/* 字符宽度 */
				{
					if ((buf[m * ((2 * width) / font_width) + i / 8] & (0x80 >> (i % 8 ))) != 0x00)
					{
						LCD_PutPixel(x, y, _tFont->FrontColor);	/* 设置像素颜色为文字色 */
					}
					else
					{
						if (_tFont->BackColor != CL_MASK)	/* 透明色 */
						{
							LCD_PutPixel(x, y, _tFont->BackColor);	/* 设置像素颜色为文字背景色 */
						}
					}
	
					x++;
				}
				y++;
			}
	
			if (_tFont->Space > 0)
			{
				/* 如果文字底色按_tFont->usBackColor，并且字间距大于点阵的宽度，那么需要在文字之间填充(暂时未实现) */
			}
			_usX += width + _tFont->Space;	/* 列地址递增 */
			_ptr++;			/* 指向下一个字符 */
		}
	}
}

/*
*********************************************************************************************************
*	函 数 名: LCD_DispStr
*	功能说明: 在LCD指定坐标（左上角）显示一个字符串
*	形    参:
*		_usX : X坐标
*		_usY : Y坐标
*		_ptr  : 字符串指针
*		_tFont : 字体结构体，包含颜色、背景色(支持透明)、字体代码、文字间距等参数
*	返 回 值: 无
*********************************************************************************************************
*/
void LCD_DispStr(uint16_t _usX, uint16_t _usY, char *_ptr, FONT_T *_tFont)
{
    LCD_DispStrEx(_usX, _usY, _ptr, _tFont, 0, 0);
}
