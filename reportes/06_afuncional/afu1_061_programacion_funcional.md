```{=latex}
\clearpage
```
# Programación funcional

## Paradigma

La programación funcional es un *paradigma* de programación en el que los programas se construyen principalmente mediante funciones, tratándolas como valores que pueden almacenarse, pasarse como argumentos y ser devueltas por otras funciones. Se inspira en el concepto matemático de función, donde una entrada produce una salida. Por ejemplo,
tomemos la función $f(x)=2x +3$.



```c
;(define nombre valor)
(define (f x)
  (+ (* 2 x) 3))
```

Ahora define una función llamada *line* que recibe $m$ y $b$, y devuelve una (otra) función que recibe $x$ y calcula $mx+b$:

*line* recibe los parámetros de una recta y devuelve la función correspondiente a esa recta


```c
;lineas.rkt
#lang racket
(define (line m b)
  (lambda (x)
    (+ (* m x) b)))

(define l1 (line 2 1))
  
(displayln (l1 5))

```
