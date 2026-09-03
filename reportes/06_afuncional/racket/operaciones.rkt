;operaciones.rkt
;f_escala:  Multiplica función por escalar
;f_compExp: Comprime/expande funcion en el tiempo
;f_sum:     Suma de funciones
;f_shift:   Introduce un retardo/adelanto
;f_offset:  Introduce un offset positivo/negativo

#lang racket
(define (gen_line m b)
    (lambda (x) (+ (* m x) b)))

(define l (gen_line 1 1))

(define (f_escala  f k) (lambda (x) (* k (f x))))
(define (f_compExp f k) (lambda (x) (f (* k x))))
(define (f_shift f k)   (lambda (x) (f (+ k x))))
(define (f_sum f g)     (lambda (x) (+ (f x) (g x))))
(define (f_offset f k)  (lambda (x) (+ k (f x))))

