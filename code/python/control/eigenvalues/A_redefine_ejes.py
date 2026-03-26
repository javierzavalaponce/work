import numpy as np
import matplotlib.pyplot as plt

A = np.array([[3, 1],
              [1, 2]])

x = np.array([1, 1])

for _ in range(20):
    x = A @ x
    print(x)

print("----")

# Base canónica
e1 = np.array([1, 0])
e2 = np.array([0, 1])

# Transformación de los ejes
Ae1 = A @ e1
Ae2 = A @ e2

# Crear círculo
theta = np.linspace(0, 2*np.pi, 100)
circle = np.array([np.cos(theta), np.sin(theta)])


# Transformar círculo
circle_transformed = A @ circle

# Plot
plt.figure()
plt.axhline(0)
plt.axvline(0)

# círculo original
plt.plot(circle[0], circle[1], label="Original")

# círculo transformado
plt.plot(circle_transformed[0], circle_transformed[1], label="Transformado")

# ejes originales
plt.quiver(0, 0, e1[0], e1[1], angles='xy', scale_units='xy', scale=1)
plt.quiver(0, 0, e2[0], e2[1], angles='xy', scale_units='xy', scale=1)

# ejes transformados
plt.quiver(0, 0, Ae1[0], Ae1[1], angles='xy', scale_units='xy', scale=1)
plt.quiver(0, 0, Ae2[0], Ae2[1], angles='xy', scale_units='xy', scale=1)

plt.legend()
plt.gca().set_aspect('equal')
plt.title("Transformación lineal A")
plt.show()



