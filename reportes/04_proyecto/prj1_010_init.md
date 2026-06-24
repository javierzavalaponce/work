```{=latex}
\clearpage
```
	
# Resumen

Este proyecto de investigación propone el desarrollo de una arquitectura de control distribuida, conmutada y tolerante a fallos para Sistemas Ciber-Físicos (CPS, por sus siglas en inglés). La solución aborda dos desafíos críticos en sistemas de control modernos:

1. La necesidad de estrategias de control robustas que puedan ejecutarse en plataformas embebidas con recursos limitados, garantizando tiempos de respuesta deterministas, y 

2. La exigencia de alta disponibilidad y tolerancia a fallos en aplicaciones de misión crítica (como vehículos aéreos no tripulados, sistemas autónomos o redes de potencia).

La investigación se centrará en el diseño de una red de Controladores de Tiempo Real (RT-Controllers) embebidos, donde cada nodo ejecuta una ley de control diferente (por ejemplo, PID, Control por Modos Deslizantes
-SMC-, Control Lineal Cuadrático -LQR-, permitiendo así un abanico de estrategias que el sistema puede seleccionar según las condiciones operativas. La arquitectura contempla un orquestador central (o supervisor) que gestiona:

* La sincronización y distribución de señales de entrada/salida entre los *nodos*. (Un nodo es una plataforma embebida (microcontrolador, FPGA o SoC) que ejecuta, de forma autónoma y sincronizada, una instancia de un controlador (PID, SMC, LQR, etc.) y se comunica con el orquestador y con otros nodos a través de un bus de tiempo real (CAN, EtherCAT, SPI, etc.).)

* La lógica de conmutación (Switching Logic), que decide en cada instante cuál de los controladores disponibles debe tomar el control de la planta, basándose en el estado del sistema, la presencia de fallos y las restricciones de tiempo real.

El sistema operará de forma determinista, con cada controlador manteniendo sus estados internos sincronizados en cada ciclo de cómputo. Esto garantiza que todos los controladores estén siempre listos para tomar el control ante cualquier anomalía (fallo en un actuador, saturación, degradación del sensor o pérdida de comunicación entre nodos), aumentando así la robustez, fiabilidad y disponibilidad del sistema completo.


La principal contribución de este proyecto radica en el diseño de una arquitectura de control que integra un esquema de conmutación basado en fallos con un enfoque distribuido y descentralizado, operando bajo estrictas restricciones de tiempo real. A diferencia de los enfoques clásicos (que suelen ser centralizados o con un único controlador de respaldo), este sistema permite una redundancia activa y diversificada, donde cada controlador aporta una estrategia diferente (robustez, optimalidad, rapidez) y el orquestador elige la más adecuada según el contexto operativo. Esto no solo mejora la tolerancia a fallos, sino que también optimiza el rendimiento del sistema en diferentes regímenes de operación.

\newpage

