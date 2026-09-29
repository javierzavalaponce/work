#lang racket

(define (integral-cuadrados tiempo funcion)
  (if (or (null? (cdr tiempo))
          (null? (cdr funcion)))
      0
      (+ (* (/ (+ (sqr (car funcion))
                   (sqr (cadr funcion)))
                2.0)
            (- (cadr tiempo)
               (car tiempo)))
         (integral-cuadrados (cdr tiempo)
                             (cdr funcion)))))

(define (norma-l2 tiempo funcion)
  (sqrt
   (integral-cuadrados tiempo funcion)))


(define tiempo
  '(0.0 0.1 0.25 0.5 0.8 1.0))

(define funcion
  '(0.0 0.1 0.25 0.5 0.8 1.0))

(norma-l2 tiempo funcion)