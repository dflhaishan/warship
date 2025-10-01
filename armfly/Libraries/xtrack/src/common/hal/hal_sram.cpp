#include "hal.h"
#include "stm32f1xx_ll_fsmc.h"

static SRAM_HandleTypeDef Extern_SRAM_HandleStruct;

void HAL::ExternSram_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    FSMC_NORSRAM_TimingTypeDef FSMC_R_W_Tim;

    __HAL_RCC_FSMC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 |
                          GPIO_PIN_4 | GPIO_PIN_5 |
                          GPIO_PIN_8 | GPIO_PIN_9 |
                          GPIO_PIN_10 | GPIO_PIN_11 |
                          GPIO_PIN_12 | GPIO_PIN_13 |
                          GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 |
                          GPIO_PIN_7 | GPIO_PIN_8 |
                          GPIO_PIN_9 | GPIO_PIN_10 |
                          GPIO_PIN_11 | GPIO_PIN_12 |
                          GPIO_PIN_13 | GPIO_PIN_14 |
                          GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 |
                          GPIO_PIN_2 | GPIO_PIN_3 |
                          GPIO_PIN_4 | GPIO_PIN_5 | 
                          GPIO_PIN_12 | GPIO_PIN_13 |
                          GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 |
                          GPIO_PIN_2 | GPIO_PIN_3 |
                          GPIO_PIN_4 | GPIO_PIN_5 |
                          GPIO_PIN_10;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
    
    Extern_SRAM_HandleStruct.Instance                  = FSMC_NORSRAM_DEVICE;              
    Extern_SRAM_HandleStruct.Extended                  = FSMC_NORSRAM_EXTENDED_DEVICE;     
    Extern_SRAM_HandleStruct.Init.NSBank               = FSMC_NORSRAM_BANK3;               //使用NE3
    Extern_SRAM_HandleStruct.Init.DataAddressMux       = FSMC_DATA_ADDRESS_MUX_DISABLE;    //地址/数据线不复用
    Extern_SRAM_HandleStruct.Init.MemoryType           = FSMC_MEMORY_TYPE_SRAM;            //SRAM
    Extern_SRAM_HandleStruct.Init.MemoryDataWidth      = FSMC_NORSRAM_MEM_BUS_WIDTH_16;    //16位数据宽度
    Extern_SRAM_HandleStruct.Init.BurstAccessMode      = FSMC_BURST_ACCESS_MODE_DISABLE;   //是否使能突发访问,仅对同步突发存储器有效,此处未用到
    Extern_SRAM_HandleStruct.Init.WaitSignalPolarity   = FSMC_WAIT_SIGNAL_POLARITY_LOW;    //等待信号的极性,仅在突发模式访问下有用
    Extern_SRAM_HandleStruct.Init.WaitSignalActive     = FSMC_WAIT_TIMING_BEFORE_WS;       //存储器是在等待周期之前的一个时钟周期还是等待周期期间使能NWAIT
    Extern_SRAM_HandleStruct.Init.WriteOperation       = FSMC_WRITE_OPERATION_ENABLE;      //存储器写使能
    Extern_SRAM_HandleStruct.Init.WaitSignal           = FSMC_WAIT_SIGNAL_DISABLE;         //等待使能位,此处未用到
    Extern_SRAM_HandleStruct.Init.ExtendedMode         = FSMC_EXTENDED_MODE_DISABLE;        //读写使用相同的时序
    Extern_SRAM_HandleStruct.Init.AsynchronousWait     = FSMC_ASYNCHRONOUS_WAIT_DISABLE;   //是否使能同步传输模式下的等待信号,此处未用到
    Extern_SRAM_HandleStruct.Init.WriteBurst           = FSMC_WRITE_BURST_DISABLE;         //禁止突发写

    FSMC_R_W_Tim.AddressSetupTime = 0x00;
    FSMC_R_W_Tim.AddressHoldTime = 0x00;
    FSMC_R_W_Tim.DataSetupTime = 0x01;
    FSMC_R_W_Tim.BusTurnAroundDuration = 0x00;
    FSMC_R_W_Tim.AccessMode = FSMC_ACCESS_MODE_A;
    HAL_SRAM_Init(&Extern_SRAM_HandleStruct, &FSMC_R_W_Tim, &FSMC_R_W_Tim);
}