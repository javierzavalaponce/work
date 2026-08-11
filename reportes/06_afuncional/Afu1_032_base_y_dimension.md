```{=latex}
\clearpage
```


# Preparacion clase: Bases y dimensión

## Objetivo

En esta sección responderemos dos preguntas fundamentales del Álgebra Lineal:

1. ¿Cuál es el número mínimo de vectores necesario para construir cualquier vector de un espacio?
2. ¿Cómo podemos saber si algunos de esos vectores son redundantes?

Responder estas preguntas nos llevará de manera natural a los conceptos de **independencia lineal**, **base** y **dimensión**.



## El problema

Consideremos el plano $\mathbb{R}^2$

Sean los vectores

```{=latex}
\[
u=(1,0), \qquad v=(0,1).
\]
```
Surge la siguiente pregunta:

*  ¿Es posible construir cualquier vector del plano utilizando únicamente estos dos vectores?

Por ejemplo,

```{=latex}
\[
(3,-2).
\]
```

Observamos que

```{=latex}
\[
3u-2v=(3,-2).
\]
```

Es decir,

```{=latex}
\[
3(1,0)-2(0,1)=(3,-2).
\]
```
Esto nos lleva al primer concepto importante.

### Combinación lineal

Una **combinación lineal** de dos vectores consiste en multiplicar cada uno por un escalar y sumar los resultados.

En general,

```{=latex}
\[
au+bv,
\]
```

donde $a$ y $b$ son números reales.

En este ejemplo, cualquier vector del plano puede escribirse como una combinación lineal de $u$ y $v$.


## ¿Qué ocurre si elegimos mal los vectores?

Consideremos ahora


```{=latex}
\[
u=(1,1), \qquad
v=(2,2).
\]
```

Intentemos obtener

```{=latex}
\[
(1,0).
\]
```


Después de varios intentos observamos que no parece posible.

Esto nos lleva a una nueva pregunta.

* ¿Será que estos dos vectores están haciendo exactamente el mismo trabajo?

Intuitivamente parece que sí, pues ambos apuntan en la misma dirección.

Necesitamos una forma matemática de demostrarlo.


## ¿Cómo demostrar que un vector es redundante?

Supongamos que existen escalares \(a\) y \(b\) tales que

```{=latex}
\[
au+bv=0.
\]
```

Sustituyendo los vectores,

```{=latex}
\[
a(1,1)+b(2,2)=0.
\]
```

Realizando la suma,

```{=latex}
\[
(a+2b,\;a+2b)=(0,0).
\]
```

Por lo tanto,

```{=latex}
\[
a+2b=0.
\]
```

Esta ecuación posee infinitas soluciones.

Por ejemplo,

```{=latex}
\[
a=-2,\qquad b=1.
\]
```

Entonces

```{=latex}
\[
-2u+v=0,
\]
```

o equivalentemente,

```{=latex}
\[
v=2u.
\]
```

Esto demuestra que uno de los vectores puede escribirse utilizando el otro.

En consecuencia, uno de ellos **es redundante**.



## Independencia lineal

La observación anterior motiva la siguiente definición.

### Definición

Un conjunto de vectores


```{=latex}
\[
\{v_1,v_2,\ldots,v_n\}
\]
```

se dice **linealmente independiente** si la igualdad

```{=latex}
\[
a_1v_1+a_2v_2+\cdots+a_nv_n=0
\]
```

implica necesariamente

```{=latex}
\[
a_1=a_2=\cdots=a_n=0.
\]
```

Es decir, la única forma de obtener el vector cero es utilizando únicamente los coeficientes nulos.

#### Interpretación

En términos sencillos,

* Ningún vector del conjunto puede construirse utilizando los demás.

Esta es la verdadera idea detrás de la independencia lineal.



## Interpretación geométrica

En el plano ocurren dos situaciones muy diferentes.

* Si dos vectores apuntan en la misma dirección, entonces uno es múltiplo del otro y son **linealmente dependientes**.

* Si apuntan en direcciones distintas, entonces ninguno puede construirse a partir del otro y son **linealmente independientes**.

Desde un punto de vista geométrico,

* los vectores dependientes generan únicamente una recta;

* los vectores independientes generan todo el plano.



## Generalización

Hasta ahora hemos trabajado únicamente en $\mathbb{R}^2$

Sin embargo, la definición de independencia lineal nunca utilizó propiedades particulares del plano.

La expresión

```{=latex}
\[
a_1v_1+a_2v_2+\cdots+a_nv_n=0
\]
```

tiene sentido en cualquier espacio vectorial.

Por ello, el concepto de independencia lineal puede aplicarse igualmente a

* vectores de $\mathbb{R}^3$

* matrices,

* polinomios,
* funciones,
* sucesiones,
* señales,

o cualquier otro espacio vectorial.


## El nacimiento del concepto de base

Ahora podemos formular una nueva pregunta.

* ¿Cuál es el conjunto más pequeño de vectores que permite construir todo el espacio?

La respuesta es precisamente una **base**.

Una base es un conjunto de vectores que cumple simultáneamente dos condiciones:

* genera todo el espacio;
* es linealmente independiente.

En otras palabras,

* no falta ningún vector;
* no sobra ningún vector.

## Definición de base

### Definición

Sea $V$ un espacio vectorial.

Un conjunto

```{=latex}
\[
B=\{v_1,v_2,\ldots,v_n\}
\]
```

es una **base** de $V$ si

1. todo vector de $V$ puede escribirse como combinación lineal de los vectores de $B$;

2. los vectores de $B$ son linealmente independientes.

#### Idea fundamental

Una base es un conjunto mínimo de generadores.

Equivalentemente,

es un conjunto máximo de vectores linealmente independientes.



## Dimensión

Una vez definido el concepto de base, surge una última pregunta.

* ¿Cuántos vectores tiene una base?

En $\mathbb{R}^2$ toda base posee exactamente dos vectores.

En $\mathbb{R}^3$ toda base posee exactamente tres vectores.

Este hecho motiva la siguiente definición.

### Definición

La **dimensión** de un espacio vectorial es el número de vectores que contiene cualquiera de sus bases.

Así, $dim(\mathbb{R}^2)=2$ y $dim(\mathbb{R}^3)=3$.

La dimensión mide el número mínimo de vectores independientes necesarios para generar todo el espacio.



### Resumen conceptual

El desarrollo seguido en esta sección puede resumirse mediante el siguiente esquema:

```bash
Problema
Combinación lineal
Independencia lineal
Base
Dimensión
```

Cada concepto surge naturalmente como respuesta a una pregunta planteada por el anterior, formando una cadena lógica que permite comprender el significado de la noción de base en un espacio vectorial.