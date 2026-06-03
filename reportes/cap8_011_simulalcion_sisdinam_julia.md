```{=latex}
\clearpage
```

## El integrador puro

La ecuación:

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
* El *sistema*	integra la entrada.

Es decir, la integral de la entrada $u$ es la salida $x$,

\begin{equation}
\begin{aligned}
x(t) = x(0) + \int_0^t u(\tau)\, d\tau
\end{aligned}
\end{equation}

en bloques:

\begin{figure}[H]
\centering
\includegraphics[width=0.79\textwidth,trim=0cm 9cm 0cm 5cm,clip]{./img/ejercicio001.pdf}
\caption{Integrador ($1/s$)}
\label{fig:integrador_basico}
\end{figure}

## Retroalimentación estática aplicada a un integrador puro


El integrador puro de la ecuación \ref{eq:integrador_puro} simplemente acumula (responde a la entrada integrándola). No *sigue referencias* por sí mismo porque no tiene ningún mecanismo de comparación ni corrección. 

* Si la entrada $u(t)$ = 0, la salida no cambia, mantiene su valor $x(0)$
* Si $u(t) = k$ constante, la salida es una rampa $x=kt$ con pendiente $k$

Para lograr que este sistema siga una referencia $r$, se añade un control
por retroalimentacion estática

\begin{figure}[H]
\centering
\includegraphics[width=1.0\textwidth,trim=0cm 7cm 0cm 7cm,clip]{./img/control_del_integrador.pdf}
\caption{Sistema en lazo cerrado con entrada constante (referencia $r$)}
\label{fig:integrador_bloques}
\end{figure}


La retroalimentación negativa con $k=1$ significa $u = (r-x)$ o bien:


\begin{equation}
\begin{aligned}
\dot{x} = r-x
\end{aligned}
\label{eq:sistema_primerorden}
\end{equation}

\vspace{1cm}

### Solución númerica. Método de Euler (*Forward o Explícito*)

Euler desarrolló estas ideas durante el siglo XVIII. A partir de una ecuación diferencial como:

\begin{equation}
\begin{aligned}
\dot{x} = f(x,t)
\end{aligned}
\end{equation}

se aproxima la evolución usando pequeños pasos de tiempo:

\begin{equation}
\begin{aligned}
\frac{x_{k+1}-x_k}{\Delta t}   =  f(x,t)
\end{aligned}
\end{equation}



\vspace{2cm}


Retomando la ecuación \ref{eq:sistema_primerorden}, podemos generar una solución numérica. Ver el siguiente ejemplo
(en lenguaje *julia*).

\begin{equation}
\begin{aligned}
\frac{x_{k+1}-x_k}{dt}   =  (r -x_k)
\end{aligned}
\end{equation}


\newpage 


En *julia*, un controlador proporcional discreto aplicado al integrador con referencia $r=5$:


``` julia
using Plots
dt = 0.1
T  = 6.0
t = 0:dt:T

x = zeros(length(t))
r = 5.0    # referencia
x[1] = 0.0 # condiciones iniciales, en julia 
           # los indices empiezan en 1

# método de Euler:
for k in 1:length(t)-1
    dx = -x[k] + r
    x[k+1] = x[k] + dt*dx
end

p = plot(t,x, xlabel = "t", ylabel = "x(t)", label = " ")
savefig(p, "integrador_retroalimentado.png")
```

\vspace{1cm}


\begin{figure}[H]
\centering
\includegraphics[height=0.30\textheight]{./img/integrador_retroalimentado.png}
\caption{Integrador retroalimentado siguiendo referencia $r = 5$}
\end{figure}


\newpage

Alternativamente (*julia*):

``` julia
using OrdinaryDiffEq
using Plots

function f!(dx, x, p, t)
    r = 5.0
    dx[1] = r - x[1]
end

# Condición inicial: x(0) = 0.0
x0 = [0.0]
tspan = (0.0, 6.0)

prob = ODEProblem(f!, x0, tspan)
sol = solve(prob)

plot(sol, label=" ", xlabel="t", ylabel="x", 
     title="dx/dt = (r - x), r=5")
savefig("integrador_retroalimentado.png")
```

\newpage

### Analogía alternativa 

Imaginemos un tanque que recibe agua por una tubería de entrada con flujo $f_e$, mientras que por la parte inferior sale agua con flujo $f_s$


\begin{figure}[H]
\centering
\includegraphics[height=0.45\textheight,trim=0cm 9cm 0cm 9cm,clip]{./img/tanque_fe_fs.pdf}
\caption{Analogia de tanque con flujos de entrada y salida}
\label{fig:tnke}
\end{figure}

Podemos pensar al tanque como un “acumulador” de flujo:

* El flujo de entrada $f_e$ agrega agua,
* El flujo de salida $f_s$ remueve, si $f_s = 0$, se trata de un integrador puro (el tanque solo almacena)
* El volumen $x$ representa la cantidad almacenada.

La relación conceptual puede expresarse como:

\begin{equation}
\begin{aligned}
\dot{x} = f_e - f_s
\end{aligned}
\end{equation}

Esta expresión indica que el volumen dentro del tanque cambia según la diferencia entre el flujo que entra y el flujo que sale.

El objetivo de control más sencillo consiste en mantener una cantidad deseada de agua dentro del tanque. Para lograrlo, el flujo de entrada debe compensar continuamente el flujo de salida.

Cuando el sistema alcanza una condición donde: $f_e = f_s$, entonces el volumen deja de variar:
$\dot{x} = 0$

Si fijamos el flujo de entrada en un valor constante, por ejemplo $f_e = 5$ 
(digamos 5 litros / segundo),
el comportamiento del tanque dependerá completamente del flujo de salida $f_s$, sin embargo no hay una única expresión, es decir:

\begin{equation}
\begin{aligned}
f_s = f(x)
\end{aligned}
\end{equation}

Mientras más agua exista dentro del tanque: mayor altura de columna líquida,
mayor presión. **Distintos modelos posibles para $f(s)$:**

* Proporcional lineal $f_s = kx$ con $k=1$, $f_s = x$
* Ley de Torricelli $f_s=k\sqrt{x}$ 
* Salida constante  $f_s = c$

Tomando el modelo $f_s = x$ 

\begin{equation}
\begin{aligned}
\dot{x} = 5 - x
\end{aligned}
\end{equation}

Si $x$ es pequeño, domina la entrada, si $x$ es grande, domina la salida,
eventualmente ambos se equilibran. Ver campo direccional:

\begin{figure}[H]
\centering
\includegraphics[height=0.25\textheight]{./img/campo_tanque.png}
\caption{Campo direccional para $\dot{x} = 5 - x$}
\end{figure}

\newpage


