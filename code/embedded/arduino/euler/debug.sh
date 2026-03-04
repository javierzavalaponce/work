#!/bin/bash

arduino-cli compile \
  --fqbn arduino:avr:uno \
  --build-property compiler.cpp.extra_flags="-g -Og" \
  --build-path build .

qemu-system-avr \
  -machine arduino-uno \
  -bios build/euler.ino.elf \
  -S \
  -gdb tcp::1234


