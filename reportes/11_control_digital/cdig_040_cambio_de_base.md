```{=latex}
\clearpage
```

## Cambio de Base. 

### Forma canonica controlador

Partiendo de un sistema expresado en espacio de estados,

$\dot{x} = Ax + Bu$
\
$y = Cx + Du$
\

Con $A \in \mathbb{R^{n\times n}}$
y $B \in \mathbb{R^{n\times 1}}$
se busca una transformación de similaridad 
$x=Tz$ 
tal que el sistema transformado


```{=latex}
\begin{equation}
\begin{aligned}
\dot{z} &= \bar{A} z +Bu \\
y&=\bar{C}z+Du
\end{aligned}
\end{equation}
```

con

```{=latex}
\begin{equation}
\begin{aligned}
\bar{A}&=T^{-1}AT \\
\bar{B}&=T^{-1}B  \\
\bar{C}&=CT
\end{aligned}
\end{equation}
```

quede expresado en forma canónica controlador (también llamada forma compañera o de Brunovsky):

```{=latex}
\[
\bar{A} =
\begin{bmatrix}
0 & 1 & 0 & \cdots & 0 \\
0 & 0 & 1 & \cdots & 0 \\
\vdots & & & \ddots & \vdots \\
0 & 0 & 0 & \cdots & 1 \\
-a_0 & -a_1 & -a_2 & \cdots & -a_{n-1}
\end{bmatrix}
\]
```


```{=latex}
\[
\bar{B} =
\begin{bmatrix}
0 \\ 0 \\ \vdots \\ 0 \\ 1
\end{bmatrix}
\]
```

donde los $a_i$ son los coeficientes del polinomio característico de $A$:

```{=latex}
\[
det(SI-A) = s^n + a_{n-1}s^{n-1} + \cdots  a_1 s + a_0
\]
```

### Algoritmo de cálculo de la transformación $T$

**1. Verificar controlabilidad**

```{=latex}
\[
M = [B \; AB \; A^{2}B \;  ... \; A^{n-1}B] \in \mathbb{R}^{n\times n}
\]
```
Si $rango⁡(M)=n$, el sistema es controlable y la transformación existe. 
Si $rango⁡(M)<n$, no existe forma canónica controlador (el sistema no es alcanzable).

**2. Obtener el polinomio característico**

Calcular:
```{=latex}
\[
det(SI-A) = s^n + a_{n-1}s^{n-1} + \cdots  a_1 s + a_0
\]
```

**3. Construir la matriz WW (matriz compañera auxiliar)**


\subsubsection{Paso 3 --- Construir la matriz \(W\) (matriz compañera auxiliar)}

Se define la matriz de coeficientes en forma invertida:

```{=latex}
\[
W =
\begin{bmatrix}
a_1 & a_2 & \cdots & a_{n-1} & 1 \\
a_2 & a_3 & \cdots & 1 & 0 \\
\vdots & \vdots & \ddots & \vdots & \vdots \\
a_{n-1} & 1 & \cdots & 0 & 0 \\
1 & 0 & \cdots & 0 & 0
\end{bmatrix}
\]
```

(Es una matriz de Toeplitz invertida construida con los coeficientes $a_i$)


\newpage 

**4. Calcular $T$**


```{=latex}
\[
\boxed{
T=MW
}
\]
```


```{=latex}
\[
\begin{aligned}
\bar{A}&=T^{-1}AT \\
\bar{B}&=T^{-1}B
\end{aligned}
\]
```

**Resumen del algoritmo**

\begin{enumerate}
\item Calcular $M = \big[\,B \;\; AB \;\; \cdots \;\; A^{n-1}B\,\big]$
\item Verificar $\operatorname{rango}(M) = n$
\item Calcular $\det(sI-A) = s^n + a_{n-1}s^{n-1} + \cdots + a_0$
\item Construir $W$ con los $a_i$
\item $T = M\,W$
\item $\bar{A} = T^{-1}AT, \quad \bar{B} = T^{-1}B$
\end{enumerate}


\newpage



Como hizo Kalman para demostrar que basta construir una matriz $M$ de controlabilidad asi:

```{=latex}
\[
M = [B \; AB \; A^{2}B \;  ... \; A^{n-1}B] \in \mathbb{R}^{n\times n}
\]
```

que significa en terminos geometricos o algebraicos el rango de una matriz. Que se concluye del rango



-----
muestrame como es que puedo desarrollar detalladamente el proceso matematico por el cual mostrar que el producto punto se puede expresar como una transformación lineal
y que relaciones guarda esto con el producto punto de funciones cuando veo estas como vectores. añade organizada y consistentemente la explicacion matematica de como visualizar funciones como vectores de dimension infinita 





(asi se dice (?)) 