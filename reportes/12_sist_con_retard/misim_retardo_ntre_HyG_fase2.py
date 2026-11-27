'''
Este script simula en Python un lazo de control 
retroalimentado con retardo de tiempo puro en el camino directo, 
para estudiar cómo el retardo afecta la estabilidad del sistema.

Recibe por línea de comandos el retardo Tau y el nombre del archivo .png de salida.
Implementa el retardo con un buffer 
tipo cola (deque) de tamaño Tau/dt: 
en cada paso lee la señal de control más antigua y guarda la nueva, 
emulando el retardo de forma discreta.

Integra la dinámica de la planta con método de Euler 
(paso dt=0.01 simulación de 15 s).

En cada iteración: calcula el error e=r−y
aplica el controlador, lee la señal retardada del buffer, 
integra la planta  y actualiza el buffer con la nueva u.

Permite visualizar experimentalmente el efecto del retardo sobre la 
respuesta en lazo cerrado: 

#Limitaciones

- Usa Euler explícito (precisión limitada si dt es grande).
- Retardo discreto por buffer (no usa aproximación de Padé).
- Condiciones iniciales en reposo.
'''

import sys
import numpy as np
import matplotlib.pyplot as plt
from collections import deque


def main():
    plt.close('all')
    if len(sys.argv) != 3:
        print("Uso: python misim_retardo_ntre_HyG_fase2.py <tau> <output.png>")
        sys.exit(1)
    do_once(float(sys.argv[1]), sys.argv[2])


def dinamica_planta(y, u):
    """Nueva planta: dy/dt = -2y + 2u"""
    return -2*y + 2*u

def paso_rk4(dinamica_sistema, y, u, dt):
    # Calcula las 4 pendientes (k1, k2, k3, k4)
    k1 = dinamica_sistema(y, u)
    k2 = dinamica_sistema(y + (dt/2) * k1, u)
    k3 = dinamica_sistema(y + (dt/2) * k2, u)
    k4 = dinamica_sistema(y + dt * k3, u)
    
    # Promedio ponderado
    y_new = y + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
    return y_new

def do_once(input1,input2):
    # --- 1. Definición de Parámetros ---
    k = 2.0          # Ganancia del controlador H(s) = k
    tau = input1        # Retardo en segundos
    dt = 0.01        # Paso de simulación 
    t_final = 15.0   # Tiempo total de simulación
    filename=input2
    
    # --- 2. Configuración del Buffer de Retardo ---
    # ¿Cuántas muestras necesitamos guardar para tener el retardo de 1.5s?
    # Si dt = 0.01, necesitamos 150 muestras para tener 1.5 segundos.
    N_retardo = int(tau / dt) 
    # double-ended queue:
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
        # A) El lazo de realimentación (Sumador) - AHORA VE EL PRESENTE
        # La señal que se retroalimenta es y(t), no y(t-tau).
        error = r - y
        
        # B) Controlador H(s) = k
        u_control = k * error
        
        # C) EL RETARDO EN EL CAMINO DIRECTO
        # La señal de control se retrasa antes de entrar a la planta
        u_retardada = buffer_retardo[0]
        
        # D) La Planta usa la función de derivadas
        # Integrar la planta con RK4
        y_nueva = paso_rk4(dinamica_planta, y, u_retardada, dt)
        
        # E) Actualizar el buffer de retardo
        # ¡OJO! Ahora guardamos la señal de control 
        #(lo que entra al buffer de retardo)
        buffer_retardo.append(u_control)
        
        # F) Guardar datos
        tiempos.append(t)
        salidas_y.append(y)
        senales_control_u.append(u_control)
        
        # G) Avanzar el tiempo y actualizar el estado
        y = y_nueva
        t += dt
        
    plt.figure(figsize=(10, 5))
    plt.plot(tiempos, salidas_y, label='Salida Y(t)', color='blue', linewidth=2)
    plt.plot(tiempos, [r]*len(tiempos), 'r--', label='Referencia R(t)')
    plt.title(f'Simulación de lazo cerrado con retardo Tau={tau:04.2f}s (k={k:.2f})')
    plt.xlabel('Tiempo (s)')
    plt.ylabel('Amplitud')
    plt.grid(True)
    plt.legend(loc='lower left')

    plt.xlim(0, t_final)
    plt.ylim(-3.5, 3.8)

    plt.tight_layout()
    plt.savefig(filename, dpi=150)
    plt.close()

if __name__ == "__main__":
    try:
        main()
    except (KeyboardInterrupt, EOFError):
        print("\nSaliendo.")    