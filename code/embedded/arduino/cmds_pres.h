

arduino-cli compile --fqbn arduino:avr:uno ./fur02_encoder_state_mach.c/fur02_encoder_state_mach.c.ino


arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno ./fur02_encoder_state_mach.c/fur02_encoder_state_mach.c.ino

minicom -D /dev/ttyACM0 -b 115200


