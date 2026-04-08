# PORQUE es importante la programacion funcional


### Predecible
Sin efectos secundarios
Facil de razonar

### Paralelizable
no hay dependencias de estado
puedes ejecutar en paralelo

### Cercano a matematicas
ideal para simulacion
graficos, control , DSP



# TIEMPO EN PROGRAMACION FUNCIONAL

Esto es importante:

Caracteristicas
 
## No hay estado que evoluciona
   * el tiempo se modela como variable (*t*)
   * no como **proceso**

## Inmutabilidad
   * Los valores (de *las variables*) no cambian
     ejemplo:  x=x+1; //no funcional
     (funcional: todo en una sola expresion):
     ejemplo:
     linea 16 no "compila" en openscad
     mejor(dentro del paradigma funcional) linea 17:
```c
  15   │ theta = theta_max * sin(360 * $t) ; 
  16   │ theta = theta*exp(-2*$t)
  17   │ //theta = theta_max * sin(360*$t) * exp(-2*$t);
```    

ejemplo completo (openscad:

d = 450;
radio=25;

module pendulo(theta=0)
{
    rotate([theta,0,0])
        translate([0,0,-d]) {
            cylinder(h=d, r=3);
            sphere(radio);
        }
}

theta_max = 30;
theta = theta_max * sin(360*$t) * exp(-2*$t);
pendulo(theta);

## Declarativo (No imperativo)


no dices como hacer algo paso a paso
Dices:
   * que relacion existe entre las variables

# Como pensar funcionalmente:

haz A -> luego B
Piensas:

resultado = f(g(x))
(Composicion)
funcional es declarativo!
funcional no es imperativo!

ejemplo del pendulo:
calcular seno
luego multiplicar
luego aplicar decay
funcional 
angulo = Max * sen(1vuelta) * Amortigua_exp(-NEG*t)

* obsserva como nay "antes ni despues"
* el resultado es fijo. misma entrada corresponde a misma salida


