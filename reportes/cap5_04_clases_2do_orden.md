### Sistemas de segundo orden

La ecuación caracteristica de un sistema de segundo orden se escribe como:

```{=latex}
\begin{equation}
\begin{aligned}
s^2 + 2\zeta \omega_n s + \omega_n^2 = 0
\end{aligned}
\end{equation}
```

Sus polos son:
\
```{=latex}
\begin{equation}
\begin{aligned}
s = -\zeta \omega_n \pm j\,\omega_n \sqrt{1 - \zeta^2}
\end{aligned}
\end{equation}
```
\

* La ecuación característica define los polos

* Los polos definen el comportamiento del sistema

\newpage

**Ejemplo:** Sea el siguiente sistema en lazo abierto, diseñar un control por retroalimentación
estatica de la salida. 

```{=latex}
\begin{equation}
\begin{aligned}
G(s) = \frac{1}{s^2 + 4s + 1}
\end{aligned}
\end{equation}
```


```julia
using ControlSystems
using Plots

s=tf("s")
G = tf([1], [1, 4, 1])
println(pole(G))
p = rlocusplot(G)
savefig(p, "root_locus2do_orden.png")

# Construye el sistema en lazo cerrado con realimentación unitaria.
# para diferentes k (3 y 5) :
println(pole(feedback(3*G, 1)))
println(pole(feedback(5*G, 1)))
y, t = step(feedback(5*G,1))
plot(t, vec(y))
savefig("step5.png")
```


\begin{figure}[H]
\centering
\includegraphics[height=0.35\textheight]{./img/root_locus2do_orden.png}
\caption{Root locus: en s= -2 los polos se fusionan}
\end{figure}

\newpage


La siguiente figura muestra la respuesta al escalón, corresponde a esta sección:

```c
println(pole(feedback(5*G, 1)))
y, t = step(feedback(5*G,1))
plot(t, vec(y))
savefig("step5.png")
```

\begin{figure}[H]
\centering
\includegraphics[height=0.3\textheight]{./img/step5.png}
\caption{Respuesta al escalón, con k = 5}
\end{figure}

\newpage

