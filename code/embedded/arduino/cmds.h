simavr -m atmega328p -f 16000000 uart.elf

minicom -D /dev/ttyACM0 -b 9600 -C log.csv
minicom -D /dev/ttyACM0 -b 9600 -C log01.csv
