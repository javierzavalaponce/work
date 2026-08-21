```{=latex}
\clearpage
```

# Ejercicios

## Ejercicio 1: Normas y Convergencia de Funciones

**Objetivo:**
Implementar funciones para calcular las normas $L_1$, $L_2$ y $L_\infty$
de una función en un intervalo, y luego usarlas para analizar la convergencia de una sucesión de funciones.

**Descripción:**
Considere la sucesión de funciones 
$f_n(x)= x^n$ en el intervalo $[0,1]$. Sabemos que esta sucesión converge puntualmente a la función 
$f(x)=0$ para $x \in [0,1)$ y a $f(1)=1$. Sin embargo, la convergencia de la sucesión depende de la norma utilizada para medir la distancia entre las funciones.


**Paso 1:** Implementación de normas. Escribe funciones en Python que calculen de forma aproximada:

```python
norma_1(f, a, b, N): 
```

Calcula $\|f\|_1 = \int_a^b |f(x)|\,dx$ usando integración numérica (por ejemplo, la regla del trapecio con N puntos).

```python
norma_2(f, a, b, N): 
```

Calcula $\|f\|_2 = \sqrt{ \int_a^b |f(x)|^2\,dx}$

```python
norma_inf(f, a, b, N): 
```

Aproxima: $\|f\|_\infty = \sup_{x \in [a,b]} |f(x)|$  mediante el máximo de los valores obtenidos al muestrear la función en N puntos.

 **Paso 2:** Análisis de convergencia.

* Define la función $f_n(x)=x^n$  y la función límite $f(x)=0$

* Para $n=1,2,4,8,16,32,64$, calcula las distancias 
$\|f_n-f\|_1$,
$\|f_n-f\|_2$,
$\|f_n-f\|_\infty$. Grafica cómo estas distancias decrecen (o no) a medida que $n$ aumenta.

**Preguntas:**

* ¿La sucesión converge a $f$ en la norma $L_1$?, ¿Y en $L_2$?, ¿Y en $L_\infty$?
* ¿Qué nos dice este experimento sobre la dependencia de la convergencia con respecto a la norma elegida?

