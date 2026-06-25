```{=latex}
\clearpage
```
# Paquete fuzzy-logic-toolkit (octave)

Este paquete puede generar funciones de membresia,

```bash
octave>pkg install -forge fuzzy-logic-toolkit
```

### ejemplo.m

En *ejemplo.m*:

```bash
pkg load fuzzy-logic-toolkit

# Definir el dominio (valores de x)
x = 0:0.1:10;

# Crear funciones de membresía
# Triangular: pico en 5, base en 3 y 7
y_tri = trimf(x, [3 5 7]);

# Trapezoidal: meseta entre 4 y 6, base en 2 y 8
y_trap = trapmf(x, [2 4 6 8]);

# Gaussiana: centro en 5, sigma = 1
y_gauss = gaussmf(x, [1 5]);

# Sigmoide: pendiente 2, punto de inflexión en 5
y_sig = sigmf(x, [2 5]);

# Graficar los resultados
plot(x, y_tri, x, y_trap, x, y_gauss, x, y_sig)
legend('Triangular', 'Trapezoidal', 'Gaussiana', 'Sigmoide')

```

```{=latex}
\clearpage
```
### Gráficas

\begin{figure}[H]
\centering
\includegraphics[width=1.0\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/funciones_membresia.png}
\caption{Funciones de membresía}
\label{fig:funcs_membresia}
\end{figure}


