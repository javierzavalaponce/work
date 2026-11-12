import sys
import numpy as np
import matplotlib.pyplot as plt

def main():
    if len(sys.argv) != 2:
        print("Uso: python graficar.py <archivo.dat>")
        sys.exit(1)

    archivo = sys.argv[1]

    try:
        # Cargar los datos (asume columnas separadas por espacios)
        datos = np.loadtxt(archivo)
    except Exception as e:
        print(f"Error al leer el archivo: {e}")
        sys.exit(1)

    # Extraer las columnas (0 es tiempo, 1 es la variable x)
    t = datos[:, 0]
    x = datos[:, 1]

    # Crear la figura con un tamaño agradable
    plt.figure(figsize=(8, 6))
    
    # Graficar con el color púrpura y grosor similar al de tu imagen
    plt.plot(t, x, color='darkorchid', linewidth=1.5, label='x(t)')
    
    # Configurar títulos y etiquetas
    plt.title('Sistema con retardo', pad=15)
    plt.xlabel('Tiempo', labelpad=10)
    plt.ylabel('x(t)', labelpad=10)
    
    # Ajustar los límites del eje X e Y para que coincidan con tu captura
    plt.xlim(0, max(t))
    plt.ylim(0, 1.05)
    
    # Agregar la leyenda arriba a la derecha
    plt.legend(loc='upper right', frameon=False)
    
    # Ajustar el diseño para que no se corte nada
    plt.tight_layout()
    
    # Guardar la imagen
    nombre_salida = archivo.replace('.dat', '.png')
    plt.savefig(nombre_salida, dpi=150)
    print(f"Imagen generada exitosamente: {nombre_salida}")
    
    # Mostrar la imagen en pantalla (opcional)
    # plt.show()

if __name__ == "__main__":
    main()


