#!/bin/bash

arduino-cli compile \
  --fqbn arduino:avr:uno \
  --build-property compiler.cpp.extra_flags="-g -Og" \
  --build-path build .

qemu-system-avr \
  -machine arduino-uno \
  -bios build/fur01_encoder_00ctrlmanual.ino.elf \
  -S \
  -gdb tcp::1234


