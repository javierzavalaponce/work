# Simulación de Sistemas Dinámicos Usando *julia* 


## El integrador puro

La ecuación:


```{=latex}
\begin{equation}
\begin{aligned}
\dot{x} = u(t)
\end{aligned}
\end{equation}
```
se puede leer como:

* La derivada temporal de $x$ es igual a la entrada $u$
* El *sistema*	 integra la entrada.

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


El integrador puro simplemente acumula (responde a la entrada integrándola). No *sigue referencias* por sí mismo porque no tiene ningún mecanismo de comparación ni corrección. 

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

\vspace{1cm}




\newpage


## $\dot{x} = x u(t)$

En esta ecuación:

* La rapidez de cambio de $x$ depende del valor actual de $x$
* La entrada $u(t)$ actúa modulando el crecimiento o decrecimiento del estado

A diferencia del integrador puro $\dot{x} = u(t)$, donde la entrada se acumula, 
aquí el propio estado participa en su evolución. El sistema ya no es lineal respecto al estado, 
porque $x$ se multiplica por la entrada



\newpage




\newpage