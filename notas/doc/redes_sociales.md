ESTE ARCHIVO TRATA DE:






Simular contagio en redes (Python o Julia)
Analizar grafos reales (centralidad, comunidades)
Modelos tipo SIR, SIS, umbral
Cómo detectar fake news con datos



Pregunta:

que info comprobable tienes de : Carl Jung demostró que no sólo los individuos sufren neurosis y traumas; también las sociedades enteras enferman a menudo en su psique colectiva


RESPUESTA:

La frase que mencionas mezcla una idea real de Carl Gustav Jung con una interpretación exagerada. Vamos por partes y con evidencia.

🧠 1. ¿Qué sí dijo Jung (comprobable)?

Jung desarrolló el concepto de inconsciente colectivo, que:

Es una parte de la psique compartida por todos los humanos, no individual.

Contiene arquetipos (patrones universales de pensamiento y simbolismo).

Se infiere observando similitudes en mitos, sueños y símbolos entre culturas.

👉 Importante:
Esto no es una “demostración científica” en el sentido moderno, sino una teoría interpretativa basada en observación clínica y comparaciones culturales.

🏛️ 2. ¿Jung habló de sociedades “enfermas”?

Sí, pero con matices:

Jung aplicó sus ideas a la cultura y la historia, sugiriendo que los fenómenos colectivos (guerras, ideologías, masas) reflejan dinámicas psíquicas profundas.
Sin embargo, esto fue más filosófico y clínico que experimental.

👉 No existe evidencia de que haya “demostrado” que:

“las sociedades enferman en su psique colectiva”
como un hecho verificable científicamente.

Es más correcto decir:
✔ Jung interpretaba que las sociedades pueden manifestar conflictos psicológicos colectivos
❌ pero no lo probó con métodos científicos modernos

🔬 3. ¿Qué dice la psicología actual?

Aquí es donde hay que ser crítico:

La psicología contemporánea no considera el inconsciente colectivo como una teoría empíricamente demostrada.
Muchas ideas de Jung son vistas como:
útiles en terapia o análisis cultural
pero difíciles de falsar o medir científicamente

En cambio, hoy se estudian fenómenos similares con otros enfoques:

Contagio social (emociones, creencias)
Psicología de masas
Dinámica de redes sociales

👉 Estos sí tienen modelos matemáticos y datos.

⚖️ 4. Conclusión clara

La frase que citas es una simplificación popular:

✔ Basada en ideas reales de Jung (inconsciente colectivo, psique compartida)
❌ Pero incorrecta al decir que él “demostró” científicamente que las sociedades enferman

Una versión más fiel sería:

Jung propuso que existen estructuras psíquicas colectivas y que los fenómenos sociales pueden reflejar conflictos psicológicos compartidos, pero esto es una interpretación teórica, no una demostración científica.

Si quieres, puedo conectarte esto con cosas modernas (por ejemplo: polarización política, redes sociales o “histerias colectivas”) y ver dónde Jung sí encaja… y dónde ya no.

Dinámica de redes sociales  , esto me interesa

Buen enfoque — aquí sí entramos en terreno medible y moderno, muy distinto a Jung. La dinámica de redes sociales intenta explicar cómo se propagan ideas, emociones y comportamientos usando modelos matemáticos, datos y grafos.

🧠 1. La idea base: una red

Una red social se modela como:

Nodos → personas
Aristas → relaciones (amistad, follow, interacción)

Esto viene de la Teoría de grafos.

Lo interesante no es solo quién está conectado, sino cómo está conectado:

redes densas vs dispersas
hubs (usuarios muy conectados)
comunidades (clusters)
🔥 2. Cómo se propaga algo (idea, emoción, rumor)

Aquí entra el concepto clave: difusión.

Un modelo clásico es:

I
t+1
	​

=I
t
	​

+βI
t
	​

(N−I
t
	​

)

Donde:

I
t
	​

: personas “infectadas” (que adoptaron la idea)
β: probabilidad de contagio
N: población total

👉 Esto es una adaptación de modelos epidemiológicos (como el SIR).

🌊 3. Contagio social (emociones e ideas)

Esto sí está bien documentado:

Emociones como felicidad, enojo o miedo se contagian
Ideas virales siguen patrones similares a enfermedades
La repetición aumenta la probabilidad de creencia (efecto exposición)

Relacionado con:

Contagio social
Psicología de masas
🧩 4. Fenómenos clave que explican “sociedades que parecen enfermar”

Aquí es donde se conecta con tu intuición tipo Jung, pero con datos:

📌 a) Cámaras de eco
Solo ves ideas similares a las tuyas
Refuerza creencias extremas
📌 b) Cascadas de información
La gente copia decisiones de otros aunque sean incorrectas
Ejemplo: fake news que se vuelven “verdad” por repetición
📌 c) Polarización
Dos grupos se vuelven cada vez más opuestos
Medible en redes como Twitter o Facebook
📊 5. Qué hace esto poderoso (y peligroso)

Porque ahora sí hay evidencia:

Se analizan millones de datos en tiempo real
Se puede predecir qué se vuelve viral
Se pueden manipular tendencias (marketing, política)

Ejemplo de campo relacionado:

Ciencia de redes
⚖️ 6. Conexión con tu idea original (Jung vs ciencia moderna)

Aquí viene lo interesante:

Jung → intuición: “lo colectivo tiene vida psicológica propia”
Ciencia actual → modelo:
✔ Las redes generan comportamientos emergentes
✔ Grupos pueden actuar de forma irracional
✔ Se pueden detectar “patologías colectivas” (polarización extrema, desinformación)

Pero:

❌ No es una “psique colectiva mística”
✔ Es resultado de interacciones + estructura de red
🧭 Si quieres profundizar

Te puedo llevar por rutas más técnicas según tu perfil (que ya veo que te gusta programar):

Simular contagio en redes (Python o Julia)
Analizar grafos reales (centralidad, comunidades)
Modelos tipo SIR, SIS, umbral
Cómo detectar fake news con datos

Solo dime qué te gustaría:
👉 ¿más matemático, más programación o más aplicado a redes reales?





----------------


que es esto: Modelos tipo SIR, SIS, umbral

Son modelos matemáticos de difusión/contagio en redes (o poblaciones). Se usan para describir cómo algo “se propaga”: enfermedades, ideas, rumores, comportamientos.

🦠 1. Modelo SIR (Susceptible–Infectado–Recuperado)

Divide a la población en 3 estados:

S: susceptibles (aún no adoptan / no están infectados)
I: infectados (sí adoptaron / están activos)
R: recuperados (ya no participan o son inmunes)

La dinámica típica es:

⎩

⎨

⎧
	​

dt
dS
	​

=−βSI
dt
dI
	​

=βSI−γI
dt
dR
	​

=γI
	​


Cómo interpretarlo en redes sociales:

S → gente que no ha visto el contenido
I → gente que lo comparte
R → gente que ya se cansó o lo ignoró

👉 Ejemplo: un meme que explota y luego muere.

🔁 2. Modelo SIS (Susceptible–Infectado–Susceptible)

Aquí no hay inmunidad:

S → I → S → I → …

La dinámica:

dt
dI
	​

=βI(N−I)−γI

Interpretación:

Puedes “reinfectarte” (volver a creer, compartir o reaccionar)

👉 Ejemplo:

rumores persistentes
temas recurrentes (conspiraciones, tendencias cíclicas)
⚖️ 3. Modelo de umbral (Threshold model)

Este es diferente (y muy importante para redes sociales):

👉 No te contagias por una sola exposición, sino cuando suficientes vecinos ya lo hicieron.

Idea básica:

Adopta si 
vecinos totales
vecinos activos
	​

>θ

Donde:

θ: umbral personal (ej. 0.3 = 30%)

Interpretación:

No compartes algo hasta que “muchos” lo hacen

👉 Ejemplos:

unirte a una protesta
usar una app nueva
adoptar una opinión política
🧠 Diferencia clave (esto es lo importante)
Modelo	Cómo ocurre el contagio
SIR	contacto directo basta
SIS	igual que SIR pero repetible
Umbral	necesitas presión social





Conexión con redes sociales reales
SIR → viralidad rápida (TikToks, memes)
SIS → temas que nunca mueren
Umbral → cambios sociales grandes (modas, ideologías)
⚠️ Insight potente

Aquí está lo interesante (y conecta con tu intuición inicial):

En SIR/SIS → el contagio es biológico-like
En umbral → el contagio es social + psicológico

👉 Por eso fenómenos como:

polarización
“cancelaciones”
burbujas ideológicas

se explican mejor con modelos de umbral.

Si quieres, podemos hacer algo más práctico (muy acorde a tu perfil):

👉 
simular uno de estos modelos en Julia o Python y ver cómo cambia el comportamiento al modificar parámetros (β, γ, θ).





