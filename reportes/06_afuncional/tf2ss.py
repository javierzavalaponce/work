
import numpy as np


def tf2ss(num, den):
    """
    Convierte una función de transferencia en espacio de estados
    mediante la forma canónica controlable.

    num: coeficientes del numerador, en orden descendente.
    den: coeficientes del denominador, en orden descendente.

    Retorna:
        A, B, C, D
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

    # Coeficientes del denominador:
    # den = [1, a1, a2, ..., an]
    a = den[1:]

    # Ganancia directa
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


# --------------------------------------------------
# EJEMPLO
# --------------------------------------------------

num = [1]
den = [1, -3, 2]

A, B, C, D = tf2ss(num, den)

print("A =")
print(A)

print("\nB =")
print(B)

print("\nC =")
print(C)

print("\nD =")
print(D)


