import numpy as np
import matplotlib.pyplot as plt

# Dominio
s = np.linspace(-10, 10, 2000)

# K(s) = -(s-2)(s-3)/(s-1)
num = np.polyval([-1, 5, -6], s)
den = np.polyval([1, -1], s)

K = num / den

# Derivada numérica
dK = np.gradient(K, s)

# Gráfica de K(s)
plt.figure()
plt.plot(s, K)
plt.title("K(s)")
plt.xlabel("s")
plt.ylabel("K")
plt.grid(True)
plt.ylim(-20, 20)

# Gráfica de dK/ds
plt.figure()
plt.plot(s, dK)
plt.title("dK/ds")
plt.xlabel("s")
plt.ylabel("dK/ds")
plt.grid(True)
plt.ylim(-10, 20)

plt.show()


