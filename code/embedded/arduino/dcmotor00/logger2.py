import serial
import time

# Configurar puerto serial
ser = serial.Serial('/dev/ttyACM2', 115200, timeout=1)
time.sleep(2)  # Esperar a que Arduino reinicie

print("=" * 50)
print("LECTOR DE RPM - AS5600")
print("=" * 50)
print()

try:
    while True:
        if ser.in_waiting:
            # Leer línea del Arduino
            line = ser.readline().decode().strip()
            
            # Saltar líneas de encabezado
            if line and not line.startswith("AS5600") and not line.startswith("Format"):
                try:
                    # Separar valores
                    parts = line.split(',')
                    if len(parts) >= 3:
                        rps = float(parts[0])
                        rpm = float(parts[1])
                        angle = float(parts[2])
                        
                        # Crear barra visual
                        bar_length = min(30, int(rps * 5))
                        bar = "█" * bar_length + "░" * (30 - bar_length)
                        
                        # Mostrar en pantalla
                        print(f"RPS: {rps:5.2f} | RPM: {rpm:5.0f} | Ángulo: {angle:3.0f}° [{bar}]", end='\r')
                        
                except (ValueError, IndexError):
                    pass
        
        time.sleep(0.01)  # Pequeña pausa
        
except KeyboardInterrupt:
    print("\n\n✅ Programa detenido")
    ser.close()