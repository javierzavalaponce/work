
"""
Simulación de un lazo de control retroalimentado con retardo
de tiempo puro en el camino directo.

El programa permite estudiar experimentalmente cómo el retardo
afecta la respuesta y la estabilidad de un sistema en lazo cerrado.

Recibe por línea de comandos:
    1. El retardo tau, expresado en segundos.
    2. El nombre del archivo PNG de salida.

La planta se representa mediante un modelo en espacio de estados:

    dx/dt = A @ x + B * u

    y = C @ x + D * u

donde:
    x : vector columna de estados de la planta.
    u : señal de entrada.
    y : salida escalar de la planta.
    A, B, C, D : matrices del modelo en espacio de estados.

La dinámica de la planta se integra mediante el método RK4
(Runge-Kutta de cuarto orden), con un paso de integración dt.

El retardo se implementa mediante un buffer tipo cola (deque).
En cada iteración se lee la muestra más antigua del buffer,
que representa la señal de control retardada, y se almacena
la nueva señal de control.

El retardo se representa mediante un número entero de muestras:

    N_retardo = round(tau / dt)

En cada iteración:
    1. Se obtiene la señal de control que llega a la planta.
    2. Se calcula la salida de la planta.
    3. Se calcula el error e = r - y.
    4. Se calcula la señal de control.
    5. Se integra la dinámica de la planta mediante RK4.
    6. Se actualiza el buffer de retardo, si existe.

Limitaciones:
    - El retardo se aproxima a un número entero de muestras.
    - No se utiliza una aproximación de Padé.
    - RK4 supone que la entrada permanece constante durante
      cada intervalo de integración.
    - Las condiciones iniciales de los estados son cero.
"""


import sys
import numpy as np
import matplotlib.pyplot as plt
from collections import deque


def main():
    plt.close('all')

    if len(sys.argv) != 3:
        print(
            "Uso: python misim_retardo_ntre_HyG_fase2.py "
            "<tau> <output.png>"
        )
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

    # Función interna que calcula las derivadas de los estados
    def dinamica_sistema(x, u):

        # A @ x: producto matricial.
        # B * u: matriz columna multiplicada por un escalar.
        dx_dt = A @ x + B * u

        return dx_dt

    return dinamica_sistema, A, B, C, D


def paso_rk4(dinamica_sistema, x, u, dt):
    """
    Avanza un paso de integración para el vector de estados x.

    dinamica_sistema(x, u) devuelve dx/dt.
    Se supone que u permanece constante durante el intervalo dt.
    """

    # Calcular las cuatro pendientes del vector de estados
    k1 = dinamica_sistema(x, u)
    k2 = dinamica_sistema(x + (dt / 2) * k1, u)
    k3 = dinamica_sistema(x + (dt / 2) * k2, u)
    k4 = dinamica_sistema(x + dt * k3, u)

    # Combinar las pendientes para obtener el nuevo vector de estados
    x_nueva = x + (dt / 6) * (k1 + 2*k2 + 2*k3 + k4)

    return x_nueva


def do_once(tau, filename):

    # --- 1. Definición de parámetros ---

    k = 2.0          # Ganancia del controlador H(s) = k
    dt = 0.01        # Paso de simulación en segundos
    t_final = 15.0   # Tiempo total de simulación

    # Validar el retardo
    if tau < 0:
        raise ValueError("El retardo tau no puede ser negativo.")

    # --- 2. Definición de la planta ---

    # G(s) = 10 / (s^2 + 2s + 5)
    G_num = [10]
    G_den = [1, 2, 5]

    # Obtener la dinámica y las matrices del espacio de estados
    dinamica_sistema, A, B, C, D = crear_dinamica_desde_tf(
        G_num,
        G_den
    )

    # --- 3. Condiciones iniciales ---

    # x representa el vector de estados de la planta.
    # Su dimensión es n x 1, donde n es el orden del denominador.
    #
    # Para esta planta de segundo orden:
    #
    # x = [[0],
    #      [0]]
    #
    # La planta comienza en reposo: todos sus estados son cero.

    x = np.zeros((A.shape[0], 1))

    r = 1.0
    t = 0.0

    # --- 4. Configuración del buffer de retardo ---

    # Convertir el retardo en un número entero de muestras.
    #
    # Ejemplo:
    # tau = 1.5 s
    # dt  = 0.01 s
    # N_retardo = 150 muestras

    N_retardo = int(round(tau / dt))

    # Crear un buffer con N_retardo muestras inicializadas en cero.
    #
    # maxlen=N_retardo garantiza que, al agregar una muestra nueva,
    # la muestra más antigua sea descartada automáticamente.
    #
    # Si N_retardo = 0, el buffer queda vacío y no se utilizará.

    buffer_retardo = deque(
        [0.0] * N_retardo,
        maxlen=N_retardo
    )

    # --- 5. Listas para guardar los datos y graficar ---

    tiempos = []
    salidas_y = []
    senales_control_u = []

    # --- 6. Bucle de simulación ---

    while t <= t_final:

        # A) Obtener la señal que llega a la planta.

        if N_retardo > 0:

            # Con retardo, la entrada es la muestra más antigua
            # almacenada en el buffer.
            u_retardada = buffer_retardo[0]

        else:

            # Sin retardo todavía no conocemos u_control,
            # porque primero necesitamos calcular la salida y el error.
            # Por ahora usamos cero para calcular la salida.
            u_retardada = 0.0

        # B) Calcular la salida de la planta.
        #
        # y = C @ x + D * u_retardada
        #
        # .item() extrae el único elemento de la matriz resultante
        # y lo convierte en un escalar Python.

        y_salida = (C @ x + D * u_retardada).item()

        # C) Calcular el error y la señal de control.

        error = r - y_salida
        u_control = k * error

        # D) Resolver la entrada que recibe la planta.

        if N_retardo == 0:

            # Sin retardo, la señal de control entra inmediatamente.
            u_retardada = u_control

        # E) Integrar la dinámica de la planta con RK4.

        x_nueva = paso_rk4(
            dinamica_sistema,
            x,
            u_retardada,
            dt
        )

        # F) Actualizar el buffer de retardo.

        if N_retardo > 0:

            # Guardar la nueva señal de control.
            # La muestra más antigua sale automáticamente
            # porque el buffer tiene capacidad N_retardo.
            buffer_retardo.append(u_control)

        # G) Guardar datos para las gráficas.

        tiempos.append(t)
        salidas_y.append(y_salida)
        senales_control_u.append(u_control)

        # H) Actualizar el estado y avanzar el tiempo.

        x = x_nueva
        t += dt

    # --- 7. Graficar resultados ---

    plt.figure(figsize=(10, 5))

    plt.plot(
        tiempos,
        salidas_y,
        label='Salida Y(t)',
        color='blue',
        linewidth=2
    )

    plt.plot(
        tiempos,
        [r] * len(tiempos),
        'r--',
        label='Referencia R(t)'
    )

    plt.title(
        f'Simulación de lazo cerrado con retardo '
        f'Tau={tau:04.2f}s (k={k:.2f})'
    )

    plt.xlabel('Tiempo (s)')
    plt.ylabel('Amplitud')
    plt.grid(True)
    plt.legend(loc='lower left')

    plt.xlim(0, t_final)

    plt.tight_layout()
    plt.savefig(filename, dpi=150)
    plt.close()


if __name__ == "__main__":

    try:
        main()

    except (KeyboardInterrupt, EOFError):
        print("\nSaliendo.")
