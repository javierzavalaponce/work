#lang racket

(define (line m b)
  (lambda (x)
    (+ (* m x) b)))

(define f1 (line 2 3))
(define g (line 5 1))

(displayln (f 2))
(displayln (g 1))


(define (sum_func f g)
  (lambda (x)
    (+ (f x) (g x))))

(define h (sum_func f g))
(displayln (h 1))


(define (offset alpha f)
  (lambda (x)
    (* alpha (f x))))

(define o (offset 10 f1))
(displayln (o 1))