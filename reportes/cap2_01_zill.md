# Libro: Ecuaciones diferenciales  (Zill)

## Capitulo 1. Resumen

1. **Definición de ecuación diferencial**  

   Es una ecuación que involucra derivadas de una o más variables dependientes respecto a una o más variables independientes.[@zill]

2. **Tipos de ecuaciones diferenciales**  

   - **EDO (ordinarias):** derivadas respecto a una sola variable.  

   - **EDP (parciales):** derivadas respecto a múltiples variables.

   - **Clasificación por orden**  El orden de una ED es el de la derivada de mayor grado presente. 

3. **Forma general y forma normal**  
   - Forma general:  

   ```{=latex}
   \begin{equation}
   \begin{aligned}
   F(x, y, y', \ldots, y^{(n)}) = 0
   \end{aligned}
   \end{equation}
   ```


   - Forma normal: despejada respecto a la derivada de mayor orden.

4. **Linealidad**  

   Una ED es lineal si:

\
```{=latex}
\begin{equation}
\begin{aligned}
a_n(x)\frac{d^n y}{dx^n} + a_{n-1}(x)\frac{d^{n-1} y}{dx^{n-1}} + \cdots + a_1(x)\frac{dy}{dx} + a_0(x)y = g(x)
\end{aligned}
\end{equation}
```
\

   - La función desconocida y sus derivadas aparecen en primer grado.
   - Los coeficientes dependen solo de la variable independiente.  

   En caso contrario, es **no lineal**.




5. **Solución de una ecuación diferenciales**  

   Una función es solución si al sustituirse en la ecuación la convierte en una identidad en un intervalo dado.

6. **Intervalo de definición (o existencia)**  
   Toda solución está asociada a un intervalo donde es válida y derivable.

7. **Soluciones explícitas e implícitas**  
   - Explícita: 
```{=latex}
\begin{equation}
\begin{aligned}
  y = f(x)
\end{aligned}
\end{equation}
```

   - Implícita: 
   

```{=latex}
\begin{equation}
\begin{aligned}
  G(x, y) = 0
\end{aligned}
\end{equation}
```

   En otras palabras: no siempre es posible despejar explícitamente.

8. **Familias de soluciones y parámetros**  
   - Ec. diferecnial de orden n → familia con n constantes arbitrarias.  
   - Representan infinitas soluciones.  
   - Una solución sin parámetros es una **solución particular**.

9. **Conceptos adicionales importantes**  

   - Sistemas de ecs. diferenciales: múltiples ecuaciones con varias funciones desconocidas

\newpage

\newpage
