import numpy as np
import matplotlib.pyplot as plt
import sys

inputfilename = sys.argv[1] #ej. file.txt
outputfilename = sys.argv[2] #ej. file.png
# Cargar datos (dos columnas: tiempo y voltaje)
data = np.loadtxt(inputfilename)

t = data[:, 0]   # tiempo
v = data[:, 1]   # voltaje


# ==============================
# Graficar
# ==============================
plt.figure()
#plt.plot(t, Vin, label="Vin")
plt.plot(t, v, label="Vout (RC)")
plt.xlabel("Tiempo (t)")
plt.ylabel("Voltaje (V)")
plt.title("Simulación Circuito RC")
plt.legend()
plt.grid()

plt.tight_layout()
plt.savefig(outputfilename, dpi=300)

