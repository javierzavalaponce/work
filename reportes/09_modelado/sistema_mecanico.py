import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt

# 1. Definimos los parámetros (los mismos que usaste en XPP)
m1, m2 = 1.0, 2.0
B1, B2, B = 0.2, 0.3, 0.1
k1, k2, k = 10.0, 5.0, 8.0
f2 = 0.0

# 2. Definimos la función del sistema (el equivalente a las líneas de tu .ode)
def sistema(t, y):
    x1, v1, x2, v2 = y
    
    # Condición para el impulso de f1 (Fuerza de 50 durante 0.1 segundos)
    f1 = 50.0 if t < 0.1 else 0.0
    
    # Aceleraciones (tus ecuaciones despejadas)
    a1 = (f1 - (B1 + B)*v1 + B*v2 - (k1 + k)*x1 + k*x2) / m1
    a2 = (-f2 + B*v1 - (B2 + B)*v2 + k*x1 - (k2 + k)*x2) / m2
    
    # Retornamos las derivadas: dx1/dt, dv1/dt, dx2/dt, dv2/dt
    return [v1, a1, v2, a2]

# 3. Condiciones iniciales (el golpe inicial)
y0 = [0.0, 0.0, 0.0, 0.0] # x1=0, v1=0, x2=0, v2=0

# 4. Intervalo de tiempo (de 0 a 20 segundos, con 1000 puntos)
t_span = (0, 20)
t_eval = np.linspace(t_span[0], t_span[1], 1000)

# 5. Resolvemos la ecuación diferencial
sol = solve_ivp(sistema, t_span, y0, t_eval=t_eval, method='RK45')

# 6. Gráficamos los resultados
plt.figure(figsize=(10, 5))
plt.plot(sol.t, sol.y[0], label='x1 (Masa 1)')
plt.plot(sol.t, sol.y[2], label='x2 (Masa 2)')
plt.title('Simulación de las dos masas')
plt.xlabel('Tiempo (s)')
plt.ylabel('Desplazamiento')
plt.legend()
plt.grid(True)
plt.show()



