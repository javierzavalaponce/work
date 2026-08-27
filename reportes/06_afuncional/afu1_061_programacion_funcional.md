```{=latex}
\clearpage
```
# Programación funcional

## Init

La programación funcional es un paradigma de programación en el que los programas se construyen principalmente mediante funciones, tratándolas como valores que pueden almacenarse en variables, pasarse como argumentos y ser devueltas por otras funciones. Se inspira en el concepto matemático de función, donde una entrada produce una salida, y busca reducir los cambios de estado y efectos secundarios. Lenguajes como Racket, Lisp, Scheme, Haskell y, en cierta medida, Python y JavaScript, permiten utilizar este enfoque

ejemplo lineas.rkt

```bash
#lang racket
(define (line m b)
  (lambda (x)
    (+ (* m x) b)))

(define l1 (line 2 1))
(define l2 (line -1 3))
(define l3 (line 0.5 -2))

(displayln (l1 5))
(displayln (l2 5))
(displayln (l3 10))
```
