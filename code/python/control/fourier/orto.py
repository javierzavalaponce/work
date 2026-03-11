import math
import numpy as np
import pandas as pd
from scipy.integrate import trapezoid  # Método trapecio
import matplotlib.pyplot as plt


Ts = 0.001 # Frecuencua de muestreo 1KHz


# Tiempo de simulación 1 segundo
t = np.arange(0, 1.0, Ts) #Tenemos 1000 muestras

A    = 1;
freq = 1; #1Hz
fase = (np.pi)
y1  = A * np.cos(1 * 2 * np.pi * freq * t) 
y2  = A * np.cos(2 * 2 * np.pi * freq * t) 


plt.figure()
plt.plot(t,y1)
plt.plot(t,y2)
plt.plot(t,y1*y2,linewidth=3)
plt.axhline(y=0, color='black', linewidth=1) 
plt.xlabel("tiempo")
plt.ylabel("Magnitud")
plt.title("multiplicando cos(1wt)*cos(2wt)")
plt.grid()
plt.tight_layout()
plt.savefig("orto.png")



integral = trapezoid(y1*y2, t)
print(integral)