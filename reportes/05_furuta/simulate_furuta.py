import numpy as np
import matplotlib.pyplot as plt
from furuta_models import FurutaPendulum
from sensor_fusion import SensorFusion
from markov_decision import MarkovDecisionProcess
import time

# ============================
# CONFIGURACIÓN DEL SISTEMA
# ============================

# Parámetros físicos del péndulo de Furuta
params = {
    'm1': 0.5,      # kg
    'm2': 0.3,      # kg
    'l1': 0.3,      # m
    'l2': 0.4,      # m
    'J1': 0.01,     # kg*m^2
    'J2': 0.02,     # kg*m^2
    'b1': 0.01,     # fricción viscosa
    'b2': 0.005,    # fricción viscosa
    'g': 9.81       # m/s^2
}

# Controladores
class SwingUpController:
    def __init__(self, E_target, k_energy):
        self.E_target = E_target  # Energía objetivo para swing-up
        self.k_energy = k_energy  # Ganancia del controlador de energía
    
    def compute_torque(self, state):
        theta1, omega1, theta2, omega2 = state
        # Energía actual del péndulo
        E = 0.5 * params['m2'] * params['l2']**2 * omega2**2 + params['m2'] * params['g'] * params['l2'] * (1 - np.cos(theta2))
        # Par de swing-up (basado en energía)
        torque = self.k_energy * (self.E_target - E) * np.sign(omega2 * np.cos(theta2))
        return np.clip(torque, -1.0, 1.0)

class LQRController:
    def __init__(self, K):
        self.K = K  # Matriz de ganancias LQR [K1, K2, K3, K4]
    
    def compute_torque(self, state):
        # Asume que el estado es [theta1, omega1, theta2, omega2]
        torque = -np.dot(self.K, state)
        return np.clip(torque, -1.0, 1.0)

# ============================
# INICIALIZACIÓN DE MÓDULOS
# ============================

# Modelo del sistema
furuta = FurutaPendulum(params)

# Filtro sensorial
sensor = SensorFusion(sampling_freq=100)

# Controladores
swing_up = SwingUpController(E_target=params['m2']*params['g']*params['l2'], k_energy=10.0)
K_lqr = np.array([10, 2, 50, 5])  # Ganancias LQR (ajustar según modelo)
lqr = LQRController(K_lqr)

# MDP para decisión de conmutación
state_bins = {
    'theta1': (-np.pi, np.pi, 20),
    'omega1': (-10, 10, 10),
    'theta2': (-np.pi, np.pi, 30),
    'omega2': (-20, 20, 15)
}
actions = [0, 1]  # 0 = Swing-Up, 1 = LQR Estabilización
mdp = MarkovDecisionProcess(state_bins, actions, alpha=0.1, gamma=0.9, epsilon=0.3)

# ============================
# FUNCIÓN DE RECOMPENSA
# ============================

def compute_reward(state, action_idx, torque):
    theta1, omega1, theta2, omega2 = state
    reward = 0.0
    
    # Recompensa por mantener el péndulo vertical (theta2 ≈ 0)
    reward += -abs(theta2) * 5.0
    
    # Penalización por oscilaciones del brazo
    reward += -abs(theta1) * 0.5
    
    # Penalización por consumo de corriente (usar medición real)
    reward += -abs(torque) * 0.1
    
    # Bonus por estabilización exitosa
    if abs(theta2) < 0.1 and abs(omega2) < 0.5:
        reward += 10.0
    
    # Penalización por fallo (péndulo toca tope)
    if abs(theta2) > np.pi * 0.8:
        reward -= 20.0
    
    return reward

# ============================
# SIMULACIÓN PRINCIPAL
# ============================

def run_simulation(episodes=5, steps_per_episode=500, dt=0.02):
    """
    Ejecuta la simulación del péndulo de Furuta con MDP
    """
    total_rewards = []
    
    for episode in range(episodes):
        print(f"Episodio {episode+1}/{episodes}")
        
        # Estado inicial: péndulo colgando (estable)
        state = np.array([0.0, 0.0, np.pi, 0.0])  # theta2 = pi (colgando)
        torque = 0.0
        episode_reward = 0
        
        # Variables para el filtro complementario
        gyro_angle = state[2]  # theta2 del péndulo
        
        for step in range(steps_per_episode):
            # 1. Seleccionar acción (controlador) usando MDP
            action_idx, action = mdp.get_action(state, explore=(episode < 3))
            
            # 2. Ejecutar controlador seleccionado
            if action == 0:  # Swing-Up
                torque = swing_up.compute_torque(state)
            else:  # LQR
                # Ajustar estado para LQR: theta2 debe ser 0 (vertical)
                state_lqr = [state[0], state[1], state[2] - np.pi, state[3]]
                torque = lqr.compute_torque(state_lqr)
            
            # 3. Simular dinámica del sistema
            next_state = furuta.dynamics(state, torque, dt)
            
            # 4. Simular medición de sensores con ruido
            # Simular acelerómetros
            accel_x = np.sin(state[2]) * 9.81 + np.random.normal(0, 0.1)
            accel_y = np.cos(state[2]) * 9.81 + np.random.normal(0, 0.1)
            accel_z = np.random.normal(0, 0.05)
            
            # Estimación de ángulo por acelerómetro
            accel_angle = sensor.get_angle_from_accel(accel_x, accel_y, accel_z)[0]
            
            # Filtro complementario para mejorar estimación
            filtered_theta2 = sensor.complementary_filter(gyro_angle, accel_angle, dt)
            
            # Simular medición de corriente (torque * factor de escala + ruido)
            current_measure = abs(torque) * 0.5 + np.random.normal(0, 0.05)
            filtered_current = sensor.filter_current(current_measure)
            
            # 5. Calcular recompensa
            reward = compute_reward(next_state, action_idx, torque)
            episode_reward += reward
            
            # 6. Actualizar tabla Q del MDP
            mdp.update_q_table(state, action_idx, reward, next_state)
            
            # 7. Avanzar el estado
            state = next_state
            gyro_angle = filtered_theta2
            
            # Condición de parada temprana (si se estabiliza)
            if abs(state[2] - np.pi) < 0.05 and abs(state[3]) < 0.1:
                print(f"  ¡Estabilizado en paso {step}!")
                break
        
        total_rewards.append(episode_reward)
        print(f"  Recompensa total: {episode_reward:.2f}")
        
        # Reducir exploración con el tiempo
        mdp.epsilon = max(0.05, mdp.epsilon * 0.95)
    
    return total_rewards

# ============================
# EJECUTAR SIMULACIÓN
# ============================

if __name__ == "__main__":
    print("Iniciando simulación de Péndulo de Furuta con MDP...")
    start_time = time.time()
    
    rewards = run_simulation(episodes=10, steps_per_episode=1000, dt=0.02)
    
    elapsed = time.time() - start_time
    print(f"Simulación completada en {elapsed:.2f} segundos")
    print(f"Recompensas por episodio: {rewards}")
    print(f"Recompensa promedio: {np.mean(rewards):.2f}")
    
    # Guardar modelo entrenado
    mdp.save_model('furuta_mdp_model.pkl')
    print("Modelo MDP guardado en 'furuta_mdp_model.pkl'")



