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
$(shell find ${ARMFLY}/Libraries/lvgl/src/ -type f -name '*.c') \
$(shell find ${ARMFLY}/Libraries/xtrack/src/ -type f -name '*.c')

C_INCLUDES +=  \
-I${ARMFLY}/Libraries/CMSIS/Device/ST/STM32F1xx/Include \
-I${ARMFLY}/Libraries/CMSIS/Include \
-I${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Inc/Legacy \
-I${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Inc \
-I${ARMFLY}/Libraries/lvgl \
-I${ARMFLY}/Libraries/xtrack/inc \
-I${ARMFLY}/Libraries/xtrack/src/pages/ \
-I${ARMFLY}/Libraries/xtrack/src/pages/dialplate \
-I${ARMFLY}/Libraries/xtrack/src/pages/livemap \
-I${ARMFLY}/Libraries/xtrack/src/pages/startup \
-I${ARMFLY}/Libraries/xtrack/src/pages/statusbar \
-I${ARMFLY}/Libraries/xtrack/src/pages/systeminfos \
-I${ARMFLY}/Libraries/xtrack/src/pages/template \
-I${ARMFLY}/Libraries/xtrack/src/resources \
-I${ARMFLY}/Libraries/xtrack/src/resources/font \
-I${ARMFLY}/Libraries/xtrack/src/utils/millistaskmanager \
-I${ARMFLY}/Libraries/xtrack/src/utils/pagemanager \
-I${ARMFLY}/Libraries/xtrack/src/utils/datacenter \
-I${ARMFLY}/Libraries/xtrack/src/utils/arduinojson \
-I${ARMFLY}/Libraries/xtrack/src/utils/filters \
-I${ARMFLY}/Libraries/xtrack/src/utils/gpx \
-I${ARMFLY}/Libraries/xtrack/src/utils/gpx_parser \
-I${ARMFLY}/Libraries/xtrack/src/utils/mapconv \
-I${ARMFLY}/Libraries/xtrack/src/utils/pointcontainer \
-I${ARMFLY}/Libraries/xtrack/src/utils/storageservice \
-I${ARMFLY}/Libraries/xtrack/src/utils/stream \
-I${ARMFLY}/Libraries/xtrack/src/utils/time \
-I${ARMFLY}/Libraries/xtrack/src/utils/tone \
-I${ARMFLY}/Libraries/xtrack/src/utils/trackfilter \
-I${ARMFLY}/Libraries/xtrack/src/utils/wstring \
-I${ARMFLY}/Libraries/xtrack/src/utils/tinygps \
-I${ARMFLY}/Libraries/xtrack/src/utils/arduinoapi \
-I${ARMFLY}/Libraries/xtrack/src/utils/lv_ext \
-I${ARMFLY}/Libraries/xtrack/src/utils/lv_poly_line \
-I${ARMFLY}/Libraries/xtrack/src/utils/tileconv \
-I${ARMFLY}/Libraries/xtrack/src/common/dataproc \
-I${ARMFLY}/Libraries/xtrack/src/common/hal \
-I${ARMFLY}/Libraries/xtrack/src/common/music

ASMM_SOURCES += \
$(shell find ${ARMFLY}/Libraries/lvgl/src -type f -name '*.S')

AS_INCLUDES += \
-I${ARMFLY}/Libraries/lvgl

CPP_SOURCES += \
$(shell find ${ARMFLY}/Libraries/lvgl/src/ -type f -name '*.cpp') \
$(shell find ${ARMFLY}/Libraries/xtrack/src/ -type f -name '*.cpp')