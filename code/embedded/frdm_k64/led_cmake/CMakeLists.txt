cmake_minimum_required(VERSION 3.20)
project(blink_led C ASM)

# =====================================
# Toolchain
# =====================================
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)

# =====================================
# CPU flags
# =====================================
set(CPU_FLAGS
    -mcpu=cortex-m4
    -mthumb
)

set(FPU_FLAGS
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

# =====================================
# Fuentes
# =====================================

set(SOURCES
    src/main.c
    ../SDK_2_11_0_FRDM-K64F/devices/MK64F12/system_MK64F12.c
    ../SDK_2_11_0_FRDM-K64F/devices/MK64F12/gcc/startup_MK64F12.S
    ../SDK_2_11_0_FRDM-K64F/devices/MK64F12/drivers/fsl_gpio.c
    ../SDK_2_11_0_FRDM-K64F/devices/MK64F12/drivers/fsl_clock.c
)

# =====================================
# Target
# =====================================
add_executable(blink.elf ${SOURCES})

# =====================================
# Compile options (CORRECTO)
# =====================================
target_compile_options(blink.elf PRIVATE
    ${CPU_FLAGS}
    ${FPU_FLAGS}
    -O0
    -g
    -Wall
    -std=c11
)

# Definiciones (equivalente a -DCPU_MK64FN1M0VLL12)
target_compile_definitions(blink.elf PRIVATE
    CPU_MK64FN1M0VLL12
)

# =====================================
# Includes (por target)
# =====================================
target_include_directories(blink.elf PRIVATE
    src
    ../SDK_2_11_0_FRDM-K64F/devices/MK64F12
    ../SDK_2_11_0_FRDM-K64F/devices/MK64F12/drivers
    ../SDK_2_11_0_FRDM-K64F/CMSIS/Core/Include
)
# =====================================
# Linker
# =====================================
target_link_options(blink.elf PRIVATE
    ${CPU_FLAGS}
    ${FPU_FLAGS}
    -T ../MK64FN1M0xxx12_flash.ld
    --specs=nano.specs
    --specs=nosys.specs
    -Wl,-Map=blink.map
)
# =====================================
# Post build
# =====================================
add_custom_command(TARGET blink.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary blink.elf blink.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex   blink.elf blink.hex
    COMMENT "Generating BIN and HEX files"
)