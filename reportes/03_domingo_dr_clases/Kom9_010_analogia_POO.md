
### Analogía con la programación orientada a objetos:


La clase define la estructura de un estado.
Un objeto es una instancia concreta (por ejemplo, $[3,0.1]$ o $[1,1]$
El espacio de estados es el conjunto de todas las instancias posibles de esa clase.

```bash
#include <iostream>
#include <vector>

class Estado
{
public:
    std::vector<double> x;
};

int main()
{
    // Primer estado
    Estado e1;
    e1.x.push_back(3.0);
    e1.x.push_back(0.1);

    // Segundo estado
    Estado e2;
    e2.x.push_back(1.0);
    e2.x.push_back(1.0);

    // Colección de estados
    std::vector<Estado> espacioEstados;

    espacioEstados.push_back(e1);
    espacioEstados.push_back(e2);

    // Mostrar los estados almacenados
    std::cout << "Estados almacenados:\n\n";

    for (const Estado& estado : espacioEstados)
    {
        std::cout << "[ ";

        for (double valor : estado.x)
            std::cout << valor << " ";

        std::cout << "]\n";
    }

    return 0;
}
```




Un std::vector<double> normalmente contiene sólo tres cosas:

data -----> puntero al heap

size ------ número de elementos

capacity -- memoria reservada


Una analogía

Imagina que std::vector es el administrador de un almacén.

El stack contiene únicamente la oficina del administrador (el objeto vector).
El heap es la bodega donde realmente se guardan las cajas (los elementos double).

Cada push_back() no pone otra caja en la oficina; le pide al administrador que consiga más espacio en la bodega si hace falta. Esa separación entre el pequeño objeto vector y el almacenamiento dinámico es una de las ideas fundamentales de std::vector.




aso 1: El problema de las etiquetas (El "Caos" inicial)

Imagina que quieres que una red neuronal entienda tres palabras: "Rey", "Reina" y "Manzana".

Si se las das a un ordenador, este solo entiende números. Lo más simple es asignarles un ID: Rey = 1, Reina = 2, Manzana = 3.
Problema grave: El ordenador pensará que 1 + 2 = 3, es decir, que Rey + Reina = Manzana. O peor, que la distancia entre Rey (1) y Reina (2) es la misma que entre Reina (2) y Manzana (3). Eso no tiene ningún sentido semántico.

Para solucionarlo, usamos la codificación one-hot (vector de un solo "1").
Creamos un espacio de 3 dimensiones (una por cada palabra):

    Rey = (1,0,0)(1,0,0)

    Reina = (0,1,0)(0,1,0)

    Manzana = (0,0,1)(0,0,1)

¿Qué ocurre aquí en términos de "cambio de base"?
Estos tres vectores son la base canónica (los ejes e1,e2,e3e1​,e2​,e3​). Son perfectamente perpendiculares (ortogonales).
Si calculamos el producto punto (la similitud) entre "Rey" y "Reina": (1,0,0)⋅(0,1,0)=0(1,0,0)⋅(0,1,0)=0. La red piensa que estas palabras no tienen absolutamente nada en común. La base es horrible porque no refleja la realidad: Rey y Reina son muy parecidos (ambos son realeza humana), y Manzana es totalmente distinta.

Conclusión del Paso 1: Necesitamos cambiar estos ejes. Necesitamos una nueva base donde "Rey" y "Reina" tengan coordenadas cercanas, y "Manzana" quede lejos.
Paso 2: La matriz de embedding WW (El "Cambio de Base" en acción)

Aquí es donde ocurre el cambio de base. La red neuronal crea una matriz llamada WW (la capa de embedding).

Vamos a hacerlo pequeño: queremos pasar de nuestro espacio de 3 dimensiones (one-hot) a un nuevo espacio de 2 dimensiones (porque es más fácil de visualizar).
La matriz WW tiene tamaño 2×32×3. Sus columnas serán los nuevos vectores base, pero escritos en coordenadas del sistema antiguo. Supongamos que la red, después de entrenar, aprende estos valores:
W=[0.90.8−0.10.10.20.9]
W=[0.90.1​0.80.2​−0.10.9​]

Observa con atención:

    La columna 1 ([0.9,0.1]T[0.9,0.1]T) es el nuevo vector donde vivirá "Rey".

    La columna 2 ([0.8,0.2]T[0.8,0.2]T) es el nuevo vector donde vivirá "Reina".

    La columna 3 ([−0.1,0.9]T[−0.1,0.9]T) es el nuevo vector donde vivirá "Manzana".

Para obtener el embedding de "Reina", matemáticamente hacemos:
Embedding(Reina)=W⋅(0,1,0)T=columna 2=(0.8,0.2)
Embedding(Reina)=W⋅(0,1,0)T=columna 2=(0.8,0.2)

¿Qué acaba de pasar aquí?
Hemos girado y estirado los ejes del espacio. En el espacio antiguo (one-hot), Rey y Reina estaban a 90 grados. En el nuevo espacio, sus coordenadas son (0.9,0.1)(0.9,0.1) y (0.8,0.2)(0.8,0.2).
Si calculamos la distancia (ej. Euclídea) entre ellos: (0.9−0.8)2+(0.1−0.2)2=0.01+0.01=0.14(0.9−0.8)2+(0.1−0.2)2
​=0.01+0.01
​=0.14 (muy cercanos).
La distancia entre Reina (0.8,0.2)(0.8,0.2) y Manzana (−0.1,0.9)(−0.1,0.9) es mucho mayor: 0.92+(−0.7)2≈1.140.92+(−0.7)2

​≈1.14.
Hemos logrado que la geometría (las coordenadas) refleje la semántica (el significado). Eso es cambio de base.
Paso 3: ¿Qué representan los ejes de la NUEVA base?

Aquí viene la parte más sutil y profunda. En el nuevo espacio de 2D, tenemos dos ejes: el Eje X (horizontal) y el Eje Y (vertical).
¿Qué miden estos ejes?

La red neuronal no lo sabe, pero el gradiente descendente (el entrenamiento) los convierte en ejes de factores latentes (factores ocultos). En nuestro pequeño ejemplo, mira las coordenadas:

    Rey = (0.9, 0.1)

    Reina = (0.8, 0.2)

    Manzana = (-0.1, 0.9)

Si te fijas en el Eje Y (la segunda coordenada):

    "Manzana" tiene 0.9 (muy alto).

    "Rey" y "Reina" tienen 0.1 y 0.2 (muy bajo).

El Eje Y se ha convertido en el eje de "Realeza vs. Comestible".
Si el Eje Y mide "ser vivo humano", Rey y Reina puntúan bajo (0.1). Si mide "ser una fruta", Manzana puntúa alto (0.9).
El Eje X mide otra cosa, probablemente "Género" o "Rango", donde Rey (0.9) y Reina (0.8) son casi iguales.

Conclusión clave: Cambiar la base no es solo mover números. Es descubrir los ejes naturales que subyacen a tus datos. La red encuentra una base matemática donde las palabras que se usan en contextos similares quedan alineadas en los mismos ejes.
Paso 4: La magia de las analogías (La prueba del álgebra)

Ahora viene la parte que siempre sorprende y que valida que esto es un cambio de base puro: las operaciones vectoriales.

En nuestro nuevo espacio, calculemos:
Vector(Rey)−Vector(Hombre)+Vector(Mujer)=Vector(Reina)
Vector(Rey)−Vector(Hombre)+Vector(Mujer)=Vector(Reina)

¿Por qué ocurre esto en el mundo real (ej. Word2vec)?
Porque el cambio de base ha alineado uno de los ejes específicamente con el Género.
Imagina que el Eje X mide "Realeza" y el Eje Y mide "Género" (de -1 a 1, donde -1 es femenino y +1 es masculino).

    Rey = (Realeza=9, Género=1)

    Hombre = (Humanidad=5, Género=1)

    Mujer = (Humanidad=5, Género=-1)

Haz la operación:
(9,1)−(5,1)+(5,−1)=(9−5+5,1−1−1)=(9,−1)(9,1)−(5,1)+(5,−1)=(9−5+5,1−1−1)=(9,−1).
El resultado es un vector con máxima realeza (9) y género femenino (-1), que es exactamente "Reina".

¿Qué papel juega el cambio de base aquí?
Sin el cambio de base (en el espacio one-hot), esta operación daba un vector basura lleno de ceros y un 1. En el nuevo espacio, la base está tan bien elegida que los ejes están alineados con las dimensiones del significado. La resta cancela el eje "Humanidad" y la suma mueve el eje "Realeza".
Paso 5: La gran diferencia entre Control y Embeddings (Atención aquí)

En teoría de control, el cambio de base (PP) lo elegimos nosotros para que la dinámica (la matriz AA) sea diagonal. Nuestro objetivo es matemático: resolver ecuaciones diferenciales más fácilmente.

En embeddings, el cambio de base (WW) lo aprende la red mirando los datos. El objetivo no es que la dinámica sea fácil, sino que la distribución estadística de los datos sea fácil de modelar. La red busca aquella base (aquellos ejes) donde las palabras que aparecen juntas en textos tengan productos punto altos.

Comparativa directa:
Aspecto Control (Matriz PP) Embeddings (Matriz WW)
¿Quién la elige?    El ingeniero (matemáticamente). El algoritmo de entrenamiento (por gradiente).
Criterio de selección   Que AA sea diagonal o canónica. Que las palabras similares queden cercanas (máxima verosimilitud).
Naturaleza  Fija después de diseñada.   Se ajusta durante el entrenamiento.
Función principal   Desacoplar modos dinámicos. Desacoplar factores semánticos (género, tiempo, categoría).
Resultado   Facilita el cálculo de la respuesta.    Facilita la predicción de la siguiente palabra.
Paso 6: La no-linealidad (La "deformación" posterior)

Un detalle crucial: La capa de embedding es puramente lineal (no tiene función de activación). Es un cambio de base estricto, igualito al de control.

¿Dónde está la no-linealidad? Cuando ese embedding (ese punto en el nuevo espacio) pasa a la siguiente capa oculta de la red y se le aplica una ReLU. Esa ReLU deforma el espacio; rompe la estructura de suma y resta.

Por eso las analogías vectoriales solo funcionan perfectamente en el espacio de embeddings crudo, antes de que las no-linealidades lo destruyan. Es el único lugar de la red donde el espacio sigue siendo un auténtico espacio vectorial lineal, como el que estudiamos en control.
Verificación de tu comprensión (El ejercicio lento)

Imagina que entrenamos un embedding para países y capitales. El espacio de estados aprende dos ejes: Eje X = Continente y Eje Y = Capitalidad.

    "España" está en (Europa, No-Capital) = (1, 0)

    "Francia" está en (Europa, No-Capital) = (1, 0)

    "Madrid" está en (Europa, Capital) = (1, 1)

    "París" está en (Europa, Capital) = (1, 1)

Pregunta para ti: Si ahora cambio la base de este espacio (multiplico todos los vectores por una matriz de rotación de 45°), los números de "España" y "Madrid" cambiarán, pero...

    ¿Seguirá "Madrid" estando tan cerca de "París" como antes?

    ¿Seguirá cumpliéndose que Espan~a−NoCapital+Capital≈MadridEspan~a−NoCapital+Capital≈Madrid?

Respuesta esperada:
Sí y sí. Porque un cambio de base (una rotación o escalado) es una transformación lineal invertible. Esta transformación preserva las distancias relativas, los ángulos y, lo más importante, las relaciones lineales (las sumas y restas vectoriales).
Si eras capaz de hacer la analogía en una base, podrás hacerla en cualquier otra base. La semántica es invariante al sistema de coordenadas, exactamente igual que la estabilidad de un sistema de control es invariante al sistema de coordenadas.

¿Lo ves? El embedding es simplemente encontrar "el mejor ángulo" para mirar tus datos, de modo que todas las regularidades del lenguaje salten a la vista como simples líneas rectas en el espacio.


