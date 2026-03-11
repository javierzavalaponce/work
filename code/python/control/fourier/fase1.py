import math
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


Ts = 0.001 # Frecuencua de muestreo 1KHz


# Tiempo de simulación 3 segundos
t = np.arange(0, 3.0, Ts) #Tenemos 3000 muestras

A    = 1;
freq = 2; #2Hz
fase = (np.pi)
y  = A * np.sin(2 * np.pi * freq * t) 
y2 = A * np.sin(2 * np.pi * freq * t + fase) 


plt.figure()
plt.plot(t,y)
plt.plot(t,y2)
plt.xlabel("tiempo")
plt.ylabel("Magnitud")
plt.title("seno desfasado")
plt.grid()
plt.tight_layout()
plt.savefig("dos_senos_a_dos_hz.png")




