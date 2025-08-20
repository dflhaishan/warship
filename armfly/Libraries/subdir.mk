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
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_adc.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_crc.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_dac.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_dma.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_exti.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_gpio.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_i2c.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_pwr.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_rcc.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_rtc.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_sdmmc.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_spi.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_tim.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usart.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usb.c \
${ARMFLY}/Libraries/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_utils.c \
$(shell find ${ARMFLY}/Libraries/lvgl/src/ -type f -name '*.c') \
$(shell find ${ARMFLY}/Libraries/xtrack/src/ -type f -name '*.c') \
${ARMFLY}/Libraries/cm_backtrace/cm_backtrace.c \
${ARMFLY}/Libraries/arduino_core/board.c \
${ARMFLY}/Libraries/arduino_core/core_debug.c \
${ARMFLY}/Libraries/arduino_core/hooks.c \
${ARMFLY}/Libraries/arduino_core/itoa.c \
${ARMFLY}/Libraries/arduino_core/pins_arduino.c \
${ARMFLY}/Libraries/arduino_core/wiring_analog.c \
${ARMFLY}/Libraries/arduino_core/wiring_digital.c \
${ARMFLY}/Libraries/arduino_core/wiring_shift.c \
${ARMFLY}/Libraries/arduino_core/wiring_time.c \
${ARMFLY}/Libraries/arduino_core/avr/dtostrf.c \
${ARMFLY}/Libraries/arduino_core/variants/STM32F1xx/F103ZC_D_E_H_T/generic_clock.c \
${ARMFLY}/Libraries/arduino_core/variants/STM32F1xx/F103ZC_D_E_H-T/PeripheralPins.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/bootloader.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/clock.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/core_callback.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/dwt.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/hw_config.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/interrupt.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/otp.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/pinmap.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/PortNames.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/stm32_def.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/timer.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/uart.c \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/syscalls.c

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
-I${ARMFLY}/Libraries/xtrack/src/common/music \
-I${ARMFLY}/Libraries/cm_backtrace/ \
-I${ARMFLY}/Libraries/cm_backtrace/languages/ \
-I${ARMFLY}/Libraries/arduino_core/ \
-I${ARMFLY}/Libraries/arduino_core/avr \
-I${ARMFLY}/Libraries/arduino_core/variants/STM32F1xx/F103ZC_D_E_H_T \
-I${ARMFLY}/Libraries/arduino_core/srcwrapper/inc

ASMM_SOURCES += \
$(shell find ${ARMFLY}/Libraries/lvgl/src -type f -name '*.S') \
$(shell find ${ARMFLY}/Libraries/cm_backtrace/fault_handler/gcc -type f -name '*.S')

AS_INCLUDES += \
-I${ARMFLY}/Libraries/lvgl

CPP_SOURCES += \
$(shell find ${ARMFLY}/Libraries/lvgl/src/ -type f -name '*.cpp') \
$(shell find ${ARMFLY}/Libraries/xtrack/src/ -type f -name '*.cpp') \
${ARMFLY}/Libraries/arduino_core/abi.cpp \
${ARMFLY}/Libraries/arduino_core/HardwareSerial.cpp \
${ARMFLY}/Libraries/arduino_core/WMath.cpp \
${ARMFLY}/Libraries/arduino_core/WSerial.cpp \
${ARMFLY}/Libraries/arduino_core/WString.cpp \
${ARMFLY}/Libraries/arduino_core/Print.cpp \
${ARMFLY}/Libraries/arduino_core/RingBuffer.cpp \
${ARMFLY}/Libraries/arduino_core/Stream.cpp \
${ARMFLY}/Libraries/arduino_core/Tone.cpp \
${ARMFLY}/Libraries/arduino_core/WInterrupts.cpp \
${ARMFLY}/Libraries/arduino_core/IPAddress.cpp \
${ARMFLY}/Libraries/arduino_core/wiring_pulse.cpp \
${ARMFLY}/Libraries/arduino_core/variants/STM32F1xx/F103ZC_D_E_H_T/variant_generic.cpp \
${ARMFLY}/Libraries/arduino_core/variants/STM32F1xx/F103ZC_D_E_H_T/variant_VCCGND_F103ZET6_XXX.cpp \
${ARMFLY}/Libraries/arduino_core/srcwrapper/src/analog.cpp