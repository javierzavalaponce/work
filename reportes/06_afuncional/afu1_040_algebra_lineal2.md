```{=latex}
\clearpage
```
## Norma

La norma de un vector es, esencialmente, su longitud o magnitud. En $\mathbb R^2$ se usa el teorema de Pitágoras, por ejemplo, el vector $(3,4)$ tiene longitud $5$. Se usa la doble barra para denotar la norma, en este caso:


```{=latex}
\[
\| (3,4) \| = 5
\]
```
Aquí empieza a verse por qué el producto interno generaliza la noción geométrica de longitud.

```{=latex}
\[
\|u\| = \sqrt{\langle u,u\rangle}
\]
```

En $\mathbb R^n$, la norma euclídea habitual es

```{=latex}
\[
\|\mathbf{v}\|
=
\sqrt{v_1^2+v_2^2+\cdots+v_n^2}
\]
```



	
Más adelante veremos que no existe una única norma. Hay normas 1, 2, infinito, etc., y eso será muy importante para análisis funcional.

***Nota:***
Una función también puede ser considerada un elemento de un espacio: $f(x) \in V$
¿Qué significa la *"longitud"* de una función?
Dos posibilidades diferentes serían:

```{=latex}
\[
\|f\|_\infty = \max_x |f(x)|
\]
```

```{=latex}
\[
\|f\|_2 = \sqrt{\int |f(x)|^2\,dx}
\]
```
Depende de cómo decidamos medir el tamaño del elemento.
Ese es uno de los saltos conceptuales importantes hacia análisis funcional.


## Transformaciones lineales

Una transformación lineal es una función que toma vectores de un espacio vectorial y los transforma en vectores de otro espacio vectorial, respetando las operaciones de suma y multiplicación por escalares.

Si

```{=latex}
\[
T:V\rightarrow W
\]
```

es una transformación, decimos que es lineal si cumple las dos propiedades:

```{=latex}
\[
T(u+v)=T(u)+T(v)
\]

\[
T(\alpha u)=\alpha T(u)
\]
```

para cualesquiera $u,v\in V$ y cualquier escalar $\alpha$.

Ejemplo (transformación simplemente duplica la longitud de los vectores):

```{=latex}
\[
T:\mathbb R^2\rightarrow\mathbb R^2
\]

\[
T(x,y)=(2x,2y).
\]
```	

Geométricamente, una transformación lineal puede estirar, comprimir, girar, reflejar o combinar estos efectos sobre los vectores. Lo importante es que una transformación lineal conserva las combinaciones lineales. Si


```{=latex}
\[
w=\alpha u+\beta v,
\]
\[
T(w)
=
T(\alpha u+\beta v)
=
\alpha T(u)+\beta T(v).
\]
```	

Esta propiedad será fundamental cuando estudiemos bases y matrices, porque permitirá describir una transformación lineal a partir de lo que hace sobre los vectores de una base.

### De transformación lineal a matriz

Ya tenemos una transformación lineal
$T:V\rightarrow W$

Si elegimos una base para $V$ y una base para $W$, podemos representar $T$ mediante una matriz. En el caso más sencillo, consideremos $T: \mathbb R^2 \rightarrow \mathbb R^2$

Supongamos que

```{=latex}
\[
T(x,y)=(2x+y,x−y)
\]
```
Podemos escribir esta transformación como una multiplicación matricial:

```{=latex}

\[
T
\begin{pmatrix}
x\\
y
\end{pmatrix}
=
\begin{pmatrix}
2 & 1\\
1 & -1
\end{pmatrix}
\begin{pmatrix}
x\\
y
\end{pmatrix}.
\]
```

Por lo tanto, la matriz asociada a T es

```{=latex}
\[
A=
\begin{pmatrix}
2 & 1\\
1 & -1
\end{pmatrix}.
\]
```	

La matriz no es otra cosa que una forma de representar la transformación lineal una vez que hemos elegido bases.


(:8484) continua Tpg

## Nucleo

## Imagen


