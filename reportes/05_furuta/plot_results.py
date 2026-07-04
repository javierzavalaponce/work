import matplotlib.pyplot as plt
import numpy as np
import pickle

# Cargar historial del MDP
with open('furuta_mdp_model.pkl', 'rb') as f:
    q_table = pickle.load(f)

# Visualizar política aprendida (para debug)
def plot_policy(q_table, state_bins):
    """
    Visualiza la política en función de theta2 y omega2
    (manteniendo theta1 y omega1 fijos)
    """
    theta2_bins = state_bins['theta2'][2]
    omega2_bins = state_bins['omega2'][2]
    
    policy_grid = np.zeros((theta2_bins, omega2_bins))
    
    for i in range(theta2_bins):
        for j in range(omega2_bins):
            # Crear un estado ficticio
            state_key = (0, 0, i, j)  # theta1=0, omega1=0
            if state_key in q_table:
                policy_grid[i, j] = np.argmax(q_table[state_key])
            else:
                policy_grid[i, j] = -1
    
    plt.figure(figsize=(10, 8))
    plt.imshow(policy_grid, origin='lower', aspect='auto', cmap='RdYlGn')
    plt.colorbar(label='Acción (0=Swing-Up, 1=LQR)')
    plt.xlabel('omega2 (velocidad angular péndulo)')
    plt.ylabel('theta2 (ángulo péndulo)')
    plt.title('Política de Conmutación MDP Aprendida')
    plt.show()

# Ejecutar visualización
if __name__ == "__main__":
    state_bins = {
        'theta1': (-np.pi, np.pi, 20),
        'omega1': (-10, 10, 10),
        'theta2': (-np.pi, np.pi, 30),
        'omega2': (-20, 20, 15)
    }
    plot_policy(q_table, state_bins)



