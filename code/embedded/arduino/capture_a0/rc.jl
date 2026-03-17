using WAV
using Plots

# Leer archivo
x, fs = wavread("chirp.wav")

# Parámetros RC
fc = 40.0
RC = 1 / (2π * fc)
T = 1 / fs
alpha = T / (RC + T)

# Filtro RC discreto
y = similar(x)
y[1] = x[1]

for n in 2:length(x)
    y[n] = y[n-1] + alpha * (x[n] - y[n-1])
end

# Graficar
t = (0:length(x)-1) ./ fs
plot(t, x, label="Entrada")
plot!(t, y, label="Salida (RC)")

# Guardar WAV
wavwrite(y, "filtered.wav", Fs=fs)