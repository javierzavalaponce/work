```{=latex}
\clearpage
```
# Distancias

Seccion incompleta..

## Distancia entre dos puntos


```{=latex}
\[
d=
(a,b)
\]
```
seccion incompleta

## Distancia entre un punto y una recta

```{=latex}
\[
d=
(a,b)
\]
```
seccion incompleta

## Distancia entre dos conjuntos

```{=latex}
\[
d=min
(A,B)
\]
```
seccion incompleta

\newpage
# Definicion de espacio y estado

El *estado* $x$ (por ejemplo: la posición y velocidad de un péndulo) 
de un sistema.

```{=latex}
\[
x=
\begin{bmatrix}
{\theta}\\
{w}
\end{bmatrix}
\]
```

es un objeto abstracto que vive en un universo (*el espacio de estados*).

El vector de estado $x=[\theta,w]$ es la representación matemática de ese estado mediante sus coordenadas respecto a una sistema de referencia llamado *base*

* Estado: el objeto abstracto.
* Espacio de estados: el conjunto donde viven todos los estados posibles.
* Base: el sistema de referencia elegido dentro del espacio.
* Vector de estado: las coordenadas del estado respecto a una base

\vspace{1cm}

\begin{center}
\rule{0.6\textwidth}{0.4pt}
\end{center}

\vspace{1cm}

*¿Qué es un espacio de estados?*

El espacio de estados no es una *función*, es el espacio (*conjunto*) vectorial que contiene todos los valores posibles que el vector de estado puede tomar.

* Un estado es una *lista* de números.
* El espacio de estados son *todas las listas* posibles de ese tipo.

```{=latex}
\[
\mathcal{V}
=
\left\{
a_1e_1+a_2e_2+\cdots+a_ne_n
\;\middle|\;
a_i\in\mathbb{R}
\right\}
\]
```
donde $e_1,e_2,\ldots,e_n$ son los vectores de la base y
$a_1,a_2,\ldots,a_n$ son coeficientes *reales*.

\vspace{1cm}

\begin{center}
\rule{0.6\textwidth}{0.4pt}
\end{center}

\newpage

Un estado $x$ se representa mediante un vector, y ese vector puede expresarse como una combinación lineal de los vectores de una ***base***.

Todo espacio vectorial puede describirse a partir de una *base*, es decir, un conjunto de vectores linealmente independientes con los cuales es posible construir cualquier otro vector del espacio. Matemáticamente, el espacio generado por una base se expresa como el conjunto de *todas las combinaciones lineales posibles de sus vectores*. 

Es importante notar que una combinación lineal representa un único vector (o estado), mientras que el conjunto de todas las combinaciones lineales constituye el espacio vectorial completo.


\newpage
