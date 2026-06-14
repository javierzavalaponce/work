```{=latex}
\clearpage
```

#  Simulación de sistemas de primer orden


Tomemos por ejemplo el siguiente sistema:

```{=latex}
\begin{equation}
\begin{aligned}
\dot{x} = u(t)
\end{aligned}
\label{eq:integrador_puro}
\end{equation}
```

se puede leer como:

* La derivada temporal de $x$ es igual a la entrada $u$
* El *sistema*  integra la entrada.

es decir, la integral de la entrada $u$ es la salida $x$,

```{=latex}
\[
x(t) = x(0) + \int_0^t u(\tau)\, d\tau
\]
```
o bien, en bloques:

\begin{figure}[H]
\centering
\includegraphics[width=0.79\textwidth,trim=0cm 9cm 0cm 5cm,clip]{../img/ejercicio001.pdf}
\caption{Integrador ($1/s$)}
\label{fig:integrador_basico}
\end{figure}


Si tomamos el caso en que la entrada $u(t)=1$ y la salida es $x(t)$ como se muestra en la Figura  \ref{fig:integrador_basico}, el sistema queda definido por la ecuación \ref{eq:integrador_puro}, tenemos  que la integral de una constante resulta en una rampa. Al graficar el tiempo $t$ sobre el eje de las abscisas y la variable $x$ sobre el eje de las ordenadas, (Considerando condiciones nulas $x(0)=0$) se obtiene:

\begin{figure}[H]
\centering
\includegraphics[height=0.3\textheight]{../img/x_dot_equal_u.png}
\caption{Integrando una constante $1$ se obtiene una rampa}
\end{figure}


\vspace{1cm}

La figura precedente se obtiene se puede obtener con el siguiente script. Se explica a detalle después.

\vspace{1cm}

```julia
using OrdinaryDiffEq
using Plots

function f!(dx, x, p, t)
dx[1] = 1
end

# Condición inicial: x(0) = 0.0
x0 = [0.0]
tspan = (0.0, 6.0)

prob = ODEProblem(f!, x0, tspan)
sol = solve(prob)

plot(sol, label=" ", xlabel="t", ylabel="x", title="(dt/dt) =  1")
savefig("x_dot_equal_u.png")
```

\newpage

## Explicacion detallada del script

Las primeras dos líneas son dependencias:

```julia
using OrdinaryDiffEq
using Plots
```

Condición inicial: $x(0) = 0.0$. Aunque el sistema posee una sola variable de estado, $OrdinaryDiffEq$ representa los estados mediante vectores. Por ello, la condición inicial se escribe como $[0.0]$ y no simplemente como $0.0$.

```julia
x0 = [0.0]
```

Intervalo temporal de integración indicando que la simulación debe realizarse desde $t=0$ hasta $t=6$ segundos.

```julia
tspan = (0.0, 6.0)
```

Las siguientes dos líneas, generan un archivo con la gráfica resultante:

```julia
plot(sol, label=" ", xlabel="t", ylabel="x", title="(dt/dt) =  1")
savefig("x_dot_equal_u.png")
```

\vspace{1cm}

**Definición de la ecuación diferencial.** La ecuación que deseamos resolver es $\dot{x}=1$. 
En la biblioteca $OrdinaryDiffEq$,
las ecuaciones diferenciales se describen mediante una función. 
En este ejemplo:

```julia
function f!(dx, x, p, t)
    dx[1] = 1
end
```

$f!(dx, x, p, t)$ representa la ecuación $\dot{x}=f(x,p,t)$. La función recibe cuatro argumentos:

* $dx$: vector donde se almacenan las derivadas de las variables de estado. Para este ejemplo, donde solo existe una variable de estado: $dx[1]=\dot{x_1}$
* $x$: vector de estados actuales del sistema.
* $p$: parámetros adicionales (no utilizados en este ejemplo).
* $t$: tiempo actual de simulación.

El signo **$!$** al final del nombre $f!$ es una convención de $Julia$ que indica que la función modifica alguno de sus argumentos. En este caso, la función modifica el vector $dx$ almacenando en él la derivada del estado.

Los vectores $dx$ y $x$ son de tamaño 1 para este ejemplo. Matemáticamente: 


```{=latex}
\[
\begin{aligned}
x &= [x_1] \\
\dot{x} &=[\dot{x_1}]
\end{aligned}
\]
```


**Construcción y resolución del problema**. Una vez definida la ecuación diferencial, se crea un objeto que contiene toda la información necesaria para la simulación. Dicho objeto contiene:

* La ecuación diferencial $(f!)$
* La condición inicial $x0$
* El intervalo de tiempo $tspan$

```julia
prob = ODEProblem(f!, x0, tspan)
```

Conceptualmente equivale a declarar:

```{=latex}
\[
\dot{x}=1
\qquad
x(0)=0
\qquad
0 \le t \le 6
\]
```

La razón por la que $OrdinaryDiffEq$ usa vectores incluso para un sistema de primer orden es que así puede manejar de manera uniforme sistemas de cualquier dimensión. 
