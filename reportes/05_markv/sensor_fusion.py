import numpy as np
from scipy.signal import butter, lfilter

class SensorFusion:
    def __init__(self, sampling_freq=100, accel_noise=0.01):
        """
        Filtro complementario + Filtro paso bajo para acelerómetros
        """
        self.sampling_freq = sampling_freq
        self.alpha = 0.98  # Factor de confianza para el filtro complementario
        self.accel_noise = accel_noise
        
        # Diseño de filtro Butterworth para corriente
        self.b, self.a = butter(2, 10, btype='low', fs=sampling_freq)
        self.current_buffer = []
        
    def get_angle_from_accel(self, accel_x, accel_y, accel_z):
        """
        Calcula el ángulo de inclinación a partir de las lecturas del acelerómetro
        Asume que el eje Y apunta hacia adelante y Z hacia arriba
        """
        # Ángulo respecto al eje Y (para el péndulo)
        angle_y = np.arctan2(accel_x, np.sqrt(accel_y**2 + accel_z**2))
        # Ángulo respecto al eje X (para el brazo)
        angle_x = np.arctan2(accel_y, np.sqrt(accel_x**2 + accel_z**2))
        return angle_x, angle_y
    
    def complementary_filter(self, gyro_angle, accel_angle, dt):
        """
        Filtro complementario: combina giroscopio (alta frecuencia) con acelerómetro (baja frecuencia)
        """
        # Predicción del giroscopio
        predicted_angle = gyro_angle  # Asume que gyro_angle ya está integrado
        # Combinación con acelerómetro
        filtered_angle = self.alpha * predicted_angle + (1 - self.alpha) * accel_angle
        return filtered_angle
    
    def filter_current(self, current_reading):
        """
        Filtra la lectura de corriente para eliminar ruido de conmutación del PWM
        """
        self.current_buffer.append(current_reading)
        if len(self.current_buffer) > 10:
            self.current_buffer.pop(0)
        return np.mean(self.current_buffer)
    
    def kalman_filter_1d(self, measurement, prev_estimate, prev_covariance, process_noise=1e-3):
        """
        Filtro de Kalman 1D para estimar ángulo a partir de mediciones ruidosas
        """
        # Predicción
        current_estimate = prev_estimate
        current_covariance = prev_covariance + process_noise
        
        # Actualización
        kalman_gain = current_covariance / (current_covariance + self.accel_noise)
        updated_estimate = current_estimate + kalman_gain * (measurement - current_estimate)
        updated_covariance = (1 - kalman_gain) * current_covariance
        
        return updated_estimate, updated_covariance

