```{=latex}
\clearpage
```
	
# Resumen

Este proyecto de investigación propone el desarrollo de una arquitectura de control distribuida y tolerante a fallos para sistemas ciber-físicos, fundamentada en Redes Neuronales de Ecuaciones Diferenciales Ordinarias (Neural ODEs). La solución aborda dos desafíos críticos en sistemas de control modernos: (1) la necesidad de modelos dinámicos precisos y computacionalmente eficientes que puedan ejecutarse en plataformas embebidas con recursos limitados, y (2) la exigencia de alta disponibilidad y tolerancia a fallos en aplicaciones de misión crítica (como vehículos aéreos, autónomos o sistemas de potencia).

La investigación se centrará en el diseño de una red de Controladores de Tiempo Real (RT-Controllers), donde cada nodo embebido ejecuta un modelo de Neural ODE entrenado para predecir y controlar la dinámica del sistema. La arquitectura contempla un orquestador central (Hypervisor de Tiempo Real) que gestiona la sincronización, la distribución de señales de entrada/salida y la lógica de conmutación por fallos. La naturaleza continua y diferenciable de los Neural ODEs permitirá una predicción adaptativa con coste computacional y de memoria optimizados, facilitando su despliegue en FPGAs o microcontroladores de alto rendimiento. El sistema operará de forma determinista, con cada controlador manteniendo condiciones iniciales sincronizadas en cada tick del sistema, garantizando un "respaldo en caliente" listo para tomar el control ante cualquier anomalía, aumentando así la robustez y fiabilidad del sistema completo.

\newpage

# Abstract

adsf


Estado del Arte y Fundamentos para tu Propuesta

Aquí tienes un resumen de los avances más relevantes que sustentan cada parte de tu idea, incluyendo referencias a artículos científicos que puedes citar en tu propuesta.
1. Neural ODEs para Sistemas Embebidos (El "Motor Predictivo")

La base teórica de tu propuesta está muy bien soportada. Los Neural ODEs ofrecen una manera de modelar sistemas dinámicos en tiempo continuo con una eficiencia que los hace atractivos para el mundo de los sistemas embebidos.

    Eficiencia en Memoria y Cómputo Adaptativo: A diferencia de redes tradicionales, los Neural ODEs no almacenan todos los estados intermedios durante el entrenamiento, lo que reduce drásticamente el consumo de memoria 

. Además, los solucionadores numéricos pueden ajustar el tamaño del paso de integración de forma adaptativa, lo que se traduce en un coste computacional variable y, potencialmente, en una ejecución más rápida en hardware limitado

.

Physics-Enhanced Neural ODEs (PeNODEs): Esta es una variante clave para tu propuesta. En lugar de aprender la dinámica completa desde cero, un PeNODE combina las ecuaciones físicas conocidas del sistema (por ejemplo, las leyes de la mecánica o la electrónica de potencia) con una red neuronal que aprende solo las dinámicas no modeladas o las perturbaciones. Esto da como resultado un modelo mucho más pequeño, interpretable y fácil de entrenar
. Por ejemplo, un trabajo reciente demostró que este enfoque reduce el número de neuronas en un 75% para modelar sistemas de electrónica de potencia, un paso crítico para su despliegue en FPGA

    .

    Para tu propuesta: Puedes argumentar que usarás PeNODEs para crear el modelo interno de cada controlador, aprovechando el conocimiento previo de la física del sistema (por ejemplo, la dinámica de un vehículo o un motor) para reducir la carga computacional en las placas embebidas.

2. Tolerancia a Fallos y Sistemas Redundantes (El "Backup en Caliente")

Tu intuición sobre la redundancia para la tolerancia a fallos es un área de investigación muy activa y se alinea con los conceptos de Fault-Tolerant Control (FTC).

    Control Tolerante a Fallos Pasivo: El artículo "Systematic Synthesis of Passive Fault-Tolerant Augmented Neural Lyapunov Control Laws for Nonlinear Systems" 

describe un método que entrena una red neuronal para que sirva como una ley de control única que garantiza la estabilidad tanto en escenarios nominales como con fallos en los actuadores. Esto se alinea con tu idea de un controlador "preparado" para fallar.

Neurodinámica y Robustez: Investigaciones recientes proponen esquemas de control tolerante a fallos para robots redundantes que utilizan neurodinámica (como las redes neuronales recurrentes) para estimar la cinemática del sistema sin necesidad de un modelo exacto

    . Este enfoque "sin modelo" es especialmente robusto frente a ruido y fallos en los sensores, similar a lo que buscas con tu arquitectura distribuida.

    Para tu propuesta: Puedes enmarcar tu arquitectura como un sistema de control tolerante a fallos pasivo y distribuido. Cada placa embebida ejecuta un PeNODE que actúa como un controlador. El hypervisor, en lugar de ser un simple orquestador, podría implementar una lógica de "votación" o de "conmutación por fallos" basada en la consistencia de las predicciones de cada controlador. Si un controlador empieza a desviarse (fallo), el sistema cambia inmediatamente a otro.

3. Despliegue en Tiempo Real y Plataformas Embebidas (El "Orquestador/Hypervisor")

Este es el punto donde tu idea es más novedosa y donde la investigación está comenzando a converger.

    Herramientas para el Despliegue: El artículo "Hybrid Simulation Models for Embedded Applications: A Modelica and eFMI approach" 

explora específicamente cómo transformar modelos híbridos (como los PeNODEs) en código C listo para su ejecución en sistemas embebidos, utilizando estándares como eFMI y ONNX. Esto es fundamental para llevar tu idea a la práctica.

Deployments en FPGA: El trabajo sobre PENODE no solo presenta el modelo, sino también un flujo de trabajo completo "cloud-to-edge" para desplegarlo eficientemente en FPGAs

    , cumpliendo con los estrictos requisitos de tiempo real de los sistemas de electrónica de potencia.

    Para tu propuesta: Tu principal contribución de investigación podría ser la integración y orquestación de estos elementos. Mientras que los trabajos anteriores se centran en desplegar un único modelo de Neural ODE en un dispositivo embebido, tu propuesta va un paso más allá al plantear una red de estos dispositivos trabajando en conjunto. Puedes proponer investigar:

        El protocolo de sincronización entre los controladores y el hypervisor.

        Las estrategias de tolerancia a fallos a nivel de sistema (no solo de modelo).

        La escalabilidad de la arquitectura y el impacto en el rendimiento determinista del sistema.

Resumen de Artículos para tu Propuesta
Título del Artículo / Concepto	Aportación a tu Propuesta	Referencia
Physics-Embedded Neural ODEs (PENODE) para Edge Digital Twins	Muestra la viabilidad de desplegar Neural ODEs eficientes en FPGAs para sistemas de potencia en tiempo real. Respalda la idea del "motor predictivo" embebido.	
Hybrid Simulation Models for Embedded Applications: Modelica & eFMI	Proporciona un flujo de trabajo concreto para convertir modelos híbridos (PeNODEs) en código embebido (C), validando la parte práctica de tu propuesta.	
Síntesis Sistemática de Leyes de Control Tolerante a Fallos con Lyapunov Neural	Presenta una metodología para entrenar controladores que son inherentemente robustos a fallos, alineándose con tu idea de "backup en caliente".	
Guía de Neural ODEs para Ingeniería Digital	Es una excelente referencia para introducir y explicar los fundamentos de los Neural ODEs en tu propuesta.	

Espero que esta información te sea de gran utilidad para formalizar tu idea y presentar una propuesta sólida. ¡Mucho éxito con tu investigación!
