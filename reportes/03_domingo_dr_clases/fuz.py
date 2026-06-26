import numpy as np


def triangular(x, x0, x1):

    escalar = np.isscalar(x)
    x = np.asarray(x, dtype=float)
    if x1 <= x0:
        raise ValueError("x1 debe ser mayor que x0.")

    semi_ancho = (x1 - x0)/2
    centro = (x0 + x1)/2
    y = np.zeros_like(x)

    mascara_asc = (x0 < x) & (x <= centro)
    y[mascara_asc] = (x[mascara_asc]-x0)/semi_ancho

    mascara_desc = (centro < x) & (x < x1)
    y[mascara_desc] = (x1-x[mascara_desc])/semi_ancho

    if escalar:
        return float(y)

    return y

def trapezoidal(x, a, b, c, d):
    """
    Función de membresía trapezoidal.
    
    Parámetros:
    x : float o np.ndarray, valor(es) de entrada.
    a : inicio de la base izquierda (μ=0).
    b : inicio del plateau (μ=1).
    c : fin del plateau (μ=1).
    d : fin de la base derecha (μ=0).
    Debe cumplirse: a < b <= c < d.
    
    Retorna:
    Grado de pertenencia en [0, 1].
    """
    # Validación de escalar/array
    escalar = np.isscalar(x)
    x = np.asarray(x, dtype=float)
    
    # Validación de parámetros
    if not (a < b <= c < d):
        raise ValueError("Los parámetros deben cumplir: a < b <= c < d")
    
    # Inicializar con ceros (fuera del soporte)
    y = np.zeros_like(x)
    
    # Rama ascendente: a < x < b
    mask_asc = (a < x) & (x < b)
    y[mask_asc] = (x[mask_asc] - a) / (b - a)
    
    # Plateau: b <= x <= c
    mask_plateau = (b <= x) & (x <= c)
    y[mask_plateau] = 1.0
    
    # Rama descendente: c < x < d
    mask_desc = (c < x) & (x < d)
    y[mask_desc] = (d - x[mask_desc]) / (d - c)
    
    # Clip por seguridad (evita errores de redondeo)
    y = np.clip(y, 0.0, 1.0)
    
    # Si la entrada era escalar, devolver float
    if escalar:
        return float(y)
    return y


def gaussiana(x, c, sigma):
    """
    Función de membresía gaussiana.

    Parámetros:
    -----------
    x : float, int, o array-like
        Valor(es) de entrada donde evaluar la función.
    c : float
        Centro de la campana (punto de máxima pertenencia, donde mu = 1).
    sigma : float
        Ancho o dispersión de la campana (debe ser > 0).

    Retorna:
    --------
    y : float o np.ndarray
        Grado de pertenencia en el rango [0, 1].
    """
    # Guardar si la entrada es escalar
    escalar = np.isscalar(x)
    
    # Convertir a array para operaciones vectorizadas
    x = np.asarray(x, dtype=float)
    
    # Validación: sigma debe ser positivo
    if sigma <= 0:
        raise ValueError("sigma debe ser mayor que 0.")
    
    # Calcular la función gaussiana: exp(-(x-c)^2 / (2*sigma^2))
    y = np.exp(-((x - c) ** 2) / (2 * sigma ** 2))
    
    # Si era escalar, retornar float
    if escalar:
        return float(y)
    
    return y


def gauss(x, c, sigma):
    """
    Función de membresía gaussiana.

    Parámetros
    ----------
    x : float o array_like
        Valor(es) donde se evalúa la función.

    c : float
        Centro de la campana.

    sigma : float
        Desviación estándar (sigma > 0).

    Retorna
    -------
    float o ndarray
        Grado de pertenencia en el intervalo [0,1].

    Fórmula
    -------
        μ(x) = exp(-(x-c)^2/(2σ²))

    Ejemplo
    --------
    >>> import numpy as np
    >>> x = np.linspace(-5,5,100)
    >>> y = gauss(x,0,1)
    """
    
    return np.exp(-((x -c)**2)/(2*sigma**2))


def sigmoide(x, a, c):
    """
    Función de membresía sigmoidal.

    Parámetros
    ----------
    x : float, int o array-like
        Valor(es) de entrada donde evaluar la función.

    a : float
        Pendiente de la sigmoide.

        - a > 0 : función creciente.
        - a < 0 : función decreciente.

    c : float
        Punto de inflexión (μ = 0.5).

    Retorna
    -------
    float o np.ndarray
        Grado de pertenencia en el intervalo [0,1].

    Fórmula
    -------
        μ(x) = 1 / (1 + exp(-a(x-c)))

    Ejemplo
    --------
    >>> import numpy as np
    >>> x = np.linspace(-5,5,100)
    >>> y = sigmoide(x,2,0)
    """

    # Guardar si la entrada es escalar
    escalar = np.isscalar(x)

    # Convertir a ndarray
    x = np.asarray(x, dtype=float)

    # Calcular la función sigmoide
    y = 1.0 / (1.0 + np.exp(-a * (x - c)))

    # Si la entrada era escalar, devolver float
    if escalar:
        return float(y)

    return y