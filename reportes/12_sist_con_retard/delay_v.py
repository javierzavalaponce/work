import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, Circle, FancyArrowPatch
from matplotlib.animation import FuncAnimation

# ─── Parámetros ───
N = 4
G = 0.5
N_TOTAL = 40
INTERVAL = 600  # ms por frame (más lento para poder leer)

# Señal de entrada: un pulso en n=0 y otro en n=12
x = np.zeros(N_TOTAL)
x[0] = 1.0
x[12] = 0.8

# ─── Simulación ───
buf_hist = []
read_hist = []
write_hist = []
y_hist = np.zeros(N_TOTAL)
x_hist = x.copy()

buf = np.zeros(N)
w = 0
for n in range(N_TOTAL):
    d = buf[w]
    read_hist.append(d)
    buf[w] = x[n] + d * G
    write_hist.append(buf[w])
    y_hist[n] = x[n] + d
    buf_hist.append(buf.copy())
    w = (w + 1) % N

# ─── Configuración de la figura ───
fig, ax = plt.subplots(figsize=(14, 7))
ax.set_xlim(-2, 12)
ax.set_ylim(-3, 4)
ax.axis('off')
ax.set_title("Tu diagrama en acción: el viaje de la señal", fontsize=14, fontweight='bold')

# ─── Dibujo estático de los bloques ───

# 1. Punto de división de X
ax.plot(0, 1, 'ko', markersize=6, zorder=5)
ax.text(-0.3, 1.2, "X", fontsize=14, fontweight='bold')

# 2. Sumador Izquierdo
sum_left = Circle((2, 1), 0.4, fill=False, edgecolor='black', linewidth=2)
ax.add_patch(sum_left)
ax.text(2, 1, "+", fontsize=18, ha='center', va='center')

# 3. Buffer (cajas)
boxes = []
vals = []
for i in range(N):
    rect = Rectangle((3.5 + i*0.9, 0.6), 0.9, 0.8, facecolor='#e8ecf1', edgecolor='black', linewidth=1.5)
    ax.add_patch(rect)
    boxes.append(rect)
    txt = ax.text(3.95 + i*0.9, 1.0, "0.00", ha='center', va='center', fontsize=9, family='monospace')
    vals.append(txt)
ax.text(5.2, 1.7, "N = 4", fontsize=12, fontweight='bold', ha='center')
ax.text(5.2, 0.2, "BUFFER", fontsize=10, ha='center')

# 4. Sumador Derecho
sum_right = Circle((8, 1), 0.4, fill=False, edgecolor='black', linewidth=2)
ax.add_patch(sum_right)
ax.text(8, 1, "+", fontsize=18, ha='center', va='center')
ax.text(9.2, 1.2, "Y", fontsize=14, fontweight='bold')

# 5. Bloque de Feedback (g)
g_box = Rectangle((4.55, -1.4), 0.9, 0.7, facecolor='#fff3b0', edgecolor='black', linewidth=1.5)
ax.add_patch(g_box)
ax.text(5.0, -1.05, "g", fontsize=14, fontweight='bold', ha='center', va='center')

# --- Cables (líneas) ---
# X -> suma izquierda
ax.plot([0, 1.6], [1, 1], 'k-', linewidth=2)
# Suma izquierda -> buffer
ax.plot([2.4, 3.5], [1, 1], 'k-', linewidth=2)
# Buffer -> suma derecha (d)
ax.plot([7.1, 7.6], [1, 1], 'k-', linewidth=2)
ax.text(7.35, 1.3, "d", fontsize=12, style='italic')
# Suma derecha -> Y
ax.plot([8.4, 10], [1, 1], 'k-', linewidth=2)

# Cable Dry (X -> suma derecha)
ax.plot([0, 0], [1, 3], 'k-', linewidth=2) # sube
ax.plot([0, 8], [3, 3], 'k-', linewidth=2) # va a la derecha
ax.plot([8, 8], [3, 1.4], 'k-', linewidth=2) # baja al sumador

# Cable Feedback (d -> g -> suma izquierda)
ax.plot([7.1, 7.1], [1, -1.05], 'k-', linewidth=2) # baja desde d
ax.plot([7.1, 5.45], [-1.05, -1.05], 'k-', linewidth=2) # va a la izquierda hasta g
ax.plot([4.55, 2.0], [-1.05, -1.05], 'k-', linewidth=2) # sale de g y va a la izq
ax.plot([2.0, 2.0], [-1.05, 0.6], 'k-', linewidth=2) # sube al sumador izq
ax.text(2.3, -1.35, "g·d", fontsize=11, style='italic')

# ─── Elementos dinámicos (Puntos que viajan) ───
# Puntos para X (entrada directa), Feedback, y el Wet (salida del buffer)
# Usaremos "offsets" para dar la ilusión de viaje en el tiempo
dot_X = ax.text(0, 1, "0.0", color='blue', fontsize=11, fontweight='bold',
                bbox=dict(boxstyle="round,pad=0.1", fc="white", ec="blue", lw=1, alpha=0.8))
dot_F = ax.text(2.0, -1.05, "0.0", color='green', fontsize=11, fontweight='bold',
                bbox=dict(boxstyle="round,pad=0.1", fc="white", ec="green", lw=1, alpha=0.8))
dot_W = ax.text(7.1, 1, "0.0", color='red', fontsize=11, fontweight='bold',
                bbox=dict(boxstyle="round,pad=0.1", fc="white", ec="red", lw=1, alpha=0.8))

# ─── Animación ───
def update(frame):
    n = frame % N_TOTAL

    # Actualizar cajas del buffer
    for i in range(N):
        vals[i].set_text(f"{buf_hist[n][i]:.2f}")
        if (n - i) % N == 0: # resaltar la caja que se está escribiendo
            boxes[i].set_facecolor('#ffcccc')
        else:
            boxes[i].set_facecolor('#e8ecf1')

    # 1. Animación del punto X (Dry)
    # Viaja por el cable de arriba hasta el sumador derecho
    # Toma 4 frames llegar
    progress_X = min(frame % 8, 4) / 4.0 
    x_pos_X = progress_X * 8
    y_pos_X = 1 + progress_X * 2 if progress_X < 1 else 3
    if progress_X >= 1: 
        y_pos_X = 3 - (progress_X - 1) * 2 # baja al sumador
        x_pos_X = 8
    dot_X.set_position((x_pos_X, y_pos_X))
    dot_X.set_text(f"{x_hist[n]:.2f}")

    # 2. Animación del punto Feedback
    # Sale del cable d, baja, va a g, y sube al sumador izquierdo.
    progress_F = (frame % 8) / 8.0
    if progress_F < 0.25: # bajando de d
        x_pos_F, y_pos_F = 7.1, 1 - (progress_F/0.25)*2.05
    elif progress_F < 0.5: # va a la izquierda
        x_pos_F, y_pos_F = 7.1 - ((progress_F-0.25)/0.25)*2.65, -1.05
    elif progress_F < 0.75: # sale de g y va izquierda
        x_pos_F, y_pos_F = 4.45 - ((progress_F-0.5)/0.25)*2.45, -1.05
    else: # sube al sumador
        x_pos_F, y_pos_F = 2.0, -1.05 + ((progress_F-0.75)/0.25)*1.65
    
    dot_F.set_position((x_pos_F, y_pos_F))
    dot_F.set_text(f"{read_hist[n] * G:.2f}")

    # 3. Animación del punto Wet (sale del buffer)
    # Sale de la caja derecha y va al sumador derecho
    progress_W = (frame % 4) / 4.0
    x_pos_W = 7.1 + progress_W * 0.9
    dot_W.set_position((x_pos_W, 1))
    dot_W.set_text(f"{read_hist[n]:.2f}")

    return boxes + vals + [dot_X, dot_F, dot_W]

ani = FuncAnimation(fig, update, frames=N_TOTAL, interval=INTERVAL, blit=True, repeat=True)
plt.tight_layout()
plt.show()


