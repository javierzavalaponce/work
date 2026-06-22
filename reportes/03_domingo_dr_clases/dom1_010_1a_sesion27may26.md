```{=latex}
\clearpage
```

# Optimización por enjambre de partículas


## Introduccion

Considere una placa metalica cuadrada cuyos lados son de longitud  $l$,
se remueven 4 secciones como muestran las líneas punteadas, esto a fin de generar una
caja. Suponga que se desea maximizar el volumen que esa caja puede contener. Observe la figura:


\begin{figure}[H]
\centering
\includegraphics[height=0.4\textheight,trim=0cm 4cm 0cm 4cm,clip]{../img/dom_placa.pdf}
\caption{Volumen de la caja $V(x)=(l-2x)^2x$}
\label{fig:dom_placa}
\end{figure}


Si se fija la longitud $l=10$, la ecuacion del volumen de la figura \ref{fig:dom_placa} se puede expresar como:
 $V(x) = 4x^3-40x^2+100x$ y la búsqueda del volumen deseado se puede resolver como un problema típico del cálculo diferencial buscando los maximos y mínimos de la expresion igualando la derivada a cero, es decir 
$\frac{dV}{dx}=0$ lo cual resulta en que se obtiene el volumen maximo en $x =1.66$. Ver la siguiente figura:

\begin{figure}[H]
\centering
\includegraphics[height=0.4\textheight]{../img/volumen_caja.png}
\caption{$V(x) = 4x^3-40x^2+100x$}
\label{fig:volumen_caja}
\end{figure}

```{=latex}
\[
\frac{dV}{dx}
=
12x^2-80x+100
\]
```

Igualando a cero:

```{=latex}
\[
\begin{aligned}
12x^2-80x+100&=0 \\
3x^2-20x+25&=0 
\end{aligned}
\]
```

```{=latex}
\[
x=\frac{20\pm10}{6}, \qquad
x=\frac{5}{3} \qquad , \qquad 
x=5
\]
```

Como $x=5$ produce volumen cero, el máximo ocurre en $x=5/3$
Sin embargo, se pudo haber hecho un análisis puramente numerico y buscar los valores "a mano":

```{=latex}
\[
\begin{aligned}
V(0) &= 0\\
V(1) &= 64\\ 
V(2) &= 72\\
V(3) &= 48\\
V(4) &= 16\\
V(5) &= 0
\end{aligned}
\]
```
Se observa que el *máximo* valor de $V(x)$ depende del valor de $x$ y que dicho máximo se encuentra en el intervalo $(1,2)$. Ver figura

Si los valores de $x$ (1,2,3,4,5) se interpretan como posiciones dentro de un ***espacio de búsqueda***, entonces cada posición puede considerarse una solución candidata del problema. En el contexto de *Particle Swarm Optimization* (PSO), cada partícula representa una solución candidata y se encuentra ubicada en una posición $x_i$ del espacio de búsqueda.

Para este ejemplo, el espacio de búsqueda corresponde al intervalo $x \in [0,5]$, y cada partícula puede desplazarse dentro de dicho intervalo tras evaluar una ***función objetivo o de costo*** $V(x)$. El propósito del algoritmo es encontrar la posición que maximiza el volumen de la caja.

Por ejemplo: un algoritmo $PSO$ para este caso haría:

1. Soltar N partículas al azar dentro del espacio de búsqueda [0,5]
2. Evaluar el volumen en cada una
3. Cada partícula *recuerda* su mejor posición individual
4. Todas las partículas saben cuál es la mejor *posición global*
5. Mover cada partícula mezclando: su inercia + atracción a su mejor + atracción a la mejor global
6. Repetir desde el paso 2 hasta que todas se agrupen cerca del máximo


\newpage

## Concepto del PSO y ejemplo de aplicación a la sintonización de un control PI


*Un enjambre de partículas "vuela" por el espacio, cada una recuerda su mejor hallazgo, todas siguen a la mejor del grupo, y así convergen al máximo.*


El *espacio de búsqueda* del ejemplo de la introducción es  una sección de la recta real *(eje x)*, sin embargo para otro tipo de problemas, la búsqueda puede operar sobre el plano $(x,y)$, tomemos por ejemplo el caso de un control PI (proporcional integral) en donde la señal de control $u(t)$ esta definida por:


```{=latex}   
\[
u(t)=K_p\,e(t)+K_i\int_{0}^{t} e(\tau)\,d\tau
\]
```


donde $e(t)$ es el error y $u(t)$ es la acción de control. Es decir que la señal de control depende de los valores de
dos constantes, una de integración y una proporcional.
En este caso la noción de particula pudiera ser redefinida como una tupla de valores 
($K_p$,$K_i$) que representa una solución candidata para el problema de sintonización del controlador PI. Cada combinación de valores $(K_p,K_i)$ produce una respuesta dinámica distinta del sistema y, por lo tanto, puede ser evaluada mediante una función de costo ($J$).

La función de costo tiene como propósito cuantificar la *calidad* de la respuesta obtenida para una determinada partícula. Dependiendo de los objetivos de diseño, dicha función puede incorporar criterios tales como:

* minimizar el tiempo de establecimiento;
* minimizar el sobreimpulso (overshoot);
* aproximar una respuesta críticamente amortiguada;
* minimizar el error acumulado;
* cualquier otra métrica de desempeño relevante para la aplicación.


Por ejemplo, si se busca sintonizar el controlador PI para minimizar el tiempo de establecimiento, se puede definir la función de costo como

```{=latex}
\[
J(K_p,K_i)=t_s
\]
```

donde $t_s$ representa el tiempo de establecimiento obtenido al simular el sistema utilizando los parámetros $(K_p,K_i)$. Supóngase que tres partículas del enjambre representan las siguientes soluciones candidatas:

```{=latex}
\[
( K_p , K_i ) = \qquad
(1,0.5),
\qquad
(2,1),
\qquad
(5,3)
\]
```

Al simular el sistema para cada una de estas partículas se obtienen los siguientes tiempos de establecimiento:

```{=latex}
\[
\begin{aligned}
J(1,0.5) &= 3.2 \; s\\
J(2,1)   &= 1.8 \; s\\
J(5,3)   &= 2.4 \; s
\end{aligned}
\]
```

Dado que el objetivo es minimizar la función de costo, la mejor partícula es aquella que produce el menor valor de (J). En este ejemplo, la partícula

```{=latex}
\[
(K_p,K_i)=(2,1)
\]
```

es la mejor solución encontrada hasta el momento, ya que produce el menor tiempo de establecimiento.

El algoritmo PSO repite este procedimiento para todas las partículas del enjambre. Cada partícula recuerda la mejor posición que ha encontrado individualmente y, además, conoce la mejor posición encontrada por todo el grupo. Utilizando esta información, las partículas actualizan su posición dentro del espacio de búsqueda con el propósito de encontrar combinaciones de parámetros que produzcan valores cada vez menores de la función de costo.

