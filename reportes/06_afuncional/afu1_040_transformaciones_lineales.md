```{=latex}
\clearpage
```

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

### El producto punto como "transformación lineal"

En realidad, el producto punto es una función de dos variables: 

$\mathbb{R}^n \times \mathbb{R}^n \longrightarrow \mathbb{R}$ 

**no** es una transformación lineal. Sin embargo, si *fijamos* uno de los vectores, por ejemplo $v$, obtenemos una función

```{=latex}
\[
T_v:\mathbb R^n \longrightarrow \mathbb R
\]
```	

definida por

```{=latex}
\[
\boxed{T_v(u)=u\cdot v}
\]
```	
Ahora sí tenemos una transformación lineal.

Fijemos el vector

```{=latex}
\[
v=
\begin{bmatrix}
v_1\\
\vdots\\
v_n
\end{bmatrix}.
\]
```

Definimos la transformación

```{=latex}
\[
T_v(u)=u \cdot v
\]
```

Entonces

```{=latex}
\[
T_v(u)
=
\begin{bmatrix}
u_1 & \cdots & u_n
\end{bmatrix}
\begin{bmatrix}
v_1\\
\vdots\\
v_n
\end{bmatrix}.
\]
```

Por lo tanto,

```{=latex}
\[
T_v(u)
=
u_1 v_1 + \cdots + u_n v_n.
\]
```

### Proyección

La interpretación geométrica del producto punto permite relacionarlo directamente con la proyección de un vector sobre otro.

Sean $u,v\in\mathbb R^n$, con $v\neq 0$. Por definición del producto punto,

```{=latex}
\[
u\cdot v
=
\|u\|\,\|v\|\cos\theta,
\]
```

donde $\theta$ es el ángulo entre los vectores $u$ y $v$

La cantidad

```{=latex}
\[
\frac{u\cdot v}{\|v\|}
\]
```

representa la componente escalar de $u$ en la dirección de $v$. Por lo tanto, la proyección *ortogonal* de $u$ sobre $v$ es:

```{=latex}
\[
\boxed{
\operatorname{proj}_v(u)
=
\frac{u\cdot v}{v\cdot v}\,v
}
\]
```

ya que

```{=latex}
\[
v\cdot v=\|v\|^2.
\]
```

Así,

```{=latex}
\[
\operatorname{proj}_v(u)
=
\frac{u\cdot v}{\|v\|^2}\,v.
\]
```

Aquí aparece una relación importante con la transformación lineal definida anteriormente. Como

```{=latex}
\[
T_v(u)=u\cdot v,
\]
```

podemos escribir la proyección como

```{=latex}
\[
\boxed{
\operatorname{proj}_v(u)
=
\frac{T_v(u)}{\|v\|^2}\,v.
}
\]
```

Es decir, el producto punto con $v$ toma el vector $u$, extrae de él la información correspondiente a la dirección de $v$, y posteriormente esa cantidad escalar se utiliza para construir el vector proyectado.

### Ortogonalidad

La misma transformación permite caracterizar la ortogonalidad.

Dos vectores $u$ y $v$ son ortogonales si

```{=latex}
\[
u\perp v
\quad\Longleftrightarrow\quad
u\cdot v=0.
\]
```

Utilizando la transformación $T_v$, esto puede escribirse como

```{=latex}
\[
\boxed{
u\perp v
\quad\Longleftrightarrow\quad
T_v(u)=0.
}
\]
```

Por lo tanto, el conjunto de todos los vectores ortogonales a $v$ es precisamente el *núcleo* (se cubre este tema mas adelante) de la transformación lineal $T_v$:

```{=latex}
\[
\boxed{
\ker(T_v)
=
\{u\in\mathbb R^n:u\cdot v=0\}
=
v^\perp.
}
\]
```

Geométricamente, $v^\perp$ = todos los vectores perpendiculares a $v$

\vspace{2.0cm}
\begin{center}
\rule{0.6\textwidth}{0.4pt}
\end{center}
\begin{figure}[H]
\centering
\includegraphics[width=0.41\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/pendulum.png}
\end{figure}


\newpage
### Producto punto y coordenadas respecto de una base

Esta interpretación también permite comprender por qué el producto punto está relacionado con las coordenadas de un vector.

Supongamos que tenemos una base ortonormal

```{=latex}
\[
\mathcal B=
\{e_1,e_2,\ldots,e_n\}.
\]
```

Cualquier vector $u\in\mathbb R^n$ puede escribirse como

```{=latex}
\[
u
=
c_1e_1+c_2e_2+\cdots+c_ne_n.
\]
```

Para encontrar una coordenada $c_i$, tomamos el producto punto con $e_i$:

```{=latex}
\[
u\cdot e_i
=
(c_1e_1+\cdots+c_ne_n)\cdot e_i.
\]
```

Por la linealidad del producto punto,

```{=latex}
\[
u\cdot e_i
=
c_1(e_1\cdot e_i)
+\cdots+
c_n(e_n\cdot e_i).
\]
```

Como la base es ortonormal,

```{=latex}
\[
e_j\cdot e_i
=
\begin{cases}
1,&j=i,\\
0,&j\neq i.
\end{cases}
\]
```

Todos los términos desaparecen excepto el correspondiente a $c_i$. Por tanto,

```{=latex}
\[
\boxed{
u\cdot e_i=c_i.
}
\]
```

Así, en una base ortonormal, el producto punto con un vector de la base **extrae directamente una coordenada**.

Podemos escribir entonces

```{=latex}
\[
\boxed{
u
=
\sum_{i=1}^n
(u\cdot e_i)e_i.
}
\]
```

Esta expresión muestra una conexión profunda entre producto punto, proyección y cambio de base: cada término

```{=latex}
\[
(u\cdot e_i)e_i
\]
```

es la proyección de $u$ sobre la dirección $e_i$, y la suma de todas esas proyecciones reconstruye el vector $u$

### Cambio de base

El resultado anterior depende de que la base sea ortonormal. Si tenemos una base cualquiera

```{=latex}
\[
\mathcal B=\{b_1,\ldots,b_n\},
\]
```

un vector puede escribirse como

```{=latex}
\[
u=c_1b_1+\cdots+c_nb_n.
\]
```

En general, las coordenadas $c_i$ **no** se obtienen simplemente mediante

```{=latex}
\[
u\cdot b_i.
\]
```

Esto se debe a que los vectores $b_i$ no tienen necesariamente longitud unitaria ni son necesariamente ortogonales entre sí.

En una base ortonormal, en cambio, la geometría simplifica el cambio de coordenadas:

```{=latex}
\[
\boxed{
[u]_{\mathcal B}
=
\begin{bmatrix}
u\cdot e_1\\
u\cdot e_2\\
\vdots\\
u\cdot e_n
\end{bmatrix}.
}
\]
```

Por esta razón, las bases ortonormales son especialmente importantes: el producto punto permite obtener directamente las coordenadas del vector mediante proyecciones sobre los vectores de la base.

Así que la ortogonalidad puede verse como el núcleo de una transformación lineal construida mediante el producto punto.

Esto prepara el terreno para estudiar funciones como vectores, aparecerá la misma estructura:

$T_g(f)=\langle f,g\rangle$

y entonces

$\ker(T_g) = \{f:\langle f,g\rangle=0\}$

Es decir, el conjunto de funciones ortogonales a $g$. 

\vspace{2.5cm}

\begin{figure}[H]
\centering
\includegraphics[width=0.45\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/velo00.png}
\end{figure}
\newpage

### Nucleo

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


### Imagen


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

