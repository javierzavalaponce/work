;ejercios.rkt
;f_escala:  Multiplica función por escalar
;f_expande: Comprime/expande funcion en el tiempo
;f_sum:     Suma de funciones
;f_shift:   Introduce un retardo/adelanto
;f_offset:  Introduce un offset positivo/negativo

#lang racket
(require plot)
(define (line m b)
    (lambda (x) (+ (* m x) b)))

(define l (line 1 1))

(define (f_escala  f k) (lambda (x) (* k (f x))))
(define (f_expande f k) (lambda (x) (f (* k x))))
(define (f_shift f k)   (lambda (x) (f (+ k x))))
(define (f_sum f g)     (lambda (x) (+ (f x) (g x))))
(define (f_offset f k)  (lambda (x) (+ k (f x))))

(plot-file
  (list
    (function sin -3 3)
    (function (f_escala  sin 2) -2 2)
    (function (f_expande sin 2) -2 2)
    (function (f_shift   sin 1) -2 2)
    (function (f_sum     sin l) -2 2)
    (function (f_offset  sin 0.3) -2 2)
  )
  "plots.png")
