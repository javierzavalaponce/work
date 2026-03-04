Duración: 4 a 6 semanas
-------------------------------
Etapa 0 — bases matemáticas
Etapa 1 — función de transferencia profunda
Etapa 2 — estabilidad formal
Etapa 3 — root locus completo
Etapa 4 — bode completo
Etapa 5 — nyquist completo
Etapa 6 — diseño PID real


Si4713

   FUNCION DE TRANSFERENCIA
                         │
        ┌────────────────┼────────────────┐
        │                │                │
    Analisis         Estabilidad       Diseño
        │                │                │
        │                │                │
    Bode            Nyquist        Lugar de las raíces
        │                │                │
        └───────────────┼────────────────┘
                        │
                    Ajuste PID



Objetivo general

Al finalizar este plan deberías poder:

Interpretar una función de transferencia físicamente
Predecir estabilidad
Entender la respuesta temporal
Diseñar un controlador PID básico
Analizar estabilidad usando Bode, Nyquist y Lugar de Raíces
Sin usar espacio de estados.
--------------------------------------------
2️⃣ Requisitos previos mínimos (fundamentos)
Debes sentirte cómodo con:
Matemáticas
Álgebra básica
Números complejos básicos
Exponenciales

Especialmente:

e−at
e
−at
y
s=σ+jω
s=σ+jω
Sistemas físicos

Comprender bien:

Sistema RC
Sistema RL
Sistema RLC
---------------------------------------

3️⃣ Orden correcto de aprendizaje (MUY IMPORTANTE)

Este es el orden óptimo:

Función de transferencia (base absoluta)
Respuesta temporal
Análisis en frecuencia
Diagramas de Bode
Estabilidad y márgenes
Lugar geométrico de las raíces
Nyquist
PID clásico
----------------------------
Este orden evita confusión.





ETAPA 0 — Fundamento absoluto: función de transferencia
Duración: 2–4 días
Objetivo: comprender qué es realmente
Debes entender:
Qué representa:
G(s)=Y(s)U(s)
G(s)=
U(s)
Y(s)


Qué significan:
polos
ceros
ganancia

Ejemplo fundamental:

G(s)=1RCs+1
G(s)=
RCs+1
1
---------------------------


Comprender:

qué sistema físico representa

cómo responde
---------------------------
ETAPA 1 — Respuesta temporal

Duración: 3–5 días

Entrada típica: escalón

Comprender:

respuesta exponencial

tiempo de subida

tiempo de establecimiento

sobreimpulso

Sistema clave:

G(s)=1s+a
G(s)=
s+a
1
	​


y

G(s)=1s2+2ζωns+ωn2
G(s)=
s
2
+2ζω
n
s+ω
n
2
1
---------------------------
🔹 ETAPA 2 — Análisis en frecuencia

Duración: 3–5 días

Aquí aparece:

s=jω
s=jω

Comprender:

qué significa frecuencia

respuesta senoidal

ganancia vs frecuencia

Interpretación física:

entrada senoidal → salida senoidal

---------------------------
🔹 ETAPA 3 — Diagramas de Bode

Duración: 5–7 días

Aprender a:

interpretar magnitud

interpretar fase

comprender estabilidad relativa

Conceptos clave:

frecuencia de corte

margen de ganancia

margen de fase

🔹 ETAPA 4 — Lugar geométrico de las raíces (Root Locus)

Duración: 5–7 días

Concepto fundamental:

Cómo se mueven los polos cuando cambia la ganancia.

Comprender:

estabilidad

efecto de la ganancia

interpretación geométrica

🔹 ETAPA 5 — Nyquist

Duración: 5–7 días

Objetivo:

Comprender estabilidad desde otra perspectiva.

Conceptos clave:

criterio de estabilidad

relación con polos

🔹 ETAPA 6 — PID clásico

Duración: 5–10 días

Comprender qué hace cada término:

PID=Kp+Kis+Kds
PID=K
p
	​

+
s
K
i
	​

	​

+K
d
	​

s

Interpretación física:

P → reacción inmediata

I → elimina error permanente

D → anticipa cambios

5️⃣ Ejercicios fundamentales (los más importantes)

Siempre usa sistemas simples:

Sistema tipo 1:

G(s)=1s+1
G(s)=
s+1
1
	​


Sistema tipo 2:

G(s)=10s+10
G(s)=
s+10
10
	​


Sistema tipo 3:

G(s)=1s2+2s+2
G(s)=
s
2
+2s+2
1
	​


Para cada uno:

respuesta temporal

Bode

estabilidad

6️⃣ Herramientas recomendadas

Puedes usar:

Python (control library)

MATLAB / Octave

o incluso análisis manual al inicio

Octave es excelente y libre.

7️⃣ Rutina diaria recomendada (muy importante)

Duración diaria ideal: 45–90 minutos

Formato:

20 min — teoría
20 min — ejemplos
20 min — ejercicios
10 min — reflexión

No más.

La consistencia es más importante que la duración.

8️⃣ Plan sugerido de 4 semanas

Semana 1
• Función de transferencia
• Sistemas de primer orden

Semana 2
• Sistemas de segundo orden
• Respuesta temporal

Semana 3
• Análisis en frecuencia
• Diagramas de Bode

Semana 4
• Root Locus
• PID básico

Nyquist puede esperar hasta semana 5.

9️⃣ Meta realista

Después de este plan podrás:

entender libros clásicos de control

diseñar PID básicos

analizar estabilidad

Eso es una base sólida real.

🔟 Si quieres, mañana podemos comenzar con:

Etapa 0 — comprensión profunda de la función de transferencia

y trabajar solo con:

G(s)=1s+1
G(s)=
s+1
1


Ese sistema contiene el 60% de los conceptos fundamentales.