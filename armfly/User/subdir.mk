C_SOURCES +=  \
${ARMFLY}/User/main.c \
${ARMFLY}/User/libutilies.c \
${ARMFLY}/User/bsp/stm32f1xx_it.c \
${ARMFLY}/User/bsp/system_stm32f1xx.c \
${ARMFLY}/User/bsp/bsp.c \
${ARMFLY}/User/bsp/src/bsp_uart_fifo.c \
${ARMFLY}/User/bsp/src/bsp_led.c \
${ARMFLY}/User/bsp/src/bsp_tft_lcd.c \
${ARMFLY}/User/fonts/src/asc12.c \
${ARMFLY}/User/fonts/src/asc16.c \
${ARMFLY}/User/fonts/src/asc24.c \
${ARMFLY}/User/fonts/src/asc32.c

C_INCLUDES +=  \
-I${ARMFLY}/User \
-I${ARMFLY}/User/bsp \
-I${ARMFLY}/User/bsp/inc \
-I${ARMFLY}/User/fonts/inc

AS_INCLUDES +=  \
-I${ARMFLY}/User/