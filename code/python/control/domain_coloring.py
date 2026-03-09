import numpy as np
import matplotlib.pyplot as plt

# grid del plano complejo
N = 600
x = np.linspace(-2,2,N)
y = np.linspace(-2,2,N)
X,Y = np.meshgrid(x,y)

Z = X + 1j*Y

# evitar division por cero
Z[N//2,N//2] = 1e-6

W = 1/Z

# fase y magnitud
phase = np.angle(W)
mag = np.abs(W)

# normalizaciones
phase_norm = (phase + np.pi)/(2*np.pi)
mag_norm = np.tanh(mag)

plt.imshow(phase_norm * mag_norm)
plt.title("Domain coloring de f(z)=1/z")
plt.axis("off")
plt.tight_layout()
plt.savefig("file.png", dpi=300)
