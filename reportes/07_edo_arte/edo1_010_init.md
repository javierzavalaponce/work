```{=latex}
\clearpage
```

# Estudio sobre la propuesta

Paradigma positivista


Añadir al inicio del capitulo 3:

La presente investigación se enmarca en el *paradigma positivista* de la ingeniería, bajo el supuesto de que el sistema físico (convertidor elevador) puede ser representado mediante un modelo matemático determinista. Se asume que el desempeño del controlador es una magnitud objetiva y cuantificable a través de índices de rendimiento escalares. La validación de la propuesta se realizará mediante la comparación experimental entre la salida del sistema real y la salida predicha por el modelo en simulación.

\rule{0.6\textwidth}{0.4pt}

***Hipótesis***: La aproximación polinomial de un controlador generado por IA preserva la estabilidad del sistema en lazo cerrado siempre que el error de aproximación se mantenga por debajo de un umbral α en la norma H-infinito.

\rule{0.6\textwidth}{0.4pt}


Para determinar la causa de un desempeño insatisfactorio, se implementará un análisis de sensibilidad paramétrico. Se variarán sistemáticamente: (a) la frecuencia de muestreo, (b) la resolución del ADC (bits), y (c) el orden del polinomio simplificador. Esto permitirá aislar si la falla proviene de la dinámica del controlador, de la limitación del hardware, o del proceso de simplificación.

\rule{0.6\textwidth}{0.4pt}


Solo creo lo que veo. La realidad es perfectamente replicable mediante un modelo matemático. No hay espacio para la incertidumbre epistémica; el error es meramente numérico.


Reduccionismo: Su lógica es: "Si puedo escribir la función matemáticaC y ejecutarla en un RTOS, he resuelto el problema". Conviertecomplejidad del control no lineal en un problema de compilacióasignación de ticks de rel
El sesgo fatal: Cree que la simulación es isomórfica a la realidad.por sentado que si el controlador funciona en Simulink/Python, al papor su traductor automático a C, funcionará idénticamente en el hardwaSubestima brutalmente el reality gap (brecha entre simulación y mureal) como un simple problema de resolución de ADC, cuando en realidadun problema epistemológico de modelado de incertidumbres no estructurales.


# Base Epistemologica 

El conocimiento válido en ingeniería surge de la integración entre modelado matemático, demostración formal y validación experimental.


La propuesta se fundamenta en una epistemología propia de la ingeniería matemática, en la que el conocimiento se considera válido cuando puede formularse mediante modelos matemáticos, justificarse con análisis formal y corroborarse mediante simulación e implementación experimental. La investigación adopta una perspectiva predominantemente racionalista y realista, complementada con validación empírica, y asume que las técnicas de inteligencia artificial deben integrarse con herramientas matemáticas que permitan explicar, simplificar y garantizar el comportamiento de los controladores obtenidos.

# Antitesis

Todos los modelos son incorrectos, pero algunos son útiles.


La identificación de modelos puede verse como una teoría del conocimiento aplicada a la ingeniería: 
no pregunta : "¿cómo es realmente el sistema?", sino 
"¿qué podemos conocer del sistema a partir de nuestras observaciones, y con qué grado de confianza?". 


Esa es, en el fondo, una pregunta epistemológica formulada en lenguaje de ingeniería.

# TinyML

TinyML es un concepto tecnológico y también un área de estudio.
La idea ejecutar modelos de Machine Learning en dispositivos con recursos muy limitados tales como microcontroladores.

¿Qué herramientas forman parte de TinyML?

Para *entrenar* modelos: TensorFlow, PyTorch, scikit-learn, etc.
Estas normalmente se ejecutan en una computadora.

Para *convertir* modelos: TensorFlow Lite Converter,
ONNX Converter, etc.


Para *ejecutar* modelos en microcontroladores: TensorFlow Lite Micro,
microTVM, CMSIS-NN, Edge Impulse SDK, etc

___


asdf