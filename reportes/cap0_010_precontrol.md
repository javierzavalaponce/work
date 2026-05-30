```{=latex}
\clearpage
```

# Readme

## Contexto / Introducción

En contextos administrativos y comerciales, antiguamente era necesario llevar registros escritos en pergaminos o rollos para anotar transacciones, inventarios, impuestos, deudas, etc. Para reducir errores o fraudes se empleaban copias de verificación 
(ver palabras: en francés *contre‑rôle*, en español aparece como *contrarollo*). Si el registro "oficial" coincidía con otra copia independiente, se consideraba que existía control.

El sentido de “control” como dominio o mando fue apareciendo gradualmente; evolucionó hacia la noción de *tener poder para dirigir o regular* porque quien verifica (no siempre un órgano independiente) acaba disponiendo de facultades para invalidar cuentas, ordenar cambios o imponer reglas inclusive.

Durante la Revolución Industrial, el término adquirió el sentido moderno de regular máquinas y garantizar su estabilidad. Actualmente, en ingeniería, *control* significa:

* corrección continua y regulación,
* compensación del error, y
* mantenimiento de la estabilidad.


La palabra *sistema*, de origen griego ($\sigma\acute{u}\sigma\tau\eta\mu\alpha$), remite a la idea de un conjunto ordenado y estructurado.

Un **sistema de control** es un conjunto organizado de elementos (partes físicas, reglas, personas o algoritmos) diseñado para supervisar, regular y corregir el comportamiento de otro sistema a fin de mantenerlo estable o dentro de ciertos límites.

### Sistemas estáticos y dinámicos

Cuando pedaleamos una bicicleta, el giro de la rueda trasera depende directamente de la relación entre el número de dientes de las estrellas. Si la estrella delantera es grande y la trasera pequeña, una sola vuelta de los pedales produce varias vueltas de la rueda. Si la relación se modifica, tambien cambia el avance o *desarrollo*. Este comportamiento, asi como el divisor de voltaje constituyen ejemplos de sistemas estáticos: la salida depende únicamente del valor actual de la entrada. En una relación algebreaica no existe acumulación, memoria ni evolución temporal propia dentro del sistema.


En contraste, muchos sistemas reales no responden de forma instantánea, sino que evolucionan gradualmente en el tiempo debido a fenómenos como inercia, almacenamiento de energía o retardos físicos. Estos son conocidos como sistemas dinámicos y representan el principal objeto de estudio del control automático,
por ejemplo:  un horno no se calienta instantaneamente al encenderse. Para describir y predecir el comportamiento de un sistema dinámico es necesario representar cómo el sistema evoluciona con el tiempo. 

Las ecuaciones diferenciales son la herramienta matemática natural para modelar estos fenómenos, ya que permiten expresar relaciones entre una variable y sus variaciones temporales. Sistemas como motores, hornos o sistemas mecánicos suelen describirse mediante ecuaciones diferenciales que representan su dinámica y permiten analizar estabilidad, velocidad de respuesta y comportamiento ante distintas entradas.
