import numpy as np


def tf2ss(num, den):
    """
    Convierte una función de transferencia en espacio de estados
    mediante la forma canónica controlable.
    """
    # Convertir las listas a arreglos NumPy
    num = np.asarray(num, dtype=float)
    den = np.asarray(den, dtype=float)

    # Validaciones básicas
    if den.ndim != 1 or num.ndim != 1:
        raise ValueError("num y den deben ser listas unidimensionales.")

    if len(den) < 2:
        raise ValueError("El denominador debe tener grado mayor o igual a 1.")

    if den[0] == 0:
        raise ValueError("El coeficiente principal de den no puede ser cero.")

    if len(num) == 0 or np.all(num == 0):
        raise ValueError("El numerador debe contener coeficientes no nulos.")

    n = len(den) - 1

    if len(num) > len(den):
        raise ValueError("La función de transferencia debe ser propia.")

    # Normalizar para que el denominador sea mónico
    num = num / den[0]
    den = den / den[0]

    # Completar el numerador con ceros a la izquierda
    num = np.pad(num, (len(den) - len(num), 0))

    a = den[1:]
    D = np.array([[num[0]]])

    # Matriz A: forma canónica controlable
    A = np.zeros((n, n))
    if n > 1:
        A[:-1, 1:] = np.eye(n - 1)
    A[-1, :] = -a[::-1]

    # Matriz B
    B = np.zeros((n, 1))
    B[-1, 0] = 1

    # Matriz C
    c = num[1:] - D[0, 0] * den[1:]
    C = c[::-1].reshape(1, n)

    return A, B, C, D


# --------------------------------------------------
# GENERADORES DE ARCHIVOS .ODE PARA XPPAUT
# --------------------------------------------------

def generar_ode_xppaut(A, B, C, D, tau=None, nombre_archivo="celula.ode"):
    """
    Genera un archivo .ode para XPPAUT a partir de las matrices.
    Si tau es None, la entrada es un escalón unitario.
    Si tau tiene un valor, la entrada es un escalón retardado.
    """
    n = A.shape[0]
    texto = f"# Archivo generado automaticamente por mytf2ss\n"
    
    if tau is not None:
        texto += f"# Sistema con retardo en la entrada (tau = {tau})\n"
        texto += f"tau = {tau}\n\n"
    else:
        texto += f"# Sistema sin retardo (escalon unitario)\n\n"
        
    # Condiciones iniciales de los estados del sistema
    for i in range(n):
        texto += f"x{i+1}(0) = 0\n"
    
    # Si hay retardo, definimos una variable u para la entrada
    if tau is not None:
        texto += f"u(0) = 1\n"
        
    texto += "\n"
    
    # Ecuaciones diferenciales x' = Ax + Bu
    for i in range(n):
        ecuacion = f"x{i+1}' = "
        terminos_A = []
        for j in range(n):
            if A[i, j] != 0:
                terminos_A.append(f"({A[i, j]})*x{j+1}")
        
        if not terminos_A:
            ecuacion += "0"
        else:
            ecuacion += " + ".join(terminos_A)
            
        # Término de entrada (con o sin retardo)
        if B[i, 0] != 0:
            if tau is not None:
                # Usamos la variable 'u' para el retardo
                ecuacion += f" + ({B[i, 0]}) * delay(u, tau)"
            else:
                ecuacion += f" + ({B[i, 0]})"
                
        texto += ecuacion + "\n"
    
    texto += "\n"
    
    # Salida y = Cx + Du
    ecuacion_y = "y = "
    terminos_C = []
    for j in range(n):
        if C[0, j] != 0:
            terminos_C.append(f"({C[0, j]})*x{j+1}")
            
    if not terminos_C:
        ecuacion_y += "0"
    else:
        ecuacion_y += " + ".join(terminos_C)
        
    if D[0, 0] != 0:
        if tau is not None:
            ecuacion_y += f" + ({D[0, 0]}) * delay(u, tau)"
        else:
            ecuacion_y += f" + ({D[0, 0]})"
            
    texto += ecuacion_y + "\n"
    
    # EL TRUCO MÁGICO PARA XPPAUT:
    # Decimos que u es constante (u'=0), pero su condición inicial es 1.
    # Al declarar u(0)=0 en la historia (t<0), el buffer de XPPAUT guarda 0.
    # Y en t=0 salta a 1. XPPAUT automáticamente asume u(t)=0 para t<0 
    # si la variable tiene derivada 0 y condición inicial 1, pero necesitamos forzar la historia.
    # Para forzar la historia en XPPAUT se usa la sintaxis: u(t) = 0 (esto se pone en la sección de historia).
    # Pero es más fácil: u es una variable auxiliar que no cambia, u' = 0.
    # En XPPAUT, si una variable tiene u(0) = 1, y su derivada es 0, el pasado se asume como 1.
    # Para forzar el pasado a 0, podemos definir una función de tiempo.
    # La forma más limpia y garantizada en XPPAUT es usar la función heaviside con retardo:
    # En lugar de delay(u, tau), podemos usar delay(heav(t-tau), 0). 
    # PERO delay exige variable.
    
    # LA SOLUCIÓN REAL Y DEFINITIVA: 
    # En XPPAUT, puedes definir una variable que sea la entrada escalón:
    # u = heav(t) -> Esto no funciona en el .ode porque heav(t) no es variable.
    # Sin embargo, XPPAUT permite: u' = 0, u(0)=1, y luego usamos u en delay.
    # El problema es que XPPAUT asume que u fue 1 siempre. 
    # Para que asuma que u fue 0 antes de t=0, debes poner en el .ode:
    # u(t) = 0 (esto no es válido en .ode, es para la ventana de historia).
    
    # Vamos a hacer un truco: definimos la entrada como u' = 0, u(0) = 1.
    # Y en el archivo .ode, antes de las ecuaciones, definimos una sección de historia:
    # No se puede en .ode.
    
    # SOLUCIÓN DEFINITIVA: 
    # Usar un integrador para la entrada:
    # u' = 0
    # u(0) = 1
    # Pero para que el pasado sea 0, XPPAUT requiere que uses la ventana de historia.
    # Sin embargo, podemos usar la función "heav" dentro de delay si la variable es el tiempo.
    # delay(t, tau) -> retrasa el tiempo. 
    # Entonces: (1.0) * heav(t - tau) 
    # Esto es: la función escalón unitario, pero evaluada en t-tau.
    # ¡ESO ES EXACTAMENTE LO QUE QUEREMOS!
    # No necesitamos delay() en absoluto. Podemos usar la función heav() directamente.
    # heav(t - tau) es 0 para t < tau, y 1 para t >= tau.
    # ¡Es perfecto!
    
    # Vamos a cambiar el término de entrada a: (B) * heav(t - tau)
    
    # Rehacemos la generación usando heav(t - tau) en lugar de delay.
    # Para eso, modificamos el código anterior.
    
    # (Volvemos a generar el texto pero con heav)
    
    # Para el caso sin retardo: (B) * heav(t)
    # Para el caso con retardo: (B) * heav(t - tau)
    
    # Esto es mucho más limpio, no necesita buffer, y XPPAUT lo entiende perfectamente.
    
    # Re-generamos el texto desde cero con esta nueva lógica:
    
    texto = f"# Archivo generado automaticamente por mytf2ss\n"
    
    if tau is not None:
        texto += f"# Sistema con retardo en la entrada (tau = {tau})\n"
        texto += f"tau = {tau}\n\n"
    else:
        texto += f"# Sistema sin retardo (escalon unitario)\n\n"
        
    for i in range(n):
        texto += f"x{i+1}(0) = 0\n"
    texto += "\n"
    
    for i in range(n):
        ecuacion = f"x{i+1}' = "
        terminos_A = []
        for j in range(n):
            if A[i, j] != 0:
                terminos_A.append(f"({A[i, j]})*x{j+1}")
        
        if not terminos_A:
            ecuacion += "0"
        else:
            ecuacion += " + ".join(terminos_A)
            
        if B[i, 0] != 0:
            if tau is not None:
                # Usamos heav(t - tau) para el retardo exacto
                ecuacion += f" + ({B[i, 0]}) * heav(t - tau)"
            else:
                ecuacion += f" + ({B[i, 0]}) * heav(t)"
                
        texto += ecuacion + "\n"
    
    texto += "\n"
    
    ecuacion_y = "y = "
    terminos_C = []
    for j in range(n):
        if C[0, j] != 0:
            terminos_C.append(f"({C[0, j]})*x{j+1}")
            
    if not terminos_C:
        ecuacion_y += "0"
    else:
        ecuacion_y += " + ".join(terminos_C)
        
    if D[0, 0] != 0:
        if tau is not None:
            ecuacion_y += f" + ({D[0, 0]}) * heav(t - tau)"
        else:
            ecuacion_y += f" + ({D[0, 0]}) * heav(t)"
            
    texto += ecuacion_y + "\n"
    texto += "\ndone\n"
    
    try:
        with open(nombre_archivo, "w") as f:
            f.write(texto)
        print(f"\n[OK] Archivo generado: '{nombre_archivo}'")
    except IOError as e:
        print(f"\n[Error] No se pudo guardar el archivo: {e}")


# --------------------------------------------------
# INTERFAZ DE CONSOLA
# --------------------------------------------------

def leer_coeficientes(mensaje):
    while True:
        texto = input(mensaje)
        partes = texto.replace(",", " ").split()
        if not partes:
            print("Error: debes escribir al menos un coeficiente.")
            continue
        try:
            return [float(p) for p in partes]
        except ValueError:
            print("Error: solo se admiten números separados por espacios o comas.")

def mostrar_matrices(A, B, C, D):
    for nombre, matriz in (("A", A), ("B", B), ("C", C), ("D", D)):
        print(f"\n{nombre} =")
        print(matriz)

def main():
    print("=== Función de transferencia a espacio de estados ===")
    print("Escribe los coeficientes en orden descendente,")
    print("separados por espacios o comas.\n")

    while True:
        num = leer_coeficientes("Numerador: ")
        den = leer_coeficientes("Denominador: ")

        try:
            A, B, C, D = tf2ss(num, den)
        except ValueError as e:
            print(f"Error: {e}\n")
            continue

        mostrar_matrices(A, B, C, D)

        # --- GENERACIÓN DE ARCHIVOS .ODE ---
        print("\n--- Generación de Simulador (XPPAUT) ---")
        
        # 1. Generar sin retardo
        nombre_base = "celula_base.ode"
        generar_ode_xppaut(A, B, C, D, tau=None, nombre_archivo=nombre_base)
        
        # 2. Preguntar por el retardo
        usar_tau = input("\n¿Deseas generar tambien la version con retardo? (s/n): ").strip().lower()
        if usar_tau == "s":
            while True:
                try:
                    val_tau = float(input("Introduce el valor del retardo (ej. 0.5): "))
                    if val_tau < 0:
                        print("El retardo debe ser mayor o igual a cero.")
                        continue
                    break
                except ValueError:
                    print("Por favor, introduce un número válido.")
            
            nombre_retardo = "celula_retardo.ode"
            generar_ode_xppaut(A, B, C, D, tau=val_tau, nombre_archivo=nombre_retardo)
        # ---------------------------------------------------

        otra = input("\n¿Calcular otra función? (s/n): ").strip().lower()
        if otra != "s":
            break


if __name__ == "__main__":
    try:
        main()
    except (KeyboardInterrupt, EOFError):
        print("\nSaliendo.")