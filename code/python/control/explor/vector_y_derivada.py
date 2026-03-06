import numpy as np
import matplotlib.pyplot as plt

t = np.linspace(0, 2*np.pi, 20)

plt.figure()

# dibujar círculo
theta = np.linspace(0, 2*np.pi, 200)
plt.plot(np.cos(theta), np.sin(theta))

for ti in t:
    
    # vector posición
    x = np.cos(ti)
    y = np.sin(ti)

    # derivada (velocidad)
    vx = -np.sin(ti)
    vy = np.cos(ti)

    # vector posición
    plt.arrow(0, 0, x, y, head_width=0.05, length_includes_head=True)

    # vector velocidad
    plt.arrow(x, y, vx*0.4, vy*0.4, head_width=0.05, length_includes_head=True)

plt.axhline(0)
plt.axvline(0)

plt.gca().set_aspect('equal', adjustable='box')

plt.title("Vector posición y su derivada (velocidad)")
plt.grid()

plt.tight_layout()
plt.savefig("file.png", dpi=300)
