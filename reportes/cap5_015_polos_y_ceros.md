\newpage
### Polos y ceros

Definición, en una **funcion de transferencia** (expresada como division de Polinomios)

```{=latex}
\begin{equation}
\begin{aligned}
ft =  H(s)= \frac{N(s)}{D(s)}
\end{aligned}
\end{equation}
```



* Los ceros de una $ft$ son las $frecuencias$ (valores de $s$) para los
        cuales el *numerador* $N(s)=0$

* Los polos de una $ft$ son las $frecuencias$ (valores de $s$) para los
        cuales el *denominador* $D(s)=0$

Forma general de una $ft$:

```{=latex}
\begin{equation}
\begin{aligned}
  H(s)=k \cdot \frac{(s - z_1)(s - z_2)...(s - z_m)}{(s - p_1)(s - p_2)...(s - p_n)}= k \cdot \frac{\displaystyle\prod_{i=1}^{m} (s - z_i)}{\displaystyle\prod_{j=1}^{n} (s - p_j)}
\end{aligned}
\end{equation}
```

La función de transferencia $H(s)$ en el dominio de Laplace se relaciona con la respuesta temporal $h(t)$ mediante la transformada inversa:

```{=latex}
\begin{equation}
\begin{aligned}
h(t) = \mathcal{L}^{-1}\{H(s)\}
\end{aligned}
\end{equation}
```

* Los polos determinan directamente los *modos naturales* (un modo = una pieza elemental de comportamiento temporal). 
* Los ceros no crean modos nuevos; más bien moldean, cancelan o enfatizan esos modos.

En el plano complejo, la ubicación de polos y ceros codifica directamente la manera en que un sistema evoluciona en el tiempo.

\begin{table}[H]
\centering

\begin{tabular}{
|>{\centering\arraybackslash}p{0.26\textwidth}
|>{\centering\arraybackslash}p{0.30\textwidth}
|>{\centering\arraybackslash}p{0.33\textwidth}|
}

\hline

\textbf{Condición} &
\textbf{Ubicación de polos} &
\textbf{Respuesta temporal} \\

\hline

Subamortiguado &
Polos complejos conjugados &
Oscilación con sobreimpulso \\

\hline

Críticamente amortiguado &
Dos polos reales iguales &
Respuesta más rápida sin oscilación \\

\hline

Sobreamortiguado &
Dos polos reales negativos distintos &
Respuesta lenta sin oscilación \\

\hline

Inestable &
Algún polo con $\Re(s)>0$ &
Respuesta creciente \\

\hline

\end{tabular}

\caption{Relación entre amortiguamiento y ubicación de polos}
\label{tab:amortiguamiento_polos}

\end{table}

\
\

* Polos complejos conjugados. Oscilación con sobreimpulso

\begin{figure}[H]
\centering
\includegraphics[width=1.1\textwidth]{./img/01_subamortiguado.png}
\caption{Subamortiguado}
\end{figure}

\newpage

* Dos polos reales iguales. Respuesta más rápida sin oscilación

\begin{figure}[H]
\centering
\includegraphics[width=0.94\textwidth]{./img/02_criticamente_amortiguado.png}
\caption{Criticamente amortiguado}
\end{figure}


* Dos polos reales negativos distintos. Respuesta lenta sin oscilación


\begin{figure}[H]
\centering
\includegraphics[width=0.94\textwidth]{./img/03_sobreamortiguado.png}
\caption{Sobreamortiguado}
\end{figure}


* Algún polo con $\Re(s)>0$. Respuesta creciente


\begin{figure}[H]
\centering
\includegraphics[width=0.94\textwidth]{./img/04_inestable.png}
\caption{Inestable}
\end{figure}

***Nota:*** Un controlador, al introducir nuevos polos y ceros, no sólo *corrige error*. También:

* altera el orden del sistema,
* modifica la ubicación de los polos,
* cambia la dinámica y la respuesta temporal.