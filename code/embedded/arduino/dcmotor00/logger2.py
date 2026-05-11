import serial
import time
import math
import os

# ==============================
# CONFIGURACIÓN
# ==============================
PORT = '/dev/ttyACM2'
BAUDRATE = 115200

# ==============================
# SERIAL
# ==============================
ser = serial.Serial(PORT, BAUDRATE, timeout=1)
time.sleep(2)

# ==============================
# FUNCIONES
# ==============================

def clear():
    os.system('clear')

def draw_vector(angle_deg, size=11):
    """
    Dibuja un vector rotando en CLI.
    """

    grid = [[' ' for _ in range(size)] for _ in range(size)]

    cx = size // 2
    cy = size // 2

    # convertir ángulo a radianes
    theta = math.radians(angle_deg)

    # longitud del vector
    r = size // 2 - 1

    # coordenadas punta
    x = int(cx + r * math.cos(theta))
    y = int(cy - r * math.sin(theta))

    # Bresenham simple
    steps = max(abs(x - cx), abs(y - cy))

    for i in range(steps + 1):
        t = i / steps if steps != 0 else 0
        px = int(cx + (x - cx) * t)
        py = int(cy + (y - cy) * t)

        if 0 <= px < size and 0 <= py < size:
            grid[py][px] = '*'

    # centro
    grid[cy][cx] = 'O'

    # punta
    if 0 <= x < size and 0 <= y < size:
        grid[y][x] = 'X'

    return '\n'.join(''.join(row) for row in grid)

# ==============================
# LOOP PRINCIPAL
# ==============================

print("Leyendo AS5600...\n")

try:
    while True:

        if ser.in_waiting:

            line = ser.readline().decode().strip()

            try:
                parts = line.split(',')

                if len(parts) >= 3:

                    rps = float(parts[0])
                    rpm = float(parts[1])
                    angle = float(parts[2])

                    clear()

                    print("=" * 50)
                    print("VECTOR ANGULAR - AS5600")
                    print("=" * 50)

                    print(f"\nÁngulo : {angle:.1f}°")
                    print(f"RPM    : {rpm:.1f}")
                    print(f"RPS    : {rps:.2f}\n")

                    print(draw_vector(angle))

            except:
                pass

        time.sleep(0.01)

except KeyboardInterrupt:
    print("\nPrograma detenido")
    ser.close()