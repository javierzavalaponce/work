using WAV
using Plots

#Generar el chirp con silencios entre cada frecuencia
gr()
fs = 44100
frecuencias = [20, 30, 40, 50, 60, 70, 80, 90, 100]
# duración del silencio (20 ms)
silencio = zeros(Int(fs * 0.02))
chirp_signal = vcat([
    vcat(
        sin.(2π * fn .* (0:1/fs:(4/fn - 1/fs))),
        silencio
    )
    for fn in frecuencias
]...)

# vector de tiempo global
t = (0:length(chirp_signal)-1) ./ fs

p = plot(t, chirp_signal,
     xlabel="Tiempo (s)",
     ylabel="Amplitud",
     title="Barrido con silencios",
     label="señal")

savefig(p, "chirp.png")

# guardar archivo WAV
wavwrite(chirp_signal, "chirp.wav", Fs=fs)
println(length(chirp_signal) / fs, " segundos")
