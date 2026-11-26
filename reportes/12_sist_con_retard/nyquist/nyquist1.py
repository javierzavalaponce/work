import numpy as np
import matplotlib.pyplot as plt

# 1. Definimos el sistema RC y el Controlador
num_G = [1]
den_G = [1, 1]
K = 3.0  # Controlador Proporcional H(s) = 3

# 2. Rango de frecuencias
w = np.logspace(-2, 2, 1000)
s = 1j * w

# 3. Evaluamos la planta G(s) y el Lazo Abierto L(s) = K * G(s)
G_jw = np.polyval(num_G, s) / np.polyval(den_G, s)
L_jw = K * G_jw

# 4. Cálculos para Bode y Nyquist del Lazo Abierto
mag_G = 20 * np.log10(np.abs(G_jw))
mag_L = 20 * np.log10(np.abs(L_jw))
fase_G = np.angle(G_jw, deg=True)
fase_L = np.angle(L_jw, deg=True)

# 5. Graficación
fig = plt.figure(figsize=(15, 5))

# --- Gráfica 1: Bode Magnitud ---
ax1 = fig.add_subplot(131)
ax1.semilogx(w, mag_G, 'b--', label='G(s) - Sin control (K=1)')
ax1.semilogx(w, mag_L, 'r-', linewidth=2, label=f'L(s) - Con K={K}')
ax1.axhline(0, color='black', linewidth=0.8)
ax1.set_title('Bode - Magnitud')
ax1.set_ylabel('Magnitud (dB)')
ax1.grid(True, which="both", ls="--")
ax1.legend()

# --- Gráfica 2: Bode Fase ---
ax2 = fig.add_subplot(132)
ax2.semilogx(w, fase_G, 'b--', label='G(s) - Fase')
ax2.semilogx(w, fase_L, 'r-', linewidth=2, label=f'L(s) - Fase (Igual)')
ax2.axhline(-180, color='black', linewidth=0.8)
ax2.set_title('Bode - Fase')
ax2.set_ylabel('Fase (grados)')
ax2.grid(True, which="both", ls="--")
ax2.legend()

# --- Gráfica 3: Nyquist ---
ax3 = fig.add_subplot(133)
ax3.plot(G_jw.real, G_jw.imag, 'b--', label='G(s) - Sin control')
ax3.plot(L_jw.real, L_jw.imag, 'r-', linewidth=2, label=f'L(s) - K={K}')
ax3.plot(-1, 0, 'kx', markersize=12, markeredgewidth=2, label='Punto Crítico (-1,0)')
ax3.set_title('Diagrama de Nyquist')
ax3.set_xlabel('Parte Real')
ax3.set_ylabel('Parte Imaginaria')
ax3.grid(True)
ax3.axhline(0, color='black', linewidth=0.5)
ax3.axvline(0, color='black', linewidth=0.5)
ax3.axis('equal')
ax3.set_xlim(-1.5, 3.5)
ax3.set_ylim(-1.5, 1.5)
ax3.legend(loc='lower left')

plt.tight_layout()
plt.show()