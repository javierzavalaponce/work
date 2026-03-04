FRDM K64
Microcontrolador (MCU)

MCU principal: MK64FN1M0VLL12

Arquitectura: ARM Cortex-M4 con FPU y DSP
Frecuencia: Hasta 120 MHz
Memoria Flash: 1 MB para código/firmware
RAM: 256 KB
Paquete 100-LQFP
----

Flash
┌──────────────────────┐
│ 0x00000000 SP value  │
│ 0x00000004 Reset_H.  │
│ 0x00000008 NMI       │
│ ...                  │
└──────────────────────┘
        ↓
CPU carga SP
CPU salta a Reset_Handler
        ↓
Inicialización
        ↓
main()

	-------



RESET físico
      ↓
CPU lee 0x00000000 → MSP
CPU lee 0x00000004 → PC
      ↓
Reset_Handler
      ↓
Copiar .data
      ↓
Limpiar .bss
      ↓
SystemInit
      ↓
__libc_init_array
      ↓
main()


