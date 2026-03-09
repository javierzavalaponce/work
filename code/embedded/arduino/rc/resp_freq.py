import math
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

RC = 0.1
Ts = 0.002
A  = 5.0  # Amplitud

# Vector de frecuencias
f = np.linspace(1, 10, num=10)

# Tiempo de simulación (500 puntos = 1 segundo)
t = np.arange(0, 1.0, Ts)

# Lista para almacenar todas las simulaciones y[]
Y_matrix = []

for i, freq in enumerate(f):
    x = A * np.sin(2 * np.pi * freq * t)  # Entrada seno (vector)
    y = np.zeros_like(t)  # Estado inicial
    for n in range(1, len(t)):
        y[n] = y[n-1] + (Ts/RC) * (x[n] - y[n-1])  # Ecuación discreta RC
    
    Y_matrix.append(y)  # Agregar fila completa

# Convertir a matriz 10x500 y luego DataFrame
Y_array = np.array(Y_matrix)  # Shape: (10, 500)
df = pd.DataFrame(Y_array, 
                  index=[f"Freq_{int(fi)}Hz" for fi in f],
                  columns=[f"t_{i}" for i in range(500)])

print("Shape del DataFrame:", df.shape)
print(df.head())

# GRAFICAR: 10 curvas en mismo plot
plt.figure(figsize=(12, 8))
for freq_label in df.index:
    plt.plot(t, df.loc[freq_label], label=freq_label, linewidth=2)

plt.xlabel('Tiempo [s]')
plt.ylabel('Voltaje salida [V]')
plt.title('Respuesta en Frecuencia del Circuito RC\n(10 frecuencias 1-10 Hz)')
plt.grid(True, alpha=0.3)
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()
plt.tight_layout()
plt.savefig("fre.png", dpi=300)
