
#lang racket
;; ejemplo de calculo de la integral (integral sin 0 3.14159 0.1)
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
  (sqrt
   (integral
    (lambda (x) (sqr (f x)))
    a
    b
    dx)))


(norm sin 0 pi 0.001)