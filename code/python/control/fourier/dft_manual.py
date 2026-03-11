import math
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


Ts = 0.001 # Frecuencua de muestreo 1KHz


# Tiempo de simulación 1 segundo
t = np.arange(0, 1.0, Ts) #Tenemos 1000 muestras

A    = 1;
freq1 = 3; 
freq2 = 5; 
y1  = A * np.sin(2 * np.pi * freq1 * t) 
y2  = A * np.sin(2 * np.pi * freq2 * t) 

y = y1 + y2
N = len(y)
Fs = 1/Ts


X = np.zeros(N, dtype=complex)

for k in range(N):
    s = 0
    for n in range(N):
        angle = -2j * np.pi * k * n / N
        s += y[n] * np.exp(angle)
    X[k] = s


freq = np.arange(N) * Fs / N
mag = np.abs(X)
plt.figure()
plt.plot(freq, mag)
plt.xlim(0,20)
plt.xlabel("Frecuencia [Hz]")
plt.ylabel("Magnitud")
plt.title("DFT calculada manualmente")
plt.grid()
plt.show()



