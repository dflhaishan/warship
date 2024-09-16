C_SOURCES +=  \
${ARMFLY}/User/main.c \
${ARMFLY}/User/libutilies.c \
${ARMFLY}/User/bsp/stm32f1xx_it.c \
${ARMFLY}/User/bsp/system_stm32f1xx.c

C_INCLUDES +=  \
-I${ARMFLY}/User \
-I${ARMFLY}/User/bsp \
-I${ARMFLY}/User/bsp/inc

AS_INCLUDES +=  \
-I${ARMFLY}/User/