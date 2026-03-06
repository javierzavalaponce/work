import numpy as np
import matplotlib.pyplot as plt

theta = np.linspace(0, 2*np.pi, 200)

z = np.exp(1j*theta)

x = z.real
y = z.imag

plt.figure()
plt.plot(x, y)
plt.axhline(0)
plt.axvline(0)

plt.gca().set_aspect('equal', adjustable='box')

plt.title("Movimiento generado por e^(iθ)")
plt.xlabel("Parte real")
plt.ylabel("Parte imaginaria")

plt.grid()
plt.tight_layout()
plt.savefig("circ.png", dpi=300)
