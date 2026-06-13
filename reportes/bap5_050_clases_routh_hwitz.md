### Criterio de Routh-Hurwitz


El Criterio de Routh-Hurwitz sirve para determinar estabilidad de un sistema sin calcular explícitamente las raíces del polinomio a partir de su ecuación característica.
Sea $P(s)$ el polinomio, p. ej:


```{=latex}
\begin{equation}
\begin{aligned}
P(s)=a_n s^n + a_{n-1}s^{n-1} + a_{n-2}s^{n-2} + \cdots + a_0
\end{aligned}
\end{equation}
```
\

El *algoritmo* de este criterio es:


1. Construir la tabla de Routh colocando en la primera columna (columna pivote) todas las potencias de $s$

2. Fila $s^n$ Se colocan coeficientes alternados empezando desde el mayor grado: 
$a_n , a_{n-2} , a_{n-4} \cdots$

3. Fila $s^{n-1}$ Se colocan los coeficientes (alternados) restantes, si faltan terminos se rellenan con cero: 
$a_{n-1} , a_{n-3} , a_{n-5} \cdots$

4. Calcular filas siguientes. Cada elemento se calcula mediante un determinante dividido por el primer elemento de la fila anterior.

5. Si en la primera columna, ocurren $n$ cambios de signo, entonces el sistema tiene
$n$ polos inestables.

Más concretamente, si se tiene:

\begin{center}
\begin{tabular}{c|c c c}
$s^n$     & $\alpha$ & $b$ & $C$ \\
$s^{n-1}$ & $\phi$ & $e$ & $F$ \\
$s^{n-2}$ & $\gamma$ & $H$ & ...\\
...& & &
\end{tabular}
\end{center}

Entonces los elementos $\gamma$ y $H$ de la siguiente fila son:

```{=latex}
\begin{equation}
\begin{aligned}
\gamma = \frac{(\phi)(b)-(\alpha)(e)}{\phi}
\end{aligned}
\end{equation}
```

```{=latex}
\begin{equation}
\begin{aligned}
H = \frac{(\phi)(C)-(\alpha)(F)}{\phi}
\end{aligned}
\end{equation}
```


**Para estabilidad:**
Todos los elementos de la primera columna deben ser positivos.
Cada cambio de signo en la primera columna implica una raíz en el semiplano derecho (un polo inestable).

\newpage

**Ejemplo**, sea el siguiente sistema:

```{=latex}
\begin{equation}
\begin{aligned}
G(s) = \frac{1}{(s-1)(s+3)(s+6)}
\end{aligned}
\end{equation}
```

Determinar la k estabilizante al aplicar retroalimentación estatica.

\begin{figure}[H]
\centering
\includegraphics[width=0.6\textwidth,trim=0cm 7cm 0cm 4cm,clip]{./img/criteriorh.pdf}
\caption{Aplicando retroalimentación}
\label{fig:criteriorh}
\end{figure}


Debido al lazo de retroalimentación,
surge una nueva funcion de transferencia,
es decir $G_2(s) = G(s) / (1+kG(s))$ 

```{=latex}
\begin{equation}
\begin{aligned}
G_2(s) = \frac{1}{(s-1)(s+3)(s+6)+k}
\end{aligned}
\end{equation}
```

Desarrollando, la ecuación caracteristica es:

```{=latex}
\begin{equation}
\begin{aligned}
s^3 + 8s^2 + 9s + (k-18) = 0
\end{aligned}
\end{equation}
```

Aplicando lo anterior:

\begin{center}
\begin{tabular}{c|cc}
$s^3$ & $1$ & $9$ \\
$s^2$ & $8$ & $k-18$ \\
$s^1$ & $\dfrac{90-k}{8}$ & $0$ \\
$s^0$ & $k-18$ &
\end{tabular}
\end{center}

El criterio de estabilidad dice que todos los elementos de
la primera columna deben ser positivos:

```{=latex}
\begin{equation}
\begin{aligned}
1 > 0 \\
8 > 0 \\
\frac{90-k}{8} > 0 \\
k - 18 > 0
\end{aligned}
\end{equation}
```
Finalmente: 
```{=latex}
\begin{equation}
\begin{aligned}
18 < k < 90
\end{aligned}
\end{equation}
```



El criterio de Routh–Hurwitz permite determinar:

* Cuántas raíces tienen parte real positiva (inestables)
* Cuántas están en el semiplano izquierdo (estables)
* Y qué condiciones deben cumplir los coeficientes (en función de k) para que *todas* las raíces sean estables

\newpage