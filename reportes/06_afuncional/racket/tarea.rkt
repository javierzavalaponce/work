;ejercios.rkt
;f_escala:  Multiplica función por escalar
;f_compExp: Comprime/expande funcion en el tiempo
;f_sum:     Suma de funciones
;f_shift:   Introduce un retardo/adelanto
;f_offset:  Introduce un offset positivo/negativo

#lang racket
(require plot)
(define (line m b)
    (lambda (x) (+ (* m x) b)))

(define l (line 1 1))

(define (f_escala  f k) (lambda (x) (* k (f x))))
(define (f_compExp f k) (lambda (x) (f (* k x))))
(define (f_shift f k)   (lambda (x) (f (+ k x))))
(define (f_sum f g)     (lambda (x) (+ (f x) (g x))))
(define (f_offset f k)  (lambda (x) (+ k (f x))))

(plot-file
  (list
    (function sin -3 3 #:color "red") 
    (function (f_escala  sin 2)   -9 9 #:color "green")
    (function (f_compExp sin 2)   -9 9 #:color "blue")
    (function (f_shift   sin 1)   -9 9 #:color "orange")
    (function (f_sum     sin l)   -9 9 #:color "purple")
    (function (f_offset  sin 3)   -9 9 #:color "black")
  )
  "plots.png")
