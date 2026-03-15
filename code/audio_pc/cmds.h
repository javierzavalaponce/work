para grabar audio
con steinberg:

pw-cat -r --channels=2 --rate=44100 --format=s16        --target alsa_input.usb-Yamaha_Corporation_Steinberg_UR22-00.analog-stereo        test.wav

sox test.wav -b 16 -c 2 -r 44100 salida.raw


+-----------------

pw-cat -r --channels=2 --rate=44100 --format=s16        --target alsa_input.usb-Yamaha_Corporation_Steinberg_UR22-00.analog-stereo        - | ./procesa_audio

asi compilo el codigo:
gcc procesa_audio.c -o procesa_audio

pw-cli list-objects | grep -i ur22




gcc delay_wav.c -o delay_wav -lsndfile
git add delay_con_feedback.c cmds.hdelay_wav.c
./delay_wav salida.wav output.wav 190 0.6
julia delay_audio.jl test.wav 120 0.4 output_delayed.wav
julia delay_audio.jl test.wav 120 0.4 02.wav


dsp lab
GStreamer

FFmpeg

PipeWire

PiFmRds



ffmpeg -re -i test.wav \
-f s16le -ac 2 -ar 44100 \
udp://IP_RPI:5000

Daemon REST en Go 
para Raspberry Pi y controlar con curl.

La idea:

recibir WAV por HTTP

cambiar parámetros DSP

ejecutar tu pipeline

consultar estado

Esto el backend laboratorio colaborativo de DSP
en RPi , la salida de audio pasa a ser broadcasteada
por fm con PiFmrds
para escucharla por radio

streaming de audio en tiempo real (tipo radio web) para que los usuarios puedan escuchar el resultado en su navegador mientras modifican los filtros. Eso convierte tu sistema en un verdadero laboratorio DSP colaborativo







