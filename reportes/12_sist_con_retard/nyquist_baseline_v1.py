import numpy as np
import matplotlib.pyplot as plt

# ==========================================
# 1. CAPA DE DATOS 
# ==========================================
# Planta G(s) = 1 / (s + 1)
G_num = [1]
G_den = [1, 1]

# Controlador H(s) = 2.0
H_num = [2.0]
H_den = [1.0]

# Retardo
tau = 0.7

# ==========================================
# 2. EL MOTOR MATEMÁTICO 
# ==========================================
# Creamos un vector de frecuencias: de 0.01 a 10 rad/s (1000 puntos)
omega = np.logspace(-2, 1, 1000)
s = 1j * omega # Aquí está el truco: s = jw

# Evaluamos los polinomios usando np.polyval
# np.polyval evalúa el polinomio en los puntos 's'
G_jw = np.polyval(G_num, s) / np.polyval(G_den, s)
H_jw = np.polyval(H_num, s) / np.polyval(H_den, s)

# El Lazo Abierto (sin retardo)
L_sin_retardo = H_jw * G_jw

# Aplicamos el retardo exacto (Multiplicación por e^-jwT)
retardo_fasor = np.exp(-s * tau)
L_con_retardo = L_sin_retardo * retardo_fasor

# ==========================================
# 3. GRAFICACIÓN
# ==========================================
plt.figure(figsize=(8, 8))

# Graficamos el lazo abierto SIN retardo (para comparar)
plt.plot(L_sin_retardo.real, L_sin_retardo.imag, 'b--', label='Sin retardo')

# Graficamos el lazo abierto CON retardo (nuestra meta)
plt.plot(L_con_retardo.real, L_con_retardo.imag, 'r-', linewidth=2, label=f'Con retardo (τ={tau})')

# El famoso Punto Crítico (-1, j0)
plt.plot(-1, 0, 'kx', markersize=12, markeredgewidth=2, label='Punto Crítico (-1, j0)')

# Detalles estéticos
plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)
plt.title('Diagrama de Nyquist Exacto')
plt.xlabel('Parte Real')
plt.ylabel('Parte Imaginaria')
plt.grid(True)
plt.legend(loc='upper right')

# Para que los ejes estén a la misma escala (círculo perfecto)
plt.axis('equal') 

# Limitar la vista para no perdernos si la curva se va al infinito
plt.xlim(-3, 3)
plt.ylim(-3, 3)

plt.show()


