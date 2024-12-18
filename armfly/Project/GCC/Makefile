##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [4.2.0-B44] date: [Mon Sep 16 00:48:13 CST 2024]
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = app


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# armfly path
ARMFLY = ../..
# Build path
BUILD_DIR = ${ARMFLY}/build

######################################
# source
######################################
# C sources
C_SOURCES =

# ASM sources
ASM_SOURCES =  \
startup_stm32f103xe.s

# ASM sources
ASMM_SOURCES = 

# CPP source
CPP_SOURCES =

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES = 

include ${ARMFLY}/Libraries/subdir.mk
include ${ARMFLY}/RTOS/FreeRTOS/Source/subdir.mk
include ${ARMFLY}/User/subdir.mk

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
GCC_PATH = ${ARMFLY}/tools/toolchain/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi/bin
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F103xE

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = stm32f103zetx.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections,--no-warn-rwx-segments

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASMM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASMM_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo building file: $<
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@echo building file: $<
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.pp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@echo building file: $<
	@$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	@echo building file: $<
	@$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@echo creating target: $@
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo creating target: $@
	@$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo creating target: $@
	@$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***