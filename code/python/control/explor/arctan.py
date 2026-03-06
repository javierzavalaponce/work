import math
import numpy as np

# arctan(x)
angulo = math.atan(0.5)      # devuelve el ángulo en radianes
angulo_deg = math.degrees(angulo)

# arctan(y/x) con manejo de cuadrantes
angulo2 = math.atan2(11, 2)   # también en radianes
angulo_deg = math.degrees(angulo2)
print(angulo2)
print(angulo_deg)



vector = np.array([2, 11])
longitud = np.linalg.norm(vector)  # Resultado: 5.0
print(longitud)
num = 5*math.sqrt(5)
print("-------")
print(num)