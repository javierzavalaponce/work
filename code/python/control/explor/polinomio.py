import numpy as np
import matplotlib.pyplot as plt

# Coeficientes para  y =  x^3 - 15x -4 
coeficientes = [1, 0, -15, -4]

# Crear puntos x
x = np.linspace(-5, 5, 10000)
y = np.polyval(coeficientes, x)

# Graficar
plt.figure()
plt.plot(x, y)
plt.grid(True)
plt.xlabel('x')
plt.ylabel('P(x)')
plt.title('Mi Polinomio')
plt.tight_layout()
plt.savefig("file.png", dpi=300)




