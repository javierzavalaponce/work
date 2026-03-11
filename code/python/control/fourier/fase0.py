import math
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


Ts = 0.001 # Frecuencua de muestreo 1KHz


# Tiempo de simulación 3 segundos
t = np.arange(0, 3.0, Ts) #Tenemos 3000 muestras

A    = 1;
freq = 2; #2Hz
y = A * np.sin(2 * np.pi * freq * t) 


plt.figure()
plt.plot(t,y)
plt.xlabel("tiempo")
plt.ylabel("Magnitud")
plt.title("Grafica de seno(2 * np.pi * freq * t)")
plt.grid()
plt.tight_layout()
plt.savefig("sin_t.png")




