import serial
import sys
import time

# --- Validar argumentos ---
if len(sys.argv) < 3:
    print(f"Uso: python {sys.argv[0]} archivo.txt num_muestras")
    sys.exit(1)

archivo_salida = sys.argv[1]
try:
    num_muestras = int(sys.argv[2])
except ValueError:
    print("num_muestras debe ser un número entero")
    sys.exit(1)

# --- Configurar puerto serie ---
# Timeout corto para no bloquear si Arduino tarda un microsegundo
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.05)
data = []

print(f"Capturando {num_muestras} muestras...")

# Pequeño delay para asegurarnos de que Arduino haya arrancado y comenzado a enviar datos
time.sleep(0.5)

start_time = time.time()
last_print = 0

while len(data) < num_muestras:
    line = ser.readline()  # Espera máximo 50 ms
    if not line:
        continue  # Timeout expiró, volver a intentar

    try:
        # Decodificar y limpiar línea
        line_str = line.decode('ascii', errors='ignore').strip()
        if line_str:
            data.append(float(line_str))
    except ValueError:
        # Ignorar líneas corruptas
        pass

    # Mostrar progreso cada 0.1 s
    if time.time() - last_print > 0.1:
        last_print = time.time()
        progreso = (len(data) / num_muestras) * 100
        print(f"\rProgreso: {len(data)}/{num_muestras} muestras ({progreso:.1f}%)", end='')

ser.close()
end_time = time.time()

# --- Guardar datos ---
with open(archivo_salida, 'w') as f:
    for valor in data:
        f.write(f"{valor}\n")

print(f"\nCaptura completada en {end_time - start_time:.3f}s")
print(f"Datos guardados en {archivo_salida}")

