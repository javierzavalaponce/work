import numpy as np
import matplotlib.pyplot as plt

fig, ax = plt.subplots()

# Vectores
x = np.array([1, 2])
y = np.array([3, 4])

ax.quiver(
    0, 0,
    x[0], x[1],
    angles="xy",
    scale_units="xy",
    scale=1
)

ax.quiver(
    0, 0,
    y[0], y[1],
    angles="xy",
    scale_units="xy",
    scale=1
)

# Etiquetas
ax.text(
    0.3,
    2.1,
    r"$\mathbf{x}=(1,2)$"
)
#ax.text(1, 2, r"$\mathbf{x}=(1,2)$")
ax.text(3, 4, r"$\mathbf{y}=(3,4)$")

# Ejes
ax.axhline(0)
ax.axvline(0)

# Límites
ax.set_xlim(-1, 5)
ax.set_ylim(-1, 5)

# Misma escala
ax.set_aspect("equal")

plt.savefig(
    "pp34.png",
    bbox_inches="tight"
)

ax.grid()
plt.show()



