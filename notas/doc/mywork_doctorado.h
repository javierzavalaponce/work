sobre la revalidacion

sere.sep.gob.mx
55 36 01 75 99
#3
cedulas profesionales educatel
Sere_javez846!


“A pesar de los avances significativos en [área], aún persiste una pregunta fundamental que no ha sido suficientemente explorada…”

“Uno de los principales desafíos actuales en [campo de estudio] es…”

“La literatura reciente coincide en que [problema], sin embargo, existe un vacío importante en…”




Implementación de controladores generados por
inteligencia artificial en sistemas embebidos
Propuesta de proyecto doctoral
Aspirante:
Javier Zavala Ponce
Asesor: Dr. Domingo de Jesús Cortés Rodríguez
Enero de 2025

Contenido
1. Introducción
2. Generación de controladores por IA
2.1Implementación de Algoritmos IA-C en Sistemas Embebidos
3. Objetivos y Metodología1. 




Control de sistemas dinámicos:
Algunos avances:
Control predictivo basado en modelo.
Control de estructura variable.
Optimización aplicada al control.

Con Algoritmos de IA-C (Aplicados al control):
Sintonizar controladores ya conocidos.
Permite experimentación con:
Variaciones de una determinada estructura de control.
Estructuras de control aleatorias.



Complementos al enfoque frecuencial clásico
Enfoque de espacio de estado
Contribuciones de Kalman
Control predictivo basado en modelo
Control por modos deslizantes
Dificultades con
Sistemas variantes en el tiempo
Modelo conocido de forma aproximada
Cambios fuertes durante operación
Simulación intensiva
y
Controladores
automáticamente

generadosSistemas embebidos:
Sistema informático especializado
Una función dedicada dentro de un
sistema mecánico o electrónico
más grande.
Cómputo en tiempo real.
MicrocontroladorProceso:
Generacion de controlador por IA.2. Generación de controladores por IA
Algoritmos de inteligencia de enjambre.
Algoritmos de programación genética.
Sistemas de inferencia difusos.
Sistema de inferencia difuso usando redes adaptables: ANFISAlgoritmos de inteligencia de enjambre
Población de agentes que interactúan
localmente entre ellos y con su medio
ambiente.
Los agentes siguen reglas simples
estructura de control centralizado
sin
Las interacciones locales entre los agentes
conduce
a
la
emergencia
de
un
comportamiento global complejo.Algunos algoritmos de optimización de enjambre.
2010Bat-inspired AlgoritmBA
2010Firefly AlgorithmFA
2010Hunting Search AlgoritmHSA
2012Krill Herd AlgorithmKHA
2012Fruit fly Optimization AlgorithmFOA
2013Dolphing EcholocationDEA
2013Bird Mating OptimizerBMO
2014Grey Wolf OptimizationGWO
2016The Whale OptimizationWO
2020Binary Grey Wolf OptimizerBGWOAlgoritmos de programación genética
Población inicial de controladores.
Definir función fitness para evaluar solución
particular
Seleccionar a los individuos mas aptos para
reproducción.
Aplicar operadores de mutación y cruza para
nueva generación de controladores.
Repetir el proceso por un cierto número
determinado de generacionesSistemas de inferencia difusos
Ventajas:
Manejan
sistemas
dinámicos no lineales sin modelo
matemático exacto.
Usan conocimiento heurístico de
expertos para emular decisiones.
Sintonización: Heurística: Ajuste de
funciones de membresía. Iterativa y
toma tiempoSistemas de inferencia difusos
usando redes adaptables: ANFIS
Combina
redes
neuronales
artificiales con lógica difusa para
modelar relaciones no lineales
complejas de forma adaptable.
MATLAB Fuzzy Logic Toolbox.
ANFIS posee cinco capas neuronales
que implementan reglas difusas
Takagi-Sugeno.
Aprendizaje automatico basado en
datos reales del sistema.2.1 Implementación de Algoritmos IA-C en Sistemas
Embebidos
Los algoritmos de IA generan código automaticámente, usualmente no optimizado.
Para ser ejecutado por una computadora.
En resumen:
1. Generación de Algoritmo.
2. Simplificacion (P. Ej: Polinomios de Bernstein).
(cálculos de aproximación y análisis numérico ).
3. Traduccion por software a lenguage C.
4. Implementación en RTOS (Sistema Operativo de Tiempo Real).RTOS y determinismoProblemas
Limitaciones en: Memoria, tiempo de cómputo , precisión numerica.
Otros: Jitter y latencias + ruido en Conversiones A/D,
El programa se debe ejecutar en tiempo real. El código que define un
controlador tiene una estructura iterativa (determinismo):
1. Lee las entradas del controlador,
2. Procesa las entradas,
3. Calcula el control,
4. Actualiza las salidas del controlador,
5. Repite.3. Objetivo general y método.
Establecer un proceso de generación de controladores por IA desde su concepción
hasta la implementación en tiempo real en un sistema embebido.

Objetivos especificos
Modificar algoritmos de IA - C de tal manera que produzcan controladores
que estén más cerca de ser implementados en sistemas embebidos
Desarrollar software para simplificar controladores generados.
Traducir controladores expresados en lenguajes de alto nivel a lenguaje C
para que puedan ejecutarse sobre un sistema embebido con sistema
operativo de tiempo real.
Ejecutar un controlador generado automáticamente en un sistema
embebido con sistema operativo de tiempo real.
Evaluar de forma automática el desempeño de un sistema controlado
mediante un sistema embebido ejecutando en tiempo real un algoritmo
generado automáticamente.Actividades principales propuestas
Análisis del los algoritmos de IA desarrollados previamente.
Desarrollo de software para simplificar y traducir expresiones de control
arrojados por los algoritmos.
Desarrollo de software para traducir expresiones simplificadas a codigo
ejecutable en sistetas embebidos.
Implementar código en sistema embebido y evaluar el sistema controlado.Asignaturas por cursar:
Seminario departamental I.
Seminario departamental II.
Seminario departamental III.
Temas selectos de electrónica.
Temas selectos de investigación.
Análisis de sistemas discretos.Implementación de controladores generados por
inteligencia artificial en sistemas embebidos
Propuesta de proyecto doctoral
Aspirante:
Javier Zavala Ponce
Asesor: Dr. Domingo de Jesús Cortés Rodríguez
Enero de 2025Skip to content
Chat history
You said:
file.pdf
PDF
resume lo mas importante de este documento
ChatGPT said:

Aquí tienes un resumen con los puntos más importantes de tu documento “Implementación de controladores generados por inteligencia artificial en sistemas embebidos – Propuesta de proyecto doctoral”:
🎯 Propósito central de la tesis

Desarrollar un proceso automático completo para:

    Generar controladores mediante algoritmos de IA y llevarlos hasta su implementación en tiempo real en sistemas embebidos.

Actualmente, los controladores generados por IA solo se ejecutan en computadoras de propósito general, pero no están listos directamente para hardware embebido industrial, que exige:

    tiempo real

    bajo cómputo

    lenguaje C

    restricciones físicas (ADC/DAC, retardos, cuantización)

La tesis busca cerrar esa brecha.
🧠 Problema que se aborda
Limitaciones del control clásico

    Requiere modelos matemáticos simples/precisos.

    Difícil para sistemas:

        no lineales

        inciertos

        variantes en el tiempo

        de alto orden

Ventaja de la IA

La IA permite:

    Simular miles de controladores

    Ajustar parámetros automáticamente

    Generar estructuras nuevas

    Optimizar desempeño sin modelado exacto

Pero:

    El código resultante es complejo y no ejecutable directamente en sistemas embebidos.

🤖 Técnicas de IA consideradas

Se revisan y usan algoritmos desarrollados en el laboratorio:
1. Inteligencia de enjambre

Ej: PSO, ACO, GWO, etc.

    Agentes = soluciones

    Se mueven en el espacio de búsqueda

    Optimizan desempeño iterativamente

2. Programación genética

    Evoluciona expresiones matemáticas/estructuras de control

    Puede generar controladores completos automáticamente

3. Control difuso (FIS)

    Basado en reglas heurísticas

    No requiere modelo exacto

4. ANFIS

    FIS + redes neuronales

    Ajuste automático de parámetros

⚠️ Dificultades al pasar a sistemas embebidos

Problemas clave:

    Conversión A/D y D/A → retardos y cuantización

    Tiempo real estricto

    Poca potencia de cómputo

    Lenguaje limitado (C)

    Código IA → grande/no optimizado

👉 Se requiere transformación y simplificación automática del controlador antes de implementarlo.
🛠️ Propuesta técnica (Metodología)

Pipeline completo:

    Seleccionar sistema físico (ej. convertidor elevador)

    Obtener modelo aproximado

    Generar controlador con IA

    Simplificar expresiones matemáticas (aproximación funcional/polinomial)

    Traducir automáticamente a C

    Implementar en sistema embebido con RTOS

    Evaluar desempeño en lazo cerrado

    Iterar si falla

🎯 Objetivos
General

Crear el proceso completo IA → embebido en tiempo real.
Específicos

    Modificar algoritmos IA para producir controladores “embeddable”

    Simplificar controladores automáticamente

    Traducir a C

    Implementar en RTOS

    Evaluar desempeño automáticamente

🔬 Aportes esperados

La tesis aportará:

✅ Metodología sistemática
✅ Herramientas software automáticas
✅ Simplificación matemática
✅ Generador automático de código C
✅ Validación en hardware real

Impacto:

    Control industrial

    Electrónica de potencia

    Robótica

    Sistemas embebidos inteligentes

📅 Plan de trabajo (4 años aprox.)

    Revisión bibliográfica

    Análisis de algoritmos IA existentes

    Desarrollo de:

        simplificador

        traductor a C

        implementación embebida

    Validación experimental

    Redacción de tesis

🧩 Idea clave en una frase

    Automatizar desde la generación de un controlador por IA hasta su ejecución eficiente en hardware embebido en tiempo real.

Si quieres, también puedo ayudarte a:
✅ resumirlo en 1 página tipo “executive summary”
✅ convertirlo en diapositivas
✅ extraer objetivos/hipótesis
✅ preparar defensa oral
✅ o hacer mapa conceptual

Solo dime qué formato necesitas.
You said:
si
ChatGPT said:

Perfecto — te extraigo los objetivos, hipótesis y preguntas de investigación en formato claro y listo para usar en:

    protocolo doctoral

    marco metodológico

    presentación de defensa

    o sección “Planteamiento del problema”

🎯 Objetivos de la investigación
✅ Objetivo general

Diseñar e implementar un proceso automático integral que permita generar controladores mediante algoritmos de inteligencia artificial y desplegarlos eficientemente en sistemas embebidos con ejecución en tiempo real.
✅ Objetivos específicos
Algoritmos de control

    Analizar y adaptar algoritmos de IA (enjambre, programación genética, FIS, ANFIS) para la generación automática de controladores.

    Modificar dichos algoritmos para producir controladores más simples y compatibles con hardware embebido.

Procesamiento matemático

    Desarrollar métodos de simplificación y aproximación funcional para reducir la complejidad matemática de los controladores generados por IA.

    Evaluar técnicas de aproximación (polinomios, bases funcionales, limitación en frecuencia/amplitud).

Implementación software

    Crear un traductor automático de expresiones matemáticas a código C optimizado.

    Garantizar que el código generado cumpla restricciones de:

        tiempo real

        memoria

        cómputo

Implementación hardware

    Integrar el controlador en un sistema embebido con RTOS.

    Definir periodos de muestreo, E/S analógicas y arquitectura de ejecución.

Validación experimental

    Evaluar el desempeño en lazo cerrado:

        estabilidad

        robustez

        rapidez de respuesta

        consumo de recursos

    Comparar contra controladores clásicos y/o versiones no simplificadas.

🔬 Hipótesis de investigación

Te las estructuro en principal + secundarias, estilo tesis doctoral.
🧠 Hipótesis principal

    Es posible automatizar el proceso completo de generación, simplificación y despliegue de controladores generados por IA, obteniendo implementaciones en sistemas embebidos en tiempo real con desempeño comparable o superior al de métodos de control tradicionales.

🧩 Hipótesis secundarias
H1 — Generación

Los algoritmos de IA pueden producir controladores robustos aun con modelos aproximados del sistema.
H2 — Simplificación

Las expresiones de control generadas por IA pueden aproximarse mediante funciones más simples (polinomiales o acotadas) sin pérdida significativa de desempeño.
H3 — Implementación

El código C generado automáticamente puede cumplir restricciones de tiempo real en hardware embebido de recursos limitados.
H4 — Desempeño

Los controladores IA simplificados mantendrán:

    estabilidad

    robustez

    tiempos de respuesta competitivos
    frente a PID/MPC/diseños clásicos.

H5 — Automatización

Un flujo automático reduce significativamente:

    tiempo de desarrollo

    intervención manual

    errores humanos

❓ Preguntas de investigación

Muy útiles para el planteamiento del problema.

    ¿Qué algoritmos de IA generan controladores más adecuados para implementación embebida?

    ¿Cómo reducir la complejidad matemática sin degradar el desempeño?

    ¿Qué métodos de aproximación funcional son más eficientes computacionalmente?

    ¿Cómo garantizar ejecución determinista en tiempo real?

    ¿Cuál es el costo computacional máximo aceptable para el controlador?

    ¿El desempeño supera o iguala a controladores clásicos?

    ¿Se puede automatizar todo el pipeline sin intervención manual?

🧪 Variables a medir (para experimentación)
Independientes

    tipo de algoritmo IA

    método de simplificación

    frecuencia de muestreo

    hardware embebido

Dependientes

    error RMS

    tiempo de establecimiento

    sobreimpulso

    robustez ante perturbaciones

    uso de CPU

    uso de memoria

    latencia de ejecución

🎓 Versión ultra-corta (para diapositiva)

Objetivo:
Automatizar IA → simplificación → C → embebido → tiempo real.

Hipótesis:
Los controladores generados por IA pueden implementarse eficientemente en sistemas embebidos manteniendo alto desempeño mediante simplificación matemática y traducción automática.

Si quieres, en el siguiente paso te puedo generar:
✅ marco metodológico formal estilo tesis
✅ diagrama del pipeline
✅ tabla objetivos ↔ métricas ↔ experimentos
✅ o redactarlo en formato académico (capítulo de protocolo)

Dime cuál prefieres.


ChatGPT can make mistakes. Check important info. See Cookie Preferences.




📘 Marco metodológico
1. Enfoque de la investigación

La presente investigación adopta un enfoque cuantitativo, experimental y aplicado, orientado al diseño, implementación y validación de un proceso automatizado para la generación de controladores mediante técnicas de inteligencia artificial y su ejecución en sistemas embebidos con restricciones de tiempo real.

El trabajo combina:

Investigación teórica → análisis de algoritmos de IA y métodos de aproximación funcional

Desarrollo tecnológico → creación de herramientas software automáticas

Validación experimental → pruebas en hardware real

Por su naturaleza, se clasifica como investigación tecnológica–experimental, debido a que no solo propone modelos teóricos, sino que implementa y evalúa prototipos funcionales.

2. Diseño metodológico general

Se propone un proceso iterativo de desarrollo y validación, compuesto por cinco etapas principales:

Generación automática del controlador mediante IA

Simplificación matemática del controlador

Traducción automática a código C

Implementación en sistema embebido con RTOS

Evaluación experimental del desempeño

Cada etapa produce artefactos verificables que sirven como entrada de la siguiente.

3. Etapas de la metodología
3.1 Selección del sistema físico de prueba

Se seleccionará un sistema dinámico con las siguientes características:

comportamiento no lineal

relevancia industrial

disponibilidad de banco experimental

dificultad de modelado analítico

Inicialmente se utilizará un convertidor elevador (boost converter) por presentar:

fase no mínima

parámetros inciertos

entrada acotada

alta no linealidad

Lo anterior lo convierte en un banco de pruebas adecuado para evaluar robustez y desempeño.

3.2 Modelado y simulación

Se desarrollará un modelo matemático aproximado del sistema con fines de simulación.

Este modelo permitirá:

evaluar controladores automáticamente

calcular métricas de desempeño

ejecutar miles de simulaciones durante el proceso de optimización

El modelo será validado comparando su respuesta contra mediciones experimentales.

3.3 Generación automática de controladores por IA

Se implementarán y evaluarán distintos enfoques:

optimización por enjambre de partículas (PSO)

programación genética

sistemas difusos (FIS)

ANFIS

El procedimiento general consistirá en:

generar una población inicial de controladores

simular el sistema en lazo cerrado

evaluar desempeño mediante una función de costo

evolucionar la población

seleccionar el mejor controlador

Función de costo típica

Podrá incluir:

error cuadrático medio

tiempo de establecimiento

sobreimpulso

esfuerzo de control

penalización por inestabilidad

El resultado será una expresión matemática del controlador.

3.4 Simplificación del controlador

Dado que los controladores generados por IA tienden a ser complejos, se propondrá un proceso de reducción de complejidad computacional, mediante:

aproximación polinomial (bases de Bernstein)

truncamiento de términos de baja contribución

limitación de frecuencia o amplitud

reducción de orden dinámico

El objetivo es:

disminuir operaciones aritméticas

reducir uso de memoria

facilitar implementación en tiempo real

Se verificará que la simplificación no degrade significativamente el desempeño.

3.5 Traducción automática a código C

Se desarrollará una herramienta software que:

convierta expresiones matemáticas a código C

optimice operaciones

elimine redundancias

garantice portabilidad

El código generado deberá cumplir:

ejecución determinista

bajo consumo de memoria

compatibilidad con compiladores embebidos

3.6 Implementación en sistema embebido

El controlador será desplegado en un sistema con:

microcontrolador o SoC

sistema operativo de tiempo real (RTOS)

adquisición analógica/digital

generación de señales de control

Se configurará:

periodo de muestreo

prioridades de tareas

interrupciones

canales de E/S

Se verificará cumplimiento de restricciones temporales mediante análisis de latencia y jitter.

3.7 Evaluación experimental

Se evaluará el desempeño del sistema en lazo cerrado mediante pruebas controladas.

Métricas consideradas
Dinámicas

error RMS

tiempo de establecimiento

sobreimpulso

robustez ante perturbaciones

Computacionales

tiempo de ejecución

uso de CPU

memoria utilizada

consumo energético

Los resultados se compararán contra:

controladores clásicos (PID/MPC)

controlador IA no simplificado

3.8 Proceso iterativo de mejora

Si el desempeño no cumple los criterios establecidos:

se identificará la etapa problemática

se ajustarán parámetros o métodos

se repetirá el ciclo

Este esquema asegura refinamiento progresivo.

4. Variables de estudio
Variables independientes

algoritmo de IA utilizado

técnica de simplificación

frecuencia de muestreo

plataforma hardware

Variables dependientes

desempeño dinámico

estabilidad

consumo de recursos

tiempo de cómputo

5. Instrumentos y herramientas
Software

simuladores numéricos

herramientas de optimización

generador automático de código

compiladores C embebidos

Hardware

sistema embebido con RTOS

sensores y actuadores

osciloscopio y equipo de medición

fuente programable

6. Criterios de validación

Se considerará exitoso el método propuesto si:

el controlador se genera automáticamente

puede ejecutarse en tiempo real

respeta restricciones de hardware

mantiene o mejora desempeño respecto a métodos clásicos

7. Productos esperados

algoritmos de IA adaptados a embebidos

software de simplificación automática

traductor automático a C

prototipo funcional en hardware real

métricas comparativas de desempeño

Si quieres, ahora te puedo generar también:

✅ diagrama visual del pipeline metodológico
✅ tabla Objetivo → Método → Métrica → Resultado esperado
✅ versión más corta para protocolo (2–3 páginas)
✅ o redactarlo en estilo artículo científico

¿Qué formato te sirve más para tu tesis ahora?

Is this conversation helpful so far?




ChatGPT can make mistakes. Check important info. See Cookie Preferences.


