import numpy as np
import matplotlib.pyplot as plt
import fuz as fz

x = np.linspace(0, 10, 1000)
y = fz.sigmoide(x, 0.6,5)

plt.plot(x, y, linewidth=2)

# limpiar eje X
plt.xticks([])

c = 5
# línea vertical punteada en el centro
plt.axvline(c, linestyle='--', color='gray', alpha=0.6)



# etiquetas
plt.annotate(r"$c$ punto de inflexión", xy=(c, 0), xytext=(0, -10),
             textcoords='offset points', ha='center')

plt.annotate(r"pendiente a=0.6", xy=(c-3.7, 0), xytext=(0, -10),
             textcoords='offset points', ha='center')



# estilo de fondo
plt.grid(True, alpha=0.3)

plt.ylim(-0.05, 1.1)

plt.savefig("fig.png", bbox_inches='tight')
plt.show()