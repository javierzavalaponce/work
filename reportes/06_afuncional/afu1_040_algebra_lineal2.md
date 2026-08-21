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

Ejemplo (transformación que duplica la longitud de los vectores):

```{=latex}
\[
T:\mathbb R^2\rightarrow\mathbb R^2
\]

\[
T(x,y)=(2x,2y).
\]
```	

Geométricamente, una transformación lineal puede estirar, comprimir, girar, reflejar o combinar estos "efectos" sobre los vectores. Lo importante es que una transformación lineal conserva las combinaciones lineales. Si


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

Esta propiedad es fundamental 
porque permite describir una transformación lineal a partir de lo que *hace* sobre los vectores de una base.

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

La matriz $A$ en este caso
es una forma de representar 
la transformación lineal una vez que hemos elegido bases.


\newpage

## Nucleo

El *núcleo* de una transformación lineal $T:V\rightarrow W$ es el conjunto de todos los vectores de $V$ que son transformados en el vector cero de $W$. En otras palabras:
núcleo = lo que la transformación *pierde*.
Se denota por $\ker(T)$ y se define como:

```{=latex}
\[
\ker(T)=\{v\in V:T(v)=0\}.
\]
```

Un ejemplo. Consideremos:

```{=latex}
\[
T: \mathbb{R}^2 \rightarrow \mathbb{R}
\]
```

definida por 

```{=latex}
\[
T(x,y) = x
\] 
```

La transformación simplemente se queda con la primera coordenada, Por ejemplo:
$T(3,7)=3$, es decir, el núcleo de T es el conjunto de los pares ordenados (0,y) tales que y pertenece a los reales:


```{=latex}
\[
\ker(T)=\{(0,y)\mid y\in\mathbb R\}
\]
```

**Observaciones**:

* Dos vectores producen exactamente la misma salida si y solo si su diferencia pertenece al kernel.

```{=latex}
\[
T(u)=T(v)
\quad\Longleftrightarrow\quad u-v\in\ker(T)
\]
```

* Si el núcleo solamente contiene al vector cero: $ker(T)=\{0\}$, entonces no existe ninguna diferencia no nula que la transformación pueda perder. Supongamos que $T(u) = T(v)$, entonces $u-v \in ker(T)$.
Pero como el kernel solo contiene al cero $u-v=0$ implica que $u=v$,
o sea $\ker(T)=\{0\} \Longleftrightarrow \text{T no pierde información entre vectores distintos}$. Lo cual significa que $T$ es *inyectiva*.


## Imagen


Sea $T:V\rightarrow W$ una transformación lineal (donde $V$ y $W$ son espacios vectoriales). La imagen de $T$, denotada como $Im(T)$, se define como:


```{=latex}
\[
Im(T)=\{ w \in W \mid \text{ existe } v \in V \text{ tal que } T(v) = w\}
\]
```

**Propiedad fundamental**

La imagen siempre es un subespacio vectorial del espacio de llegada $W$. Esto significa que:

* Contiene al vector cero de $W$
* Si se tienen dos vectores en la imagen, su suma también está en la imagen.
* Si se multiplica un vector de la imagen por un escalar, el resultado también está en la imagen.


**Ejemplo sencillo**

Para la transformación lineal: $T:\mathbb R^2 \rightarrow \mathbb R^3$
, definida como $T(x,y)=(x,y,0)$, su *imagen*
son todos los vectores en $\mathbb R^3$ que tienen su tercera coordenada igual a cero, es decir,


```{=latex}
\[
Im(T)=\{ (x,y,0) \mid x,y \in \mathbb R \}
\]
```

Esto representa el plano $XY$ dentro de $\mathbb R^3$. Es un subespacio de $\mathbb R^3$, pero no es todo $\mathbb R^3$ (porque no llegamos a vectores con $z \neq 0$).

**Conclusión**

* El Núcleo (*kernel*) dice qué vectores se "pierden" (van a cero).
* La Imagen dice qué vectores son *alcanzables*.
* Para $T:V\rightarrow W$, si la imagen es igual a todo $W$, la transformación se llama *sobreyectiva* (o *epiyectiva*).

The set of all possible vectors you can reach with linear combinations of a given pair of vectors is called the "span" of those two vectors. Restating what we just saw in this lingo, the span of most pairs of 2D vectors is all vectors in 2D space, but when they line up, their span is all vectors whose tip sit on a certain line.
