import numpy as np
import matplotlib.pyplot as plt

# función compleja
def f(z):
    return 1/z

# crear grid
x = np.linspace(-2,2,400)
y = np.linspace(-2,2,400)

plt.figure(figsize=(6,6))

# líneas verticales
for a in np.linspace(-2,2,15):
    z = a + 1j*y
    w = f(z)
    plt.plot(w.real, w.imag)

# líneas horizontales
for b in np.linspace(-2,2,15):
    z = x + 1j*b
    w = f(z)
    plt.plot(w.real, w.imag)

plt.axhline(0)
plt.axvline(0)
plt.gca().set_aspect('equal')

plt.title("Transformación del plano complejo por f(z)=1/z")
plt.tight_layout()
plt.savefig("file.png", dpi=300)
