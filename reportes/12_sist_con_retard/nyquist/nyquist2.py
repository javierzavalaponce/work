import numpy as np
import matplotlib.pyplot as plt

# 1. Sistema y Controlador
num_G = [1]
den_G = [1, 1]
K = 3.0  # Ganancia del controlador

# 2. Rango de frecuencias (de 0.001 a 5 rad/s para ver bien la espiral)
w = np.logspace(-3, np.log10(5), 2000)
s = 1j * w

# 3. Lazo Abierto SIN retardo
G_jw = np.polyval(num_G, s) / np.polyval(den_G, s)
L_sin_retardo = K * G_jw

# 4. Graficación
plt.figure(figsize=(10, 8))

# Graficamos el sistema sin retardo (la referencia)
plt.plot(L_sin_retardo.real, L_sin_retardo.imag, 'k--', linewidth=1.5, label='Sin retardo (Estable)')

# Definimos los retardos a probar
retardos = [1.0, 2.5, 4.5]
colores = ['blue', 'orange', 'red']

for tau, color in zip(retardos, colores):
    # El truco: multiplicamos por e^(-jw*tau)
    retardo_fasor = np.exp(-s * tau)
    L_con_retardo = L_sin_retardo * retardo_fasor
    
    # Graficamos
    plt.plot(L_con_retardo.real, L_con_retardo.imag, color=color, linewidth=2, label=f'Retardo τ={tau}s')

# El punto crítico (-1, 0)
plt.plot(-1, 0, 'kx', markersize=14, markeredgewidth=3, label='Punto Crítico (-1, j0)')

# Estética
plt.axhline(0, color='black', linewidth=0.8)
plt.axvline(0, color='black', linewidth=0.8)
plt.title('Efecto del Retardo en el Diagrama de Nyquist', fontsize=14)
plt.xlabel('Parte Real', fontsize=12)
plt.ylabel('Parte Imaginaria', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.axis('equal') # Fundamental para ver la circunferencia real
plt.xlim(-3, 4)
plt.ylim(-4, 2)
plt.legend(loc='upper right', fontsize=11)

plt.tight_layout()
plt.show()