## Capitulo 2 . Modelos de sistemas

* Para analizar los sistemas de control se necesitan *modelos matemáticos*
de los elmentos que componen dichos sistemas.

* A partir de una variedad de bloques funcionales es posible formar sistemas como
un lego

* Las relaciones entrada-salida de esos bloques generan a su vez una relacion global
entrada-salida combinando así las relaciones causa-efecto de cada bloque.

### Linealidad

Un sistema, operador o función es lineal si cumple:

1. Aditividad (superposición)
$f(x_1 + x_2) = f(x_1) + f(x_2)$

2. Homogeneidad (escalamiento)
$f(\alpha x) = \alpha f(x)$

Es decir:

$f(\alpha x_1 + \beta x_2) = \alpha f(x_1) \beta f(x_2)$

* Un sistema lineal es *predecible y proporcional*

* Permite usar herramientas como 
    * la transformada de Laplace
    * lugar de las raíces
    * análisis en frecuencia


\newpage
