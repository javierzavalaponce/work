# furuta_models.py - Versión simplificada para simulación

import numpy as np

class FurutaPendulum:
    def __init__(self, params):
        """
        params: dict con:
            - m1: masa del brazo (kg)
            - m2: masa del péndulo (kg)
            - l1: longitud del brazo (m)
            - l2: longitud del péndulo (m)
            - J1: inercia del brazo (kg*m^2)
            - J2: inercia del péndulo (kg*m^2)
            - b1: fricción viscosa del brazo
            - b2: fricción viscosa del péndulo
            - g: gravedad (9.81 m/s^2)
        """
        self.params = params
        
    def dynamics(self, state, torque, dt):
        """
        state = [theta1, omega1, theta2, omega2]
        theta1: ángulo del brazo (rad)
        omega1: velocidad angular del brazo (rad/s)
        theta2: ángulo del péndulo respecto a la vertical (rad)
        omega2: velocidad angular del péndulo (rad/s)
        torque: par aplicado al motor (N*m)
        dt: paso de tiempo (s)
        """
        # Extraer parámetros
        m1, m2, l1, l2, J1, J2, b1, b2, g = self.params.values()
        
        theta1, omega1, theta2, omega2 = state
        
        # Matriz de inercia M (2x2) y vector de fuerzas no lineales C
        # Ecuaciones derivadas del método de Lagrange
        
        M11 = J1 + m2 * l1**2 * np.sin(theta2)**2
        M12 = m2 * l1 * l2 * np.cos(theta2)
        M21 = m2 * l1 * l2 * np.cos(theta2)
        M22 = J2 + m2 * l2**2
        
        C1 = (m2 * l1**2 * np.sin(theta2) * np.cos(theta2) * omega2**2 
              - 2 * m2 * l1 * l2 * np.sin(theta2) * omega1 * omega2
              + b1 * omega1)
        C2 = (m2 * l1 * l2 * np.sin(theta2) * omega1**2
              - m2 * g * l2 * np.sin(theta2)
              + b2 * omega2)
        
        # Vector de fuerzas generalizadas
        Q = np.array([torque, 0])
        C_vec = np.array([C1, C2])
        M = np.array([[M11, M12], [M21, M22]])
        
        # Aceleraciones: alpha = M^{-1} (Q - C)
        accelerations = np.linalg.solve(M, Q - C_vec)
        
        # Integración con Euler (para simulación rápida)
        new_theta1 = theta1 + omega1 * dt
        new_omega1 = omega1 + accelerations[0] * dt
        new_theta2 = theta2 + omega2 * dt
        new_omega2 = omega2 + accelerations[1] * dt
        
        return np.array([new_theta1, new_omega1, new_theta2, new_omega2])

