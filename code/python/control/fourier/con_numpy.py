import math
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


Ts = 0.001 # Frecuencua de muestreo 1KHz


# Tiempo de simulación 3 segundos
t = np.arange(0, 3.0, Ts) #Tenemos 3000 muestras

A1 = 1;
A2 = 1;
freq1=3;
freq2=5;
y1 = A1 * np.sin(2 * np.pi * freq1 * t) 
y2 = A2 * np.sin(2 * np.pi * freq2 * t) 


y = y1 + y2
Y = np.fft.fft(y)
freq = np.fft.fftfreq(len(t), Ts)
mag = np.abs(Y)

plt.figure()
plt.plot(freq, mag)
plt.xlim(0,20)
plt.xlabel("Frecuencia [Hz]")
plt.ylabel("Magnitud")
plt.title("Espectro de Fourier")
plt.grid()
plt.tight_layout()
plt.savefig("02.png", dpi=300)




