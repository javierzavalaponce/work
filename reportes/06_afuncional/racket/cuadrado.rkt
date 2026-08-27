#!/usr/bin/env racket
#lang racket

(define argumentos
  (current-command-line-arguments))

(if (= (vector-length argumentos) 0)
    (printf "Uso: cuadrado.rkt numero\n")
    (let ([x (string->number (vector-ref argumentos 0))])
      (printf "El cuadrado de ~a es ~a\n" x (* x x))))

