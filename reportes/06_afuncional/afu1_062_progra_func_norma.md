```{=latex}
\clearpage
```

## Norma de una funcion en lisp


Una *norma* es una función $\|\cdot\|:V\longrightarrow [0,\infty)$
que asigna a cada vector $x \in V$ un número real no negativo, interpretado como su longitud.


En un espacio vectorial normado, la norma de un vector es la distancia entre ese vector y el vector cero.

```{=latex}
\[
\| x \| = d(x,0)
\]
```


| Prop. | Descripción |
|:---------|:------------|
| Positividad y definitud | $\|x\|\geq 0$ , $\|x\|=0\iff x=0$  | 
| Homogeneidad | $\|\alpha x\|=|\alpha|\,\|x\|$, $\forall$ escalar $\alpha$ 
| Desigualdad triangular | $\|x+y\|\leq \|x\|+\|y\|$|

: Propedades de la norma


Ejemplo de espacio vectorial normado:

```{=latex}
\[
( \mathbb R^2,\| \cdot \|_2)
\]
```


### Conexión entre distancia y norma

Una norma permite construir una métrica mediante

```{=latex}
\[
d(x,y):=\| x−y \|
\]
```
(Con $x$ y $y \in \text{ espacio vectorial }V$).
Es decir, para calcular la distancia entre $x$ y $y$, se calcula primero el vector que va de $y$ hacia $x$ y despues se calcula la longitud de ese vector.

El mensaje central es este:

* $distancia$ = separación entre dos puntos
* $norma$ = distancia de un vector al cero

\newpage

La norma $L^2$ de una función en un intervalo es:


```{=latex}
\[
\|f\|_2 = \sqrt{\int_a^b |f(x)|^2\,dt}
\]
```

Para implementar la norma, primero necesitamos una función que haga la 
integración numérica. 

\vspace{2.0cm}

```lisp
#lang racket

(define (sum term ini sig fin) ;'term' y 'sig' son  proc.
  (if (> ini fin) 
      0 
      (+ (term ini)        ;se aplica 'term' a un argumento
         (sum term (sig ini) sig fin))))

(define (integral f a b dx)
  (* (sum f (+ a (/ dx 2.0))
            (lambda (x) (+ x dx))
            b)
     dx))

(define (norm f a b dx)
  (sqrt (integral (lambda (x) (sqr (f x)))  a  b  dx)
    ))

(norm sin 0 pi 0.001)
```
1.25331...

\newpage

***sum***: (Recursiva) suma el término correspondiente al punto actual más la misma suma comenzando en el siguiente punto.

```{=latex}
\[
sum(i)=term(i)+sum(sig(i))
\]
```

| Param | Descripción |
|:---------|:------------|
| term | Procedimiento que se aplica al valor actual. | 
| ini | Valor inicial de la sucesión|
| sig | Procedimiento que calcula el siguiente valor|
|fin| Criterio de finalización|

: Parametros de *sum* (Suma sobre una sucesión)



***integral***: Divide el intervalo en pequeños pedazos, evalúa $f$ en el centro de cada pedazo, suma las alturas y multiplica por el ancho $dx$.


| Param | Descripción |
|:---------|:------------|
| f | función a integrar| 
| a | inicio del intervalo|
| b | final del intervalo|
| dx| tamaño de cada pequeño intervalo|

: Parametros de *integral* 


***norma***: 

| Param | Descripción |
|:---------|:------------|
| f | función| 
| a | inicio del intervalo|
| b | final del intervalo|
| dx| resolución numérica|

: Parametros de *norma* 

\newpage
### Norma de $f$ como una lista de valores discretos

La idea es calcular la norma cuando la entrada son dos listas:

```{=latex}
\[
tiempo  = (t_0,t_1,t_2,t_3 \cdots)
\]
```

```{=latex}
\[
funcion = (f_0,f_1,f_2,f_3 \cdots)
\]
```

Si se unen por lineas rectas los valores de $f$,
entonces cada pequeño intervalo aporta a la integral:

```{=latex}
\[
\frac{f_i^2 + f_{i+1}^2}{2}
\left(t_{i+1}-t_i\right).
\]
```

```{=latex}
\[
\boxed{
\|f\|_2
\approx
\sqrt{
\sum_i
\frac{f_i^2 + f_{i+1}^2}{2}
\left(t_{i+1}-t_i\right)
}
}
\]
```

\newpage

```lisp
#lang racket

(define (integral-cuadrados tiempo funcion)
  (if (or (null? (cdr tiempo))
          (null? (cdr funcion)))
      0
      (+ (* (/ (+ (sqr (car funcion))
                   (sqr (cadr funcion)))
                2.0)
            (- (cadr tiempo)
               (car tiempo)))
         (integral-cuadrados (cdr tiempo)
                             (cdr funcion)))))

(define (norma-l2 tiempo funcion)
  (sqrt
   (integral-cuadrados tiempo funcion)))

(define tiempo
  '(0.0 0.1 0.25 0.5 0.8 1.0))

(define funcion
  '(0.0 0.1 0.25 0.5 0.8 1.0))

(norma-l2 tiempo funcion)
```

0.5852...