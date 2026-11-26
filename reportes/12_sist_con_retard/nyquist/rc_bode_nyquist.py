import numpy as np
import matplotlib.pyplot as plt

# 1. Definimos el sistema RC (G(s) = 1 / (s+1))
num = [1]
den = [1, 1]

# 2. Creamos un rango de frecuencias (de 0.01 a 10 rad/s)
w = np.logspace(-2, 1, 500)
s = 1j * w

# 3. Evaluamos el sistema en esas frecuencias
G_jw = np.polyval(num, s) / np.polyval(den, s)

# Calculamos Magnitud (en dB) y Fase (en grados)
magnitud = np.abs(G_jw)
magnitud_db = 20 * np.log10(magnitud)
fase = np.angle(G_jw, deg=True)

# 4. Creamos la figura con 3 sub-gráficas
fig = plt.figure(figsize=(14, 5))

# --- Gráfica 1: Bode Magnitud ---
ax1 = fig.add_subplot(131)
ax1.semilogx(w, magnitud_db, 'b-', linewidth=2)
ax1.set_title('Bode - Magnitud')
ax1.set_xlabel('Frecuencia (rad/s)')
ax1.set_ylabel('Magnitud (dB)')
ax1.grid(True, which="both", ls="--")
# Marcamos la frecuencia de corte (w = 1)
ax1.axvline(1, color='r', linestyle='--', alpha=0.5)
ax1.plot(1, -3, 'ro') # A w=1, la magnitud cae a -3dB
ax1.annotate('w=1 (-3dB)', (1, -3), textcoords="offset points", xytext=(10,-15))

# --- Gráfica 2: Bode Fase ---
ax2 = fig.add_subplot(132)
ax2.semilogx(w, fase, 'g-', linewidth=2)
ax2.set_title('Bode - Fase')
ax2.set_xlabel('Frecuencia (rad/s)')
ax2.set_ylabel('Fase (grados)')
ax2.grid(True, which="both", ls="--")
ax2.axvline(1, color='r', linestyle='--', alpha=0.5)
ax2.plot(1, -45, 'ro') # A w=1, la fase es -45 grados
ax2.annotate('w=1 (-45°)', (1, -45), textcoords="offset points", xytext=(10,10))
ax2.set_ylim(-100, 10)

# --- Gráfica 3: Nyquist ---
ax3 = fig.add_subplot(133)
ax3.plot(G_jw.real, G_jw.imag, 'm-', linewidth=2)
ax3.plot(-1, 0, 'kx', markersize=12, markeredgewidth=2, label='Punto Crítico (-1,0)')
ax3.set_title('Diagrama de Nyquist')
ax3.set_xlabel('Parte Real')
ax3.set_ylabel('Parte Imaginaria')
ax3.grid(True)
ax3.axhline(0, color='black', linewidth=0.5)
ax3.axvline(0, color='black', linewidth=0.5)
ax3.axis('equal') # Misma escala en X e Y para ver el círculo real
ax3.set_xlim(-1.2, 1.2)
ax3.set_ylim(-1.2, 0.2)

# Puntos de anclaje para entender el Nyquist
# Punto en w=0.01 (frecuencia casi cero)
ax3.plot(G_jw[0].real, G_jw[0].imag, 'ro')
ax3.annotate('w=0.01 (Inicio)', (G_jw[0].real, G_jw[0].imag), textcoords="offset points", xytext=(-80,10), color='red')
# Punto en w=1 (frecuencia de corte)
ax3.plot(0.5, -0.5, 'ro')
ax3.annotate('w=1', (0.5, -0.5), textcoords="offset points", xytext=(10,-15), color='red')

plt.tight_layout()
plt.show()



