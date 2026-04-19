#lang web-server/insta

(define (start request)
  (response/xexpr
   '(html
     (head (title "Mi sitio"))
     (body (h1 "¡Hola desde DrRacket!")
           (p "Este es un servidor web funcionando")))))