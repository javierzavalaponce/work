import numpy as np
import pickle
from collections import defaultdict

class MarkovDecisionProcess:
    def __init__(self, state_space_bins, actions, alpha=0.1, gamma=0.95, epsilon=0.1):
        """
        state_space_bins: dict con los límites de discretización para cada dimensión del estado
        actions: lista de acciones posibles (ej: [0, 1] donde 0=swing-up, 1=estabilización)
        alpha: tasa de aprendizaje (learning rate)
        gamma: factor de descuento (discount factor)
        epsilon: factor de exploración (epsilon-greedy)
        """
        self.state_bins = state_space_bins
        self.actions = actions
        self.alpha = alpha
        self.gamma = gamma
        self.epsilon = epsilon
        
        # Tabla Q: (estado_discretizado, acción) -> valor
        self.q_table = defaultdict(lambda: np.zeros(len(actions)))
        
        # Historial para análisis
        self.history = {'states': [], 'actions': [], 'rewards': []}
        
    def discretize_state(self, state):
        """
        Convierte un estado continuo (vector) en un índice discreto para la tabla Q
        state = [theta1, omega1, theta2, omega2]
        """
        discretized = []
        for i, (key, (low, high, bins)) in enumerate(self.state_bins.items()):
            if i < len(state):
                value = state[i]
                # Clipping para mantener dentro de los límites
                value = np.clip(value, low, high)
                # Discretización lineal
                bin_idx = int(np.floor((value - low) / (high - low) * bins))
                bin_idx = min(bin_idx, bins - 1)
                discretized.append(bin_idx)
        return tuple(discretized)
    
    def get_action(self, state, explore=True):
        """
        Selecciona una acción usando política epsilon-greedy
        """
        state_key = self.discretize_state(state)
        
        if explore and np.random.random() < self.epsilon:
            # Exploración: acción aleatoria
            action_idx = np.random.randint(len(self.actions))
        else:
            # Explotación: mejor acción según Q
            action_idx = np.argmax(self.q_table[state_key])
        
        return action_idx, self.actions[action_idx]
    
    def update_q_table(self, state, action_idx, reward, next_state):
        """
        Actualiza la tabla Q usando la fórmula de Q-Learning
        Q(s,a) = Q(s,a) + alpha * (reward + gamma * max(Q(s',a')) - Q(s,a))
        """
        state_key = self.discretize_state(state)
        next_state_key = self.discretize_state(next_state)
        
        current_q = self.q_table[state_key][action_idx]
        max_next_q = np.max(self.q_table[next_state_key])
        
        new_q = current_q + self.alpha * (reward + self.gamma * max_next_q - current_q)
        self.q_table[state_key][action_idx] = new_q
        
        # Guardar en historial
        self.history['states'].append(state)
        self.history['actions'].append(action_idx)
        self.history['rewards'].append(reward)
    
    def save_model(self, filename):
        """
        Guarda la tabla Q en un archivo para uso embebido
        """
        # Convertir defaultdict a dict para serialización
        serializable_q = dict(self.q_table)
        with open(filename, 'wb') as f:
            pickle.dump(serializable_q, f)
    
    def load_model(self, filename):
        """
        Carga una tabla Q pre-entrenada
        """
        with open(filename, 'rb') as f:
            self.q_table = defaultdict(lambda: np.zeros(len(self.actions)), pickle.load(f))

