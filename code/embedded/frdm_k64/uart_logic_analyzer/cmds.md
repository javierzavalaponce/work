# Comandos de Referencia
arm-none-eabi-objcopy -O binary ./build/blink.elf ./build/blink.bin
cp ./build/blink.bin /media/mictlan/MBED/


cp blink.bin /media/mictlan/MBED/
arm-none-eabi-objcopy -O binary blink.elf blink.bin

---

# Comandos para DEBUG:

Cono  Segger Jlink , Lanzar primero server GBD. Asi:

* term 1 *
JLinkGDBServer -device MK64FN1M0XXX12 -if SWD -speed 4000


* term2: *
gdb-multiarch blink.elf
o
F5 en code!

---

# Para solamenente cargar el binario

JLinkExe -device MK64FN1M0VLL12 -if SWD -speed 4000 -CommanderScript para_jlink.dat 

## Para lanzar minicom
minicom -D /dev/ttyUSB0 -b 115200

