import numpy as np
import matplotlib.pyplot as plt
from collections import deque

# --- 1. Definición de Parámetros ---
k = 2.0          # Ganancia del controlador H(s) = k
tau = 1.5        # Retardo en segundos
dt = 0.01        # Paso de simulación (muy pequeño para precisión)
t_final = 15.0   # Tiempo total de simulación

# --- 2. Configuración del Buffer de Retardo ---
# ¿Cuántas muestras necesitamos guardar para tener el retardo de 1.5s?
# Si dt = 0.01, necesitamos 150 muestras para tener 1.5 segundos.
N_retardo = int(tau / dt) 
buffer_retardo = deque(maxlen=N_retardo + 1)

# Llenamos el buffer inicialmente con ceros (asumimos que el sistema inicia en reposo)
for _ in range(N_retardo):
    buffer_retardo.append(0.0)

# --- 3. Condiciones Iniciales ---
y = 0.0          # Salida de la planta G(s)
r = 1.0          # Referencia (escalón unitario)
t = 0.0          # Tiempo actual

# Listas para guardar los datos y graficar
tiempos = []
salidas_y = []
senales_control_u = []

# --- 4. Bucle de Simulación (El motor) ---
while t <= t_final:
    # A) El lazo de realimentación (Sumador)
    # La señal que sale del sumador es el error: e = r - y_retardada
    # PERO OJO: el retardo está en el lazo de realimentación.
    # La señal que se retroalimenta es y(t - tau).
    y_retardada = buffer_retardo[0] 
    
    # B) Controlador H(s) = k
    error = r - y_retardada
    u_control = k * error
    
    # C) La Planta G(s) = 1 / (s+1)
    # Ecuación: dy/dt = -y + u
    # Método de Euler: y_nueva = y_vieja + dt * (dy/dt)
    dy_dt = -y + u_control
    y_nueva = y + dt * dy_dt
    
    # D) Actualizar el buffer de retardo
    # Agregamos la nueva salida de la planta al final del buffer
    buffer_retardo.append(y_nueva)
    
    # E) Guardar datos
    tiempos.append(t)
    salidas_y.append(y)
    senales_control_u.append(u_control)
    
    # F) Avanzar el tiempo y actualizar el estado
    y = y_nueva
    t += dt

# --- 5. Visualización ---
plt.figure(figsize=(10, 5))
plt.plot(tiempos, salidas_y, label='Salida Y(t)', color='blue', linewidth=2)
plt.plot(tiempos, [r]*len(tiempos), 'r--', label='Referencia R(t)')
plt.title(f'Simulación de lazo cerrado con retardo Tau={tau}s (k={k})')
plt.xlabel('Tiempo (s)')
plt.ylabel('Amplitud')
plt.grid(True)
plt.legend()
plt.show()