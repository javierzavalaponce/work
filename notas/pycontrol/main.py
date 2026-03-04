import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from control import tf, step_response, bode

# Definir función de transferencia: numerador [1], denominador [1, 1]
G = tf([1], [1, 1])

# Respuesta al escalón
t, y = step_response(G)
plt.figure()
plt.plot(t, y)
plt.title('Respuesta al Escalón')
plt.xlabel('Tiempo')
plt.ylabel('Salida')
plt.grid(True)
plt.show()

# Diagrama de Bode
plt.figure()
bode(G)
plt.show()



