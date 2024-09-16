C_SOURCES +=  \
${ARMFLY}/RTOS/FreeRTOS/Source/croutine.c \
${ARMFLY}/RTOS/FreeRTOS/Source/event_groups.c \
${ARMFLY}/RTOS/FreeRTOS/Source/list.c \
${ARMFLY}/RTOS/FreeRTOS/Source/queue.c \
${ARMFLY}/RTOS/FreeRTOS/Source/stream_buffer.c \
${ARMFLY}/RTOS/FreeRTOS/Source/tasks.c \
${ARMFLY}/RTOS/FreeRTOS/Source/timers.c \
${ARMFLY}/RTOS/FreeRTOS/Source/freertos.c \
${ARMFLY}/RTOS/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c \
${ARMFLY}/RTOS/FreeRTOS/Source/portable/MemMang/heap_4.c \
${ARMFLY}/RTOS/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c

C_INCLUDES +=  \
-I${ARMFLY}/RTOS/FreeRTOS/Source/include \
-I${ARMFLY}/RTOS/FreeRTOS/Source/CMSIS_RTOS \
-I${ARMFLY}/RTOS/FreeRTOS/Source/portable/GCC/ARM_CM3