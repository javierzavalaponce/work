import numpy as np
import matplotlib.pyplot as plt

t = np.linspace(-20, 60, 2000)

# frecuencias cercanas
w1 = 5
w2 = 5.3

z1 = np.exp(1j*w1*t)
z2 = np.exp(1j*w2*t)

signal = (z1 + z2).real

plt.figure()

plt.plot(t, signal)

plt.title("Batidos generados por dos rotaciones complejas")
plt.xlabel("tiempo")
plt.ylabel("amplitud")

plt.grid()
plt.tight_layout()
plt.savefig("file.png", dpi=300)
