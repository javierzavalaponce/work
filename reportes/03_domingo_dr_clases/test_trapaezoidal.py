import numpy as np
import matplotlib.pyplot as plt
import fuz as fz

x = np.linspace(0, 6, 1000)
y = fz.trapezoidal(x, 1,2,4,5)

a = 1
b = 2
c = 4
d = 5

plt.plot(x, y, linewidth=2)

# limpiar eje X
plt.xticks([])

# estilo de fondo
plt.grid(True, alpha=0.3)

plt.ylim(-0.05, 1.1)


# línea vertical punteada en el centro
plt.axvline(b, linestyle='--', color='gray', alpha=0.6)
plt.axvline(c, linestyle='--', color='gray', alpha=0.6)


# etiquetas
plt.annotate(r"$a$", xy=(a, 0), xytext=(0, -10),
             textcoords='offset points', ha='center')

plt.annotate(r"$b$", xy=(b, 0), xytext=(0, -10),
             textcoords='offset points', ha='center')

plt.annotate(r"$c$", xy=(c, 0), xytext=(0, -10),
             textcoords='offset points', ha='center')

plt.annotate(r"$d$", xy=(d, 0), xytext=(0, -10),
             textcoords='offset points', ha='center')



plt.savefig("fig2.png", bbox_inches='tight')
plt.show()