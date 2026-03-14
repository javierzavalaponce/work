para grabar audio
con steinberg:

pw-cat -r --channels=2 --rate=44100 --format=s16        --target alsa_input.usb-Yamaha_Corporation_Steinberg_UR22-00.analog-stereo        test.wav

sox test.wav -b 16 -c 2 -r 44100 salida.raw


+-----------------

pw-cat -r --channels=2 --rate=44100 --format=s16        --target alsa_input.usb-Yamaha_Corporation_Steinberg_UR22-00.analog-stereo        - | ./procesa_audio

asi compilo el codigo:
gcc procesa_audio.c -o procesa_audio

pw-cli list-objects | grep -i ur22




