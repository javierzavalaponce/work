# Plan de Estudio --- Control Moderno Base

## Enfoque: Espacio de Estados + SciPy + Intuición Matemática

------------------------------------------------------------------------

# Visión General del Trayecto

Álgebra Lineal → Ecuaciones Diferenciales → Transformada de Laplace →
Funciones de Transferencia → Espacio de Estados → Diseño por
Realimentación

Duración sugerida: 6 semanas (ajustable)

------------------------------------------------------------------------

# ETAPA 0 --- Álgebra Lineal Aplicada (Semana 1)

## Objetivos

-   Comprender matrices como transformaciones
-   Entender autovalores y estabilidad
-   Dominar operaciones matriciales con NumPy

## Temas

-   Producto matricial
-   Autovalores y autovectores
-   Diagonalización
-   Exponencial matricial

## Ejercicio obligatorio

1.  Definir una matriz A 2x2
2.  Calcular autovalores
3.  Simular evolución usando expm(A\*t)

------------------------------------------------------------------------

# ETAPA 1 --- Ecuaciones Diferenciales (Semana 2)

## Objetivos

-   Resolver EDOs numéricamente
-   Entender dinámica temporal

## Herramienta

scipy.integrate.solve_ivp

## Ejercicio obligatorio

Simular: dx/dt = -2x Graficar respuesta para diferentes condiciones
iniciales.

------------------------------------------------------------------------

# ETAPA 2 --- Transformada de Laplace (Semana 3)

## Objetivos

-   Comprender que Laplace convierte derivadas en álgebra
-   Relacionar polos con dinámica

## Ejercicio obligatorio

1.  Transformar: dx/dt + 2x = u
2.  Obtener G(s)
3.  Identificar el polo

------------------------------------------------------------------------

# ETAPA 3 --- Función de Transferencia (Semana 4)

## Herramienta

scipy.signal.TransferFunction

## Objetivos

-   Simular respuesta al escalón
-   Interpretar polos y ceros

## Ejercicio obligatorio

Simular un sistema de segundo orden y variar amortiguamiento.

------------------------------------------------------------------------

# ETAPA 4 --- Espacio de Estados (Semana 5)

## Objetivos

-   Convertir EDOs a forma matricial
-   Simular usando StateSpace

## Ejercicio obligatorio

1.  Definir sistema 2x2
2.  Simular respuesta
3.  Comparar con función de transferencia equivalente

------------------------------------------------------------------------

# ETAPA 5 --- Exponencial Matricial y Estabilidad (Semana 6)

## Objetivos

-   Comprender x(t) = e\^(At)x(0)
-   Relacionar autovalores con estabilidad

## Ejercicio obligatorio

1.  Calcular e\^(At)
2.  Analizar estabilidad según parte real de autovalores

------------------------------------------------------------------------

# ETAPA 6 --- Realimentación de Estados

## Objetivos

-   Diseñar u = -Kx
-   Mover polos

## Ejercicio obligatorio

1.  Definir K
2.  Calcular A_cl = A - BK
3.  Verificar estabilidad

------------------------------------------------------------------------

# Resultado Esperado

Al finalizar podrás:

-   Interpretar estabilidad desde autovalores
-   Pasar de EDO a espacio de estados
-   Comprender función de transferencia
-   Diseñar control básico por realimentación

------------------------------------------------------------------------

# Recomendación de práctica

-   Simular todo en Python
-   Graficar siempre
-   Modificar parámetros y observar cambios
-   Repetir experimentos hasta desarrollar intuición
