'''
Este script simula en Python un lazo de control 
retroalimentado con retardo de tiempo puro en el camino directo, 
para estudiar cómo el retardo afecta la estabilidad del sistema.

Recibe por línea de comandos el retardo Tau y el nombre del archivo .png de salida.
Implementa el retardo con un buffer 
tipo cola (deque) de tamaño Tau/dt: 
en cada paso lee la señal de control más antigua y guarda la nueva, 
emulando el retardo de forma discreta.

Integra la dinámica de la planta
(paso dt=0.01 simulación de 15 s).

En cada iteración: calcula el error e=r−y
aplica el controlador, lee la señal retardada del buffer, 
integra la planta  y actualiza el buffer con la nueva u.

Permite visualizar experimentalmente el efecto del retardo sobre la 
respuesta en lazo cerrado: 

#Notas

- Usa RK4
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



def tf2ss(num, den):
    """
    Convierte una función de transferencia en espacio de estados
    mediante la forma canónica controlable.
    """
    # Convertir las listas a arreglos NumPy
    num = np.asarray(num, dtype=float)
    den = np.asarray(den, dtype=float)

    # Validaciones básicas
    if den.ndim != 1 or num.ndim != 1:
        raise ValueError("num y den deben ser listas unidimensionales.")

    if len(den) < 2:
        raise ValueError("El denominador debe tener grado mayor o igual a 1.")

    if den[0] == 0:
        raise ValueError("El coeficiente principal de den no puede ser cero.")

    if len(num) == 0 or np.all(num == 0):
        raise ValueError("El numerador debe contener coeficientes no nulos.")

    n = len(den) - 1

    if len(num) > len(den):
        raise ValueError("La función de transferencia debe ser propia.")

    # Normalizar para que el denominador sea mónico
    num = num / den[0]
    den = den / den[0]

    # Completar el numerador con ceros a la izquierda
    num = np.pad(num, (len(den) - len(num), 0))

    a = den[1:]
    D = np.array([[num[0]]])

    # Matriz A: forma canónica controlable
    A = np.zeros((n, n))
    if n > 1:
        A[:-1, 1:] = np.eye(n - 1)
    A[-1, :] = -a[::-1]

    # Matriz B
    B = np.zeros((n, 1))
    B[-1, 0] = 1

    # Matriz C
    c = num[1:] - D[0, 0] * den[1:]
    C = c[::-1].reshape(1, n)

    return A, B, C, D

def crear_dinamica_desde_tf(num, den):
    """
    Recibe los polinomios num/den de la planta, usa tf2ss para obtener 
    las matrices, y devuelve la función de dinámica lista para RK4.
    """
    A, B, C, D = tf2ss(num, den)
    
    # La función interna que usará RK4
    def dinamica_sistema(x, u):
        # A @ x es matriz por vector. 
        # B * u es matriz columna por escalar (esto da una matriz columna).
        dx_dt = A @ x + B * u 
        return dx_dt
        
    return dinamica_sistema, A, B, C, D



def paso_rk4(dinamica_sistema, x, u, dt):
    """
    Avanza un paso de integración para el vector de estados x.
    dinamica_sistema(x, u) devuelve dx/dt.
    Se supone que u permanece constante durante el intervalo dt.
    """
    # Calcula las cuatro pendientes del vector de estados
    k1 = dinamica_sistema(x, u)
    k2 = dinamica_sistema(x + (dt / 2) * k1, u)
    k3 = dinamica_sistema(x + (dt / 2) * k2, u)
    k4 = dinamica_sistema(x + dt * k3, u)

    # Combina las pendientes para obtener el nuevo vector de estados
    x_nueva = x + (dt / 6) * (k1 + 2*k2 + 2*k3 + k4)

    return x_nueva


def do_once(input1,input2):
    # --- 1. Definición de Parámetros ---
    k = 2.0          # Ganancia del controlador H(s) = k
    tau = input1        # Retardo en segundos
    dt = 0.01        # Paso de simulación 
    t_final = 15.0   # Tiempo total de simulación
    filename=input2
    
    # --- 2. CAPA DE DATOS
    # Definimos G(s) 
    G_num = [10]
    G_den = [1, 2 , 5]
    
    # Creamos la dinámica, las matrices y la salida C
    dinamica_sistema, A, B, C, D = crear_dinamica_desde_tf(G_num, G_den)


    # --- 3. Condiciones iniciales ---
    
    # x representa el vector de estados de la planta.
    # Su dimensión es n x 1, donde n es el orden del denominador.
    # np.zeros crea el vector columna: ej:
    # x = [[0],
    #      [0]] 
    #
    # La planta comienza en reposo: todos sus estados son cero.
    
    x = np.zeros((A.shape[0], 1))
    r = 1.0
    t = 0.0


    # --- 3. Configuración del Buffer de Retardo ---
    # ¿Cuántas muestras necesitamos guardar para tener el retardo de 1.5s?
    # Si dt = 0.01, necesitamos 150 muestras para tener 1.5 segundos.
    N_retardo = int(tau / dt) 
    # double-ended queue:
    buffer_retardo = deque(maxlen=N_retardo + 1)
    
    # Llenamos el buffer inicialmente con ceros (asumimos que el sistema inicia en reposo)
    for _ in range(N_retardo):
        buffer_retardo.append(0.0)
    
    
    # Listas para guardar los datos y graficar
    tiempos = []
    salidas_y = []
    senales_control_u = []
    
    # --- 5. Bucle de Simulación (El motor) ---
    while t <= t_final:

        # A) Calcular la salida real
        # C @ x es una matriz de 1x1. D[0,0] * buffer es un escalar.
        # Para que no haya bronca, sacamos el valor de la matriz con [0, 0]
        
        y_salida = float((C @ x)[0, 0] + D[0, 0] * buffer_retardo[0])
        error = r - y_salida

        # B) Controlador H(s) = k
        u_control = k * error
        
        # C) EL RETARDO EN EL CAMINO DIRECTO
        # La señal de control se retrasa antes de entrar a la planta
        u_retardada = buffer_retardo[0]
        
        # D) La Planta usa la función de derivadas
        # Integrar la planta con RK4
        x_nueva = paso_rk4(dinamica_sistema, x, u_retardada, dt)
        
        # E) Actualizar el buffer de retardo
        # ¡OJO! Ahora guardamos la señal de control 
        #(lo que entra al buffer de retardo)
        buffer_retardo.append(u_control)
        
        # F) Guardar datos
        tiempos.append(t)
        salidas_y.append(y_salida)
        senales_control_u.append(u_control)
        
        # G) Avanzar el tiempo y actualizar el estado
        x = x_nueva
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
    #plt.ylim(-3.5, 3.8)

    plt.tight_layout()
    plt.savefig(filename, dpi=150)
    plt.close()

if __name__ == "__main__":
    try:
        main()
    except (KeyboardInterrupt, EOFError):
        print("\nSaliendo.")    
