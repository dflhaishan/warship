C_SOURCES +=  \
${ARMFLY}/User/main.c \
${ARMFLY}/User/bsp/stm32f1xx_it.c \
${ARMFLY}/User/bsp/system_stm32f1xx.c \

C_INCLUDES +=  \
-I${ARMFLY}/User \
-I${ARMFLY}/User/bsp \
-I${ARMFLY}/User/lv_port

AS_INCLUDES +=  \
-I${ARMFLY}/User/

CPP_SOURCES += \
${ARMFLY}/User/lv_port/lv_port_disp.cpp \
${ARMFLY}/User/lv_port/lv_port_fs_sdfat.cpp \
${ARMFLY}/User/lv_port/lv_port_indev.cpp \
${ARMFLY}/User/lv_port/lv_port.cpp
