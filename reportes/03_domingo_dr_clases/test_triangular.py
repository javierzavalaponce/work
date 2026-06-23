import numpy as np
import matplotlib.pyplot as plt
import fuz as fz

x = np.linspace(0, 6, 1000)
y = fz.triangular(x, 1, 5)

x0 = 1
x1 = 5
xc = (x0 + x1) / 2

plt.plot(x, y, linewidth=2)

# limpiar eje X
plt.xticks([])


# línea vertical punteada en el centro
plt.axvline(xc, linestyle='--', color='gray', alpha=0.6)

# etiquetas
plt.annotate(r"$x_0$", xy=(x0, 0), xytext=(0, -10),
             textcoords='offset points', ha='center')

plt.annotate(r"$x_1$", xy=(x1, 0), xytext=(0, -10),
             textcoords='offset points', ha='center')

plt.annotate(r"$x_c$", xy=(xc, 0), xytext=(0, -10),
             textcoords='offset points', ha='center')

plt.annotate(r"$\mu=1$", xy=(xc, 1), xytext=(0, 10),
             textcoords='offset points', ha='center')

# estilo de fondo
plt.grid(True, alpha=0.3)

plt.ylim(-0.05, 1.1)

plt.savefig("fig.png", bbox_inches='tight')
plt.show()