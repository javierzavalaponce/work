### Sistemas de primer orden, circuito RC

La siguiente ecuación es una ecuacion diferencial lineal ordinaria de primer orden:

\
```{=latex}
\begin{equation}
\begin{aligned}
U(t) = a_1\frac{dy}{dt} + a_0y
\end{aligned}
\end{equation}
```
\

También se puede escribir de la siguiente manera: 

\
```{=latex}
\begin{equation}
\begin{aligned}
U(t) = a_1\dot{y} + a_0y
\end{aligned}
\end{equation}
```
\

La siguiente figura muestra un circuito RC. 
Sea:

* $U(t)$: entrada (voltaje)

* $y(t)$: salida (voltaje en el capacitor)

\begin{figure}[H]
\centering
\includegraphics[height=0.25\textheight,trim=0cm 4cm 0cm 12cm,clip]{./img/rc01.pdf}
\caption{Cerrando interruptor en t= 0 , $i(t) = C \frac{dV_C(t)}{dt}  = C\dot{y}$}
\label{fig:rc01}
\end{figure}

* Un capacitor no "recuerda" cuánta corriente recibió hace un minuto. Solo "sabe" cuál es su voltaje *ahora* y cuánta corriente está entrando *ahora*.

* El voltaje en un capacitor es una variable *continua*.

* Cerrar el interruptor significa aplicar un *escalón* de magnitud fija.

```{=latex}
\begin{equation}
\begin{aligned}
i(t)=\frac{Cdv(t)}{dt} 
\end{aligned}
\end{equation}
```

Al cerrar el interruptor y por leyes de Kirchhoff:


```{=latex}
\begin{equation}
\begin{aligned}
U(t) = RC\,\dot{y}(t) + y(t)
\end{aligned}
\end{equation}
```

```{=latex}
\begin{equation}
\begin{aligned}
\dot{y} = \frac{1}{RC} (U(t)-y(t)) 
\end{aligned}
\end{equation}
```

Aplicamos transformada de Laplace (condiciones iniciales cero):

```{=latex}
\begin{equation}
\begin{aligned}
sY(s) = \frac{1}{RC} (U(s)-Y(s))
\end{aligned}
\end{equation}
```

```{=latex}
\begin{equation}
\begin{aligned}
RCsY(s)=U(s)−Y(s)
\end{aligned}
\end{equation}
```

Reordenando,

```{=latex}
\begin{equation}
\begin{aligned}
(RCs+1)Y(s) = U(s)
\end{aligned}
\end{equation}
```
Función de Transferencia

```{=latex}
\begin{equation}
\begin{aligned}
ft = \frac{Y(s)}{U(s)} = \frac{1}{(RCs+1)}
\end{aligned}
\end{equation}
```

El polinomio del denominador, tambien llamado **ecuación caracteristica** es de primer grado ( tiene un solo *polo* ).  


El diagrama en bloques en lazo cerrado del RC constituye una *equivalencia matemática* útil **para analizar la dinámica del sistema**. Esto no implica que el circuito RC posea una retroalimentación física explícita

En particular, un circuito RC no compara la salida contra la entrada, ni posee un sumador de error o un controlador como en los sistemas clásicos de control. La dinámica del sistema surge porque el capacitor *almacena energía* e introduce dependencia temporal en la evolución del voltaje y la corriente.


\begin{figure}[H]
\centering
\includegraphics[width=1.0\textwidth,trim=0cm 7cm 0cm 4cm,clip]{./img/rc_control.pdf}
\caption{RC como sistema en lazo cerrado}
\label{fig:rc_a_bloques}
\end{figure}

En resumen, un RC es:

* Un sistema lineal e invariante en el tiempo
* Un sistema de primer orden con un solo polo **real** negativo $s=-1/RC$, o bien , ya que la constante de tiempo  $\tau = RC$ , el polo es $s=-1/ \tau$
* Un polo real produce una respuesta exponencial no oscilatoria
* Entre mas cerca queda el polo del eje imaginario (es decir, mas próximo a cero), mas lento es el tiempo de establecimiento

**Al aplicar un *escalón* al $RC$:** La corriente en el circuito (o la tensión en la resistencia) responde con una exponencial decreciente; la tensión en el capacitor responde con una exponencial creciente hacia el valor de escalón.

\newpage 

El sigiente código julia muestra la respuesta temporal del RC:

``` julia
using ControlSystems, Plots
#  Respuesta al escalón / cerrar switch
s = tf("s")
R = 1000    # 1 KOhm
C = 100e-6  # 100 microfaradios

G = 1 / (R*C*s + 1)  

# Respuesta al escalon (5VDC, ejemplo)
t = 0:0.001:0.5
y, t_out = step(G, t)

y = vec(y)

plot(t_out, y,
     xlabel="Tiempo (s)",
     ylabel="Voltaje en capacitor (V)",
     title="Carga de un capacitor",
     legend=false)
savefig("respuesta_escalon.png")
```

\vspace{1cm}

\begin{figure}[H]
\centering
\includegraphics[height=0.3\textheight]{./img/respuesta_escalon.png}
\caption{Respuesta al escalón unitario}
\end{figure}

\newpage

