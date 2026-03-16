using WAV

# parámetros de audio
fs = 44100           # frecuencia de muestreo (Hz)
f  = 100             # frecuencia del tono (Hz)
dur = 60             # duración en segundos

# vector de tiempo
t = 0:1/fs:dur

# generar seno
audio = sin.(2π * f .* t)

# opcional: bajar amplitud para evitar clipping
audio = 0.8 .* audio

# guardar archivo wav
wavwrite(audio, "100Hz.wav", Fs=fs)


