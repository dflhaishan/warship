C_SOURCES +=  \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_msp.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sram.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_nor.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.c \
$(shell find ${ARMFLY}/Libraries/lvgl/ -type f -name '*.c')

C_INCLUDES +=  \
-I${ARMFLY}/Libraries/CMSIS/Device/ST/STM32F1xx/Include \
-I${ARMFLY}/Libraries/CMSIS/Include \
-I${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Inc/Legacy \
-I${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Inc \
-I${ARMFLY}/Libraries/lvgl

ASMM_SOURCES += \
$(shell find ${ARMFLY}/Libraries/lvgl/ -type f -name '*.S')

AS_INCLUDES += \
-I${ARMFLY}/Libraries/lvgl

CPP_SOURCES += \
$(shell find ${ARMFLY}/Libraries/lvgl/ -type f -name '*.cpp')