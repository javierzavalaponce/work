```{=latex}
\clearpage
```
# Análisis funcional

## Topología

## Topología de espacios normados

## Convergencia y Completitud


## Banach

Un Espacio de Banach es un espacio vectorial donde puedes sumar objetos, medir su tamaño, y lo más importante: no tiene agujeros. Si haces una serie de aproximaciones cada vez más precisas, el punto final al que llegas siempre está dentro de ese estacionamiento.

Los 3 ingredientes obligatorios:

1. Ser un espacio vectorial: Puedes coger dos elementos cualesquiera (sean vectores, matrices o funciones) y sumarlos, o multiplicarlos por un número (escalar). El resultado sigue viviendo dentro.

2. Tener una *Norma*: Tienes una regla que le asigna un "tamaño" (o longitud) a cada objeto. Sirve para medir distancias entre ellos.

* Ser *Completo* (la clave del asunto): Si tienes una sucesión de objetos que se van acercando entre sí sin parar (lo que se llama sucesión de Cauchy), el objeto límite al que tienden tiene que estar dentro del espacio. No se permite que "se escape" a un agujero.

La analogía:

Imagina que trabajas con números racionales (fracciones). Puedes tener la sucesión 1, 1.4, 1.41, 1.414, 1.4142... (aproximando la raíz de 2). Esos números se acercan cada vez más entre sí, pero el límite ($\sqrt 2$) no es un número racional, ¡se cae por un agujero! Por eso, los racionales no son un espacio de Banach.
En cambio, los números reales sí lo son: cualquier sucesión que se aproxime tiene su límite dentro de los reales. Son un espacio sin fugas, un bloque sólido de mármol.

La gran pregunta: ¿Y esto con qué se come?
La belleza es que esto no aplica solo a números, aplica a funciones.
Puedes tener un espacio de Banach donde cada "punto" dentro de él es una función (como las ondas de la guitarra que vimos antes).

 Si mides el tamaño de la función por su altura máxima (norma del supremo), tienes un Banach.

 Si mides el tamaño por la energía total (la integral de la función al cuadrado), tienes otro Banach distinto, aunque los objetos dentro sean los mismos.

¿Por qué los usa todo el mundo (físicos e ingenieros)?
Porque los espacios de Banach son el "piso firme" para hacer cálculo y resolver ecuaciones diferenciales en dimensiones infinitas.


## Hilbert

Si tenemos producto interno y el espacio es completo, se llama Hilbert
. Aquí caen Parseval, las series de Fourier y las bases ortonormales. 
Sección 1.5 de [@hstark]


## Operadores


funciones que van de un espacio a otro (operadores). Defines continuidad (que en espacios normados es lo mismo que estar acotado) y el espacio dual (funcionales lineales). 
Capítulo 2 de [@kreyszig] 

