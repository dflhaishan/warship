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
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c

C_INCLUDES +=  \
-I${ARMFLY}/Libraries/CMSIS/Device/ST/STM32F1xx/Include \
-I${ARMFLY}/Libraries/CMSIS/Include \
-I${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Inc/Legacy \
-I${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Inc