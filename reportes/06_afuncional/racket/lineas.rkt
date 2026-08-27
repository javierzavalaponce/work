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

