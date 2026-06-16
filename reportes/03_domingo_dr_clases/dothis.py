import numpy as np
t = np.linspace(0, 2*np.pi, 200)

import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 10, 1000)
coeficientes = [4, -40, 100, 0]
y = np.polyval(coeficientes, x)

plt.figure()
plt.plot(x, y)
plt.xlabel('x')
plt.ylabel('V(x)')
plt.grid(True)
plt.title('Volumen de la caja')
plt.savefig("file.png", dpi=300)


