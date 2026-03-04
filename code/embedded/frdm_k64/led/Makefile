########################################
# Project
########################################

TARGET      := blink
BUILD_DIR   := build
SRC_DIR     := src

########################################
# SDK path (AJUSTA SI ES NECESARIO)
########################################

SDK_PATH := ../SDK_2_11_0_FRDM-K64F

########################################
# Toolchain
########################################

PREFIX  := arm-none-eabi-

CC      := $(PREFIX)gcc
AS      := $(PREFIX)gcc
OBJCOPY := $(PREFIX)objcopy
SIZE    := $(PREFIX)size

########################################
# CPU configuration
########################################

CPU := -mcpu=cortex-m4
CPU += -mthumb
CPU += -mfpu=fpv4-sp-d16
CPU += -mfloat-abi=hard

########################################
# Compiler flags
########################################

CFLAGS := $(CPU)

CFLAGS += -DCPU_MK64FN1M0VLL12

CFLAGS += -O0
CFLAGS += -g3

CFLAGS += -Wall
CFLAGS += -Wextra

CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections

CFLAGS += -std=c11

########################################
# Linker flags
########################################

LDSCRIPT := $(SDK_PATH)/devices/MK64F12/gcc/MK64FN1M0xxx12_flash.ld

LDFLAGS := $(CPU)

LDFLAGS += -T$(LDSCRIPT)

LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

# CRITICO
LDFLAGS += --specs=nano.specs
LDFLAGS += --specs=nosys.specs


########################################
# Includes
########################################

INCLUDES :=

INCLUDES += -I$(SDK_PATH)/CMSIS/Include
INCLUDES += -I$(SDK_PATH)/CMSIS/Core/Include

INCLUDES += -I$(SDK_PATH)/devices/MK64F12
INCLUDES += -I$(SDK_PATH)/devices/MK64F12/include

INCLUDES += -I$(SDK_PATH)/drivers
INCLUDES += -I$(SDK_PATH)/devices/MK64F12/drivers

INCLUDES += -I$(SRC_DIR)

########################################
# Sources
########################################

C_SOURCES :=

C_SOURCES += $(SRC_DIR)/main.c

C_SOURCES += $(SDK_PATH)/devices/MK64F12/system_MK64F12.c

C_SOURCES += $(SDK_PATH)/devices/MK64F12/drivers/fsl_gpio.c
C_SOURCES += $(SDK_PATH)/devices/MK64F12/drivers/fsl_clock.c

ASM_SOURCES :=

ASM_SOURCES += $(SDK_PATH)/devices/MK64F12/gcc/startup_MK64F12.S
########################################
# Objects
########################################

C_OBJECTS := $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
ASM_OBJECTS := $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))

OBJECTS := $(C_OBJECTS) $(ASM_OBJECTS)

########################################
# Default target
########################################

all: $(BUILD_DIR)/$(TARGET).elf

########################################
# Link
########################################

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)

	mkdir -p $(BUILD_DIR)

	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

	$(SIZE) $@

########################################
# Compile C
########################################

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c

	mkdir -p $(BUILD_DIR)

	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/system_MK64F12.o:

	mkdir -p $(BUILD_DIR)

	$(CC) $(CFLAGS) $(INCLUDES) -c \
	$(SDK_PATH)/devices/MK64F12/system_MK64F12.c \
	-o $@

$(BUILD_DIR)/fsl_gpio.o:

	mkdir -p $(BUILD_DIR)

	$(CC) $(CFLAGS) $(INCLUDES) -c \
	$(SDK_PATH)/devices/MK64F12/drivers/fsl_gpio.c \
	-o $@

$(BUILD_DIR)/fsl_clock.o:

	mkdir -p $(BUILD_DIR)

	$(CC) $(CFLAGS) $(INCLUDES) -c \
	$(SDK_PATH)/devices/MK64F12/drivers/fsl_clock.c \
	-o $@

########################################
# Compile ASM
########################################

$(BUILD_DIR)/startup_MK64F12.o:

	mkdir -p $(BUILD_DIR)

	$(AS) $(CFLAGS) -c \
	$(SDK_PATH)/devices/MK64F12/gcc/startup_MK64F12.S \
	-o $@

########################################
# Binary
########################################

bin: all

	$(OBJCOPY) -O binary \
	$(BUILD_DIR)/$(TARGET).elf \
	$(BUILD_DIR)/$(TARGET).bin

########################################
# Clean
########################################

clean:

	rm -rf $(BUILD_DIR)

########################################
# Flash (OpenSDA MSD method)
########################################

flash: bin

	cp $(BUILD_DIR)/$(TARGET).bin /media/$(USER)/DAPLINK/

########################################
# Debug info
########################################

size:

	$(SIZE) $(BUILD_DIR)/$(TARGET).elf

########################################
# Phony
########################################

.PHONY: all clean bin flash size

