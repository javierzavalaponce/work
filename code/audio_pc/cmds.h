pw-cat -r --channels=2 --rate=44100 --format=s16        --target alsa_input.usb-Yamaha_Corporation_Steinberg_UR22-00.analog-stereo        - | ./procesa_audio
gcc procesa_audio.c -o procesa_audio
pw-cli list-objects | grep -i ur22
