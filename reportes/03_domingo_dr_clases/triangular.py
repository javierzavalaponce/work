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

    y = np.clip(y,0,1)

    if escalar:
        return float(y)

    return y