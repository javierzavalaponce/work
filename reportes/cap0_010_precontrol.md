```{=latex}
\clearpage
```

# Carácter y objetivos de este material

El presente documento constituye un material de trabajo. Reúne notas de clase, resúmenes de repaso, reflexiones, ideas y apuntes elaborados durante el proceso de  consolidación de conocimientos en el área de control automático y sistemas dinámicos.

Debido a su naturaleza formativa y evolutiva, el contenido puede contener imprecisiones, omisiones o errores conceptuales propios de un proceso de reaprendizaje. En este sentido, cualquier observación, corrección o comentario será ampliamente bienvenido y apreciado.

Este trabajo se desarrolla como parte de mi proceso doctoral, particularmente como una etapa de fortalecimiento y solidificación de fundamentos teóricos antes de abordar de manera directa los temas específicos de investigación.

El proyecto doctoral en el cual se inscribe este proceso lleva por título:

*Implementación de controladores generados por inteligencia artificial en sistemas embebidos.*


```{=latex}
\clearpage
```


## Nota introductoria

En contextos administrativos y comerciales, antiguamente era necesario llevar registros escritos en pergaminos o rollos para anotar transacciones, inventarios, impuestos, deudas, etc. Para reducir errores o fraudes se empleaban copias de verificación 
(ver palabras: en francés *contre‑rôle*, en español aparece como *contrarollo*). Si el registro "oficial" coincidía con otra copia independiente, se consideraba que existía control.

El sentido de “control” como supervisión o regulación apareció de manera gradual ya que quien realiza la verificación de un sistema suele contar también con la capacidad de realizar ajustes o establecer criterios de funcionamiento.

Durante la Revolución Industrial, el término adquirió el sentido moderno de regular máquinas y garantizar su estabilidad. Actualmente, en ingeniería, *control* significa:

* corrección continua y regulación,
* compensación del error, y
* mantenimiento de la estabilidad.


La palabra *sistema*, de origen griego ($\sigma\acute{u}\sigma\tau\eta\mu\alpha$), remite a la idea de un conjunto ordenado y estructurado.

Un **sistema de control** es un conjunto organizado de elementos (partes físicas, reglas, personas o algoritmos) diseñado para supervisar, regular y corregir el comportamiento de otro sistema a fin de mantenerlo estable o dentro de ciertos límites.

### Sistemas estáticos y dinámicos

Cuando pedaleamos una bicicleta, el giro de la rueda trasera depende directamente de la relación entre el número de dientes de las estrellas. Si la estrella delantera es grande y la trasera pequeña, una sola vuelta de los pedales produce varias vueltas de la rueda. Al modificar esta relación de transmisión, cambia instantáneamente el avance o *desarrollo* de la bicicleta. Este comportamiento, al igual que el divisor de voltaje, constituye un ejemplo de sistema estático: la salida depende únicamente del valor actual de la entrada. En una relación algebraica de este tipo no existe acumulación, memoria ni evolución temporal propia dentro del sistema.


En contraste, muchos sistemas reales no responden de forma instantánea, sino que evolucionan gradualmente en el tiempo debido a fenómenos como inercia y el almacenamiento de energía. Estos son conocidos como sistemas dinámicos y representan el principal objeto de estudio del control automático,
por ejemplo:  un horno no se calienta instantaneamente al encenderse. Para describir y predecir el comportamiento de un sistema dinámico es necesario representar cómo el sistema evoluciona con el tiempo. 

El estudio de los sistemas dinámicos consiste en:

1. Definir un modelo que represente las relaciones causa-efecto y 
   las relaciones dinámicas entre las variables.
2. Aplicar método(s) para analizar el comportamiento del sistema
   cuando se aplica alguna señal externa bajo condiciones iniciales.
3. Aplicar método(s) para modificar el comportamiento del sistema
   a fin de obtener una respuesta satisfactoria.
















