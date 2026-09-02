```{=latex}
\clearpage
```
# Programación funcional

\vspace{1cm}

## Paradigma

La programación funcional es un *paradigma* de programación en el que los programas se construyen principalmente mediante funciones, tratándolas como valores que pueden almacenarse, pasarse como argumentos y ser devueltas por otras funciones. Se inspira en el concepto matemático de función, donde una entrada produce una salida. 

\vspace{1cm}

Los lenguajes como *racket* (dialecto lisp) usan notación polaca, por ejemplo para sumar $(3+2)$, se usa

```c
(+ 3 2)
```
\vspace{1cm}

Tomemos Ahora la función $f(x)=2x +3$.

```c
;(define nombre valor)
(define (f x)
  (+ (* 2 x) 3))
```
\vspace{1cm}

\newpage
## Función que devuelve función

Define una función llamada *line* que recibe dos parámetros, $m$ y $b$, y devuelve otra función. La función devuelta recibe un valor $x$ y calcula $mx+b$:

\vspace{1cm}

```c
;linea_recta.rkt
#lang racket
(define (line m b)
    (lambda (x) (+ (* m x) b)))

(define f (line 2 3))
  
(displayln (f 1))

```
\vspace{1cm}

La linea *(define f (line 2 3))* hace que $f$ sea la función correspondiente a 
$f(x)=2x+3$. Por eso, para calcular: $f(1)=2(1)+3=5$

Se usa,

```c
(f 1)
```

**Observaciones:**

* *lambda* es palabra reservada en *racket* y es una forma especial que construye un procedimiento sin darle un nombre.

* *line* recibe los parámetros ($m$ y $b$) de una recta y devuelve la función correspondiente a esa recta

* En $(lambda (x) ...)$, no se esta dando nombre a la función; se está creando una función anónima cuyos parámetros son $(x)$.

* En $(lambda (x) (+ (* m x) b))$ no significa que $lambda$ ejecute algo, Significa: *“Construye una función que, cuando posteriormente reciba un x, calculará (+ (* m x) b).”*

\newpage

## Algebra de funciones, ejercicios


| Operacion | Descripción |
|:---------|:------------|
| f_escala$(f,k)(x)=kf(x)$  | Multiplica función por escalar  | 
| f_expande$(f,k)(x)=f(kx)$  | Comprime/expande funcion en el tiempo|  
| f_sum$(f,g)(x)=f(x)+g(x)$  | Suma de funciones  |
| f_shift$(f,k)(x)=f(x+k)$  | Introduce un retardo/adelanto |
| f_offset$(f,k)(x)=k+f(x)$  | Introduce un offset positivo/negativo |

: Ejercicios en Racket

\vspace{1.0cm}


```c
#lang racket
(require plot)
(define (line m b)
    (lambda (x) (+ (* m x) b)))

(define l (line 1 1))

(define (f_escala  f k) (lambda (x) (* k (f x))))
(define (f_expande f k) (lambda (x) (f (* k x))))
(define (f_sum f g)     (lambda (x) (+ (f x) (g x))))
(define (f_shift f k)   (lambda (x) (f (+ k x))))
(define (f_offset f k)  (lambda (x) (+ k (f x))))

(plot-file
  (list
    (function sin -3 3 #:color "red") 
    (function (f_escala  sin 2)   -9 9 #:color "green")
    (function (f_expande sin 2)   -9 9 #:color "blue")
    (function (f_shift   sin 1)   -9 9 #:color "orange")
    (function (f_sum     sin l)   -9 9 #:color "purple")
    (function (f_offset  sin 3) -9 9 #:color "black")
  )
  "plots.png")
```
\newpage

\begin{figure}[H]
\centering
\includegraphics[width=0.85\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/plots_rckt00.png}
\caption{Gráficas}
\label{fig:rckt_tarea0}
\end{figure}