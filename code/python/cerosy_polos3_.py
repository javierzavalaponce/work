import numpy as np
import matplotlib.pyplot as plt
from scipy import signal


FONT_TITLE = 22
FONT_LABEL = 20
FONT_TICKS = 18

# ============================================================
# CONFIGURACION GENERAL
# ============================================================

plt.style.use("seaborn-v0_8-whitegrid")

t = np.linspace(0, 10, 2000)

# ============================================================
# FUNCION AUXILIAR
# ============================================================

def plot_case(filename, title, num, den, poles, color_response, color_poles):
    """
    Genera una figura 2x1:
        izquierda  -> polos en plano complejo
        derecha    -> respuesta temporal al escalón
    """

    system = signal.TransferFunction(num, den)
    tout, y = signal.step(system, T=t)

    fig, axes = plt.subplots(1, 2, figsize=(12, 4))

    # --------------------------------------------------------
    # GRAFICA DE POLOS
    # --------------------------------------------------------

    ax = axes[0]

    ax.axhline(0, color="black", linewidth=1)
    ax.axvline(0, color="black", linewidth=1)

    for p in poles:
        ax.plot(np.real(p), np.imag(p),
                marker='x',
                markersize=12,
                markeredgewidth=3,
                color=color_poles)

    ax.set_title("Plano de polos",fontsize=FONT_TITLE)
    ax.set_xlabel("Parte real",fontsize=FONT_TITLE-2)
    ax.set_ylabel("Parte imaginaria",fontsize=FONT_TITLE-2)

    ax.grid(True)
    
    # limites dinamicos
    real_parts = [np.real(p) for p in poles]
    imag_parts = [np.imag(p) for p in poles]
    
    xmin = min(real_parts) - 1
    xmax = max(real_parts) + 1
    
    ymax = max(1, max(np.abs(imag_parts)) + 1)
    
    ax.set_xlim(xmin, xmax)
    ax.set_ylim(-ymax, ymax)
    
    # --------------------------------------------------------
    # RESPUESTA TEMPORAL
    # --------------------------------------------------------

    ax2 = axes[1]

    ax2.plot(tout, y,
             linewidth=3,
             color=color_response)

    ax2.set_title("Respuesta temporal al escalón",fontsize=FONT_TITLE)
    ax2.set_xlabel("Tiempo",fontsize=FONT_TITLE-2)
    ax2.set_ylabel("Salida",fontsize=FONT_TITLE-2)

    ax2.grid(True)

    # --------------------------------------------------------
    # TITULO GENERAL
    # --------------------------------------------------------

    fig.suptitle(title, fontsize=16)

    plt.tight_layout()

    # guardar png
    #plt.savefig(filename, dpi=300, bbox_inches="tight")
    plt.savefig(filename, dpi=300, bbox_inches='tight',pad_inches=0.1)

    plt.close()


# ============================================================
# 1. SUBAMORTIGUADO
# ============================================================

zeta = 0.25
wn = 3

num = [wn**2]
den = [1, 2*zeta*wn, wn**2]

poles = np.roots(den)

plot_case(
    filename="01_subamortiguado.png",
    title=" ",
    num=num,
    den=den,
    poles=poles,
    color_response="royalblue",
    color_poles="darkblue"
)

# ============================================================
# 2. CRITICAMENTE AMORTIGUADO
# ============================================================

zeta = 1.0
wn = 3

num = [wn**2]
den = [1, 2*zeta*wn, wn**2]

poles = np.roots(den)

plot_case(
    filename="02_criticamente_amortiguado.png",
    title=" ",
    num=num,
    den=den,
    poles=poles,
    color_response="forestgreen",
    color_poles="darkgreen"
)

# ============================================================
# 3. SOBREAMORTIGUADO
# ============================================================

zeta = 2.0
wn = 3

num = [wn**2]
den = [1, 2*zeta*wn, wn**2]

poles = np.roots(den)

plot_case(
    filename="03_sobreamortiguado.png",
    title=" ",
    num=num,
    den=den,
    poles=poles,
    color_response="darkorange",
    color_poles="saddlebrown"
)

# ============================================================
# 4. INESTABLE
# ============================================================

# polo positivo
num = [1]
den = [1, -1]

poles = np.roots(den)

plot_case(
    filename="04_inestable.png",
    title=" ",
    num=num,
    den=den,
    poles=poles,
    color_response="crimson",
    color_poles="darkred"
)

print("Listo.")
print("Se generaron:")
print("  01_subamortiguado.png")
print("  02_criticamente_amortiguado.png")
print("  03_sobreamortiguado.png")
print("  04_inestable.png")



