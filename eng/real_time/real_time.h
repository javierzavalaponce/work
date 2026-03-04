


al parecer existenestos tres tipos de shcheduler
1. Cooperative
2. Preemptive
3. Round Robin
4. Priority-based
5. Real-Time Schedulers (RTOS)
a)Rate Monotonic (RM)
b)Earliest Deadline First (EDF)
c)Fixed Priority Preemptive


---------------------------------------------------


Cooperative (no preemptivo)

Las tareas ceden voluntariamente

Más simple
Menos overhead
Riesgo: una tarea puede bloquear todo
Usado en:
Sistemas muy simples
Algunos microcontroladores pequeños

2️⃣ Preemptive

El kernel decide cuándo cambiar de tarea

Usa interrupciones de timer

Soporta prioridades

Más robusto

Usado en:

RTOS modernos

Sistemas operativos generales

3️⃣ Round Robin

Cada tarea recibe un "time slice"

Puede ser cooperativo o preemptivo

Todos rotan en orden

4️⃣ Priority-based

Cada tarea tiene prioridad

La más alta siempre corre

Puede ser:

Preemptivo (más común)

Cooperativo

5️⃣ Real-Time Schedulers (RTOS)

En sistemas embebidos se usan variantes como:

Rate Monotonic (RM)

Earliest Deadline First (EDF)

Fixed Priority Preemptive

🏗 En sistemas reales

En:

Linux → scheduler completamente preemptivo CFS

Windows → preemptivo por prioridad

FreeRTOS → configurable (cooperative o preemptive)

Zephyr → preemptive por prioridad




