#!/usr/bin/env python3
"""
plot_adc.py

Lee un CSV de 3 columnas y grafica adc1, adc2, adc3 en los mismos ejes.
Uso:
    python plot_adc.py datos.csv
"""

import sys
import pandas as pd
import matplotlib.pyplot as plt


def main():

    if len(sys.argv) != 2:
        print("Uso: python plot_adc.py archivo.csv")
        sys.exit(1)

    csv_file = sys.argv[1]

    # Leer CSV sin headers
    df = pd.read_csv(csv_file, header=None)

    # Asignar nombres profesionales
    df.columns = ["adc1", "adc2", "adc3"]
    print(df["adc1"])

    # Estilo elegante
    plt.style.use("seaborn-v0_8-darkgrid")

    fig, ax = plt.subplots(figsize=(12, 6))

    ax.plot(df.index, df["adc1"],
            label="adc1",
            linewidth=2.0)

    ax.plot(df.index, df["adc2"],
            label="adc2",
            linewidth=2.0)

    ax.plot(df.index, df["adc3"],
            label="adc3",
            linewidth=2.0)

    # Etiquetas profesionales
    ax.set_title("ADC Samples from uController", fontsize=16, fontweight="bold")
    ax.set_xlabel("Sample", fontsize=12)
    ax.set_ylabel("ADC Value", fontsize=12)

    ax.legend(fontsize=11)
    ax.grid(True, alpha=0.3)

    plt.tight_layout()

    plt.show()


if __name__ == "__main__":
    main()

