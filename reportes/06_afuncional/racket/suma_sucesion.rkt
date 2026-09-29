#lang racket
;; Suma de los primeros 5 términos de 1/n:

(define (sum term ini sig fin) ;'term' y 'sig' son  proc.
  (if (> ini fin) 
      0 
      (+ (term ini)        ;se aplica 'term' a un argumento
         (sum term (sig ini) sig fin))))

(sum (lambda (n) (/ 1.0 n)) 1 (lambda (n) (+ n 1)) 5)