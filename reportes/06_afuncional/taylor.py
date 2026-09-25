import numpy as np
import matplotlib.pyplot as plt
import math

# Dominio
x = np.linspace(-3, 3, 500)

# Función exacta
y_exacta = np.exp(x)

# Serie de Taylor de e^x
y_taylor = (
    1
    + x
    + x**2 / math.factorial(2)
    + x**3 / math.factorial(3)
)

# Gráfica
plt.figure(figsize=(8, 5))

plt.plot(x, y_exacta, label=r"$e^x$")
plt.plot(
    x,
    y_taylor,
    label=r"$1+x+\frac{x^2}{2!}+\frac{x^3}{3!}$"
)

plt.xlabel(r"$x$")
plt.ylabel(r"$f(x)$")
plt.title("Aproximación de Taylor de $e^x$")
plt.grid(True)
plt.legend()

# Guardar como PNG
plt.savefig("taylor_ex.png", dpi=300, bbox_inches="tight")

plt.show()

