import numpy as np
import matplotlib.pyplot as plt
import control as ct

# 1. Definición de parámetros
k = 2.0
tau = 0.7
s = ct.TransferFunction.s

# 2. Bloques del sistema
H = k                                # Controlador
G = 1 / (s + 1)                      # Planta
num_pade, den_pade = ct.pade(tau, 5)
Retardo = ct.tf(num_pade, den_pade)  # Bloque de retardo e^(-tau*s)

# 3. Armado del lazo cerrado
# ¡AQUÍ ESTÁ LA MAGIA! El retardo va ANTES de la planta.
# El controlador manda la señal, pero la planta no la recibe hasta que pasa el retardo.
Camino_Directo = H * Retardo * G 
Sistema_LC = ct.feedback(Camino_Directo, 1) # Realimentación unitaria

# 4. Simulación
T = np.linspace(0, 15, 1000)
t_out, y_out = ct.step_response(Sistema_LC, T)

# 5. Gráfica
plt.figure(figsize=(8, 4))
plt.plot(t_out, y_out, label='Salida Y(t)', color='blue', linewidth=2)
plt.axhline(1, color='r', linestyle='--', label='Referencia')
plt.axvline(tau, color='gray', linestyle=':', label=f'Fin del tiempo muerto (t={tau}s)')
plt.title('Caso 3: Retardo entre Controlador y Planta (Tiempo Muerto)')
plt.xlabel('Tiempo (s)')
plt.ylabel('Amplitud')
plt.grid(True)
plt.legend()
plt.show()


