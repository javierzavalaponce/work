[ CMake y configuración ] 🟦
┌─────────────────────────────────────────────┐
│ CMakeLists.txt      ← define target ELF     │
│ config.cmake        ← toolchain & paths    │
│ flags.cmake         ← compiler/linker flags│
└─────────────────────────────────────────────┘
                     │ cmake generates Makefiles / Ninja
                     ▼
[ Compilación de fuentes ] 🟩
┌─────────────────────────────────────────────┐
│ freertos_hello.c      ← main(), tareas RTOS │
│ board.c / board.h     ← inicialización LEDs │
│ clock_config.c/h      ← configuración clocks│
│ pin_mux.c/h           ← asignación pines   │
│ Startup (implícito)   ← stack, vector table│
└─────────────────────────────────────────────┘
                     │ linker
                     ▼
[ Linker script ] 🟨
┌─────────────────────────────────────────────┐
│ MK64FN1M0xxx12_flash.ld                     │
│ - .text → Flash                             │
│ - .data → RAM                               │
│ - .bss → RAM                                │
│ - Stack / Heap para FreeRTOS                │
└─────────────────────────────────────────────┘
                     │ convert .elf → .bin/.hex
                     ▼
[ Flash a FRDM-K64F ] 🟧
┌─────────────────────────────────────────────┐
│ OpenOCD / Segger J-Link                     │
│ Carga binario en flash del MCU             │
└─────────────────────────────────────────────┘
                     │ MCU arranca
                     ▼
[ Startup MCU ] 🟥
┌─────────────────────────────────────────────┐
│ Inicializa stack pointer y vector table     │
│ Inicializa .data y .bss                     │
│ Configura clocks (SystemInit)               │
│ Llama a main()                              │
└─────────────────────────────────────────────┘
                     │ FreeRTOS toma control
                     ▼
[ main() + FreeRTOS ] 🟪
┌─────────────────────────────────────────────┐
│ xTaskCreate() → crea tareas                  │
│ Configura colas / semáforos / timers        │
│ vTaskStartScheduler() → scheduler corriendo │
└─────────────────────────────────────────────┘
                     │ Scheduler activo
                     ▼
[ FreeRTOS Scheduler ] 🟩
┌─────────────────────────────────────────────┐
│ Decide qué tarea ejecutar según prioridad   │
│ Maneja delays, colas, semáforos, timers    │
│ Ejecuta ISR / Hooks integradas              │
└─────────────────────────────────────────────┘
