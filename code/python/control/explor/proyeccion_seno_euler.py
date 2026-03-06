import numpy as np
import matplotlib.pyplot as plt

t = np.linspace(0, 2*np.pi, 200)

z = np.exp(1j*t)

x = z.real
y = z.imag

plt.figure()

plt.subplot(1,2,1)
plt.plot(x, y)
plt.title("Movimiento circular")
plt.axhline(0)
plt.axvline(0)
plt.gca().set_aspect('equal', adjustable='box')
plt.grid()

plt.subplot(1,2,2)
plt.plot(t, y)
plt.title("Proyección → señal seno")
plt.xlabel("tiempo")
plt.grid()

plt.tight_layout()
plt.savefig("file.png", dpi=300)
