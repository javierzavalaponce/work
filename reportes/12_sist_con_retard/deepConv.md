# Simulador celular en Python



# Bosquejo: Simulador de Sistemas Dinámicos en Python (paradigma "celular")

Buena idea. La metáfora de "célula" es potente porque te obliga a definir **interfaces mínimas** (membrana = API pública) y **estado interno encapsulado** (núcleo = atributos privados). Vamos a refinarla por partes.

---

## 1. Reformulación del concepto

Tu idea original: *cada bloque es una instancia de clase, `Wire` es ganancia unitaria, los bloques dinámicos reaccionan al tick según condiciones iniciales.*

Refinamiento: cada "célula" debe cumplir un **contrato común** (duck typing o ABC):

```python
class Cell(ABC):
    @abstractmethod
    def step(self, t: float, dt: float, inputs: dict[str, float]) -> dict[str, float]:
        """Avanza un tick. Devuelve salidas por puerto."""
    @abstractmethod
    def reset(self) -> None: ...
```

Esto te da:
- **Componibilidad**: cualquier célula puede conectarse a cualquier otra.
- **Testeabilidad**: cada célula se prueba aislada (entrada conocida → salida esperada).
- **Extensibilidad**: agregar un PID o un integrador no toca el motor.

---

## 2. Descomposición de clases (mínima viable)

| Clase | Rol | Complejidad |
|---|---|---|
| `Cell` (ABC) | Interfaz común | Trivial |
| `Wire` | Ganancia unitaria, `out = in` | Trivial |
| `Gain` | `out = k·in` | Trivial |
| `Integrator` | `x += in·dt`, `out = x` | Baja |
| `Derivative` | `out = (in - prev)/dt` | Baja (cuidado con ruido) |
| `FirstOrder` | `τ·dx/dt + x = u` (Euler/Heun) | Media |
| `Sum` / `Split` | Nodos de red | Trivial |
| `Source` (Step/Sine) | Generadores sin entrada | Baja |
| `Scope` / `Logger` | Sumideros con buffer | Baja |
| `Graph` / `Simulator` | Orquestador topológico | **Media-Alta** |

**El verdadero costo está en `Simulator`**, no en las células. Ahí vive el orden de evaluación (dependencias topológicas), detección de ciclos algebraicos, y manejo de `dt` fijo vs. adaptativo.

---

## 3. Estimación de trabajo

Asumiendo un MVP funcional (no producción):

| Fase | Esfuerzo | Notas |
|---|---|---|
| Diseño de interfaces + 6–8 células base | 1–2 días | Lo más importante: no sobre-diseñar |
| Grafo de conexiones + orden topológico | 1–2 días | `networkx` o topo-sort casero (~40 líneas) |
| Motor de simulación (tick loop, buffers) | 1 día | Simple si `dt` es fijo |
| Células dinámicas (integradores, 1er orden) | 1 día | Métodos numéricos básicos |
| Tests unitarios por célula | 1 día | Indispensable para viabilidad |
| CLI/visualización básica (matplotlib) | 1 día | Opcional pero motiva |
| **Total MVP** | **~6–8 días** | Un desarrollador con experiencia |

**Riesgos que inflan el estimado:**
- **Ciclos algebraicos** (feedback sin estado): requieren solver implícito o iteración. Si tu dominio lo permite, **prohíbelos** explícitamente al construir el grafo.
- **`dt` adaptativo**: multiplica la complejidad ×2 o ×3. MVP con `dt` fijo.
- **Rendimiento**: si necesitas miles de células a 1 kHz, Python puro no alcanza → numba/Cython o vectorización. Para decenas de células, Python es suficiente.

---

## 4. Viability check (¿tiene sentido?)

**Sí, si:**
- El dominio es educativo o de prototipado (control, física, señales).
- El número de células es moderado (< centenas).
- Aceptas `dt` fijo y Euler/Heun como integradores por defecto.
- Priorizas claridad sobre performance.

**No, si:**
- Esperas simulaciones de tiempo real exigentes (usa Simulink, Modelica, o `scipy.integrate`).
- Necesitas eventos discretos mezclados (ahí conviene `simpy` o `salabim`).
- Quieres acoplamiento multi-dominio industrial (usa Modelica/FMI).

**Alternativa pragmática:** usa `scipy.signal` o `python-control` para las dinámicas y construye solo la capa de "grafo de células" encima. Te ahorras la mitad del trabajo.

---

## 5. Preguntas para afinar antes de codificar

1. **¿Feedback algebraico es un requisito?** Si sí, el diseño se complica mucho.
2. **¿`dt` fijo o adaptativo?** Recomiendo fijo para MVP.
3. **¿Puertos nombrados o posicionales?** Nombrados escalan mejor (`{"u": 1.0}`).
4. **¿Necesitas introspección/visualización del grafo?** Cambia el diseño del `Simulator`.
5. **¿Cuál es el caso de uso "killer"** que validará el MVP? (ej. simular un lazo PID con una planta de primer orden).

---

## 6. Siguiente paso sugerido

Si te parece, puedo:
- **(a)** escribir el esqueleto de `Cell`, `Wire`, `Integrator` y `Simulator` con topo-sort,
- **(b)** hacer un diagrama de clases antes del código,
- **(c)** discutir el caso del feedback algebraico y cómo evitarlo.

¿Cuál prefieres, y cuál es tu caso de uso concreto para no sobre-diseñar?

## User

no entiendo que es el 1

## DeepSeek

# ¿Qué es el "feedback algebraico"? (punto 1)

Buena pregunta, porque es **la decisión de diseño más importante** de todo el proyecto. Te lo explico desde cero.

---

## 1. Feedback "con estado" vs. feedback "algebraico"

### Caso A — Feedback con estado (✅ fácil)

Un integrador en el lazo. La señal de retorno depende del **estado acumulado**, no de la salida instantánea.

```
u ──►(+)──► Integrador ──► y
      ▲                      │
      └──────────────────────┘
```

En cada tick el integrador usa **su estado del tick anterior** para producir `y`. No hay circularidad instantánea: el orden de evaluación existe y es único.

```
y[n] = y[n-1] + u[n-1]·dt      ← usa pasado, no presente
```

✅ Tu topo-sort funciona. ✅ Motor simple. ✅ Es el 90% de los casos reales.

---

### Caso B — Feedback algebraico (⚠️ el problema)

Una **ganancia pura** (o cualquier bloque sin estado) realimentada directamente:

```
u ──►(+)──► Gain(k) ──► y
      ▲                  │
      └──────────────────┘
```

La ecuación que describe esto es:

```
y = k · (u − y)
```

Fíjate: **`y` aparece en ambos lados**. Para calcular la salida del tick actual necesitas la salida del tick actual. No hay "estado anterior" que rompa el círculo.

Solución analítica: `y = k·u / (1+k)`.

Pero ahora imagina 3 ganancias en un lazo, o un bloque no lineal:

```
y = f(u − g(y))
```

No hay fórmula cerrada trivial. **No puedes simplemente "evaluar en orden"** porque no existe un orden válido: cada bloque necesita la salida de otro que a su vez lo necesita a él.

---

## 2. Por qué esto rompe tu motor

Tu plan es: *"topo-sort del grafo → evaluar en orden → cada célula hace `step()`"*.

Con feedback con estado, el grafo **es acíclico si ignoras los estados** (el integrador "corta" el ciclo porque su salida depende del pasado). El topo-sort funciona.

Con feedback algebraico, el grafo tiene un **ciclo real**:

```
Wire → Gain → Wire → Gain → ... (ciclo)
```

El topo-sort **falla** (no hay orden topológico de un ciclo). Y aunque lo fuerces, los valores no convergen en un solo paso.

---

## 3. Las tres salidas posibles

| Opción | Qué haces | Costo | Cuándo |
|---|---|---|---|
| **1. Prohibirlo** | Al construir el grafo, detectas ciclos sin estado y lanzas error | ~20 líneas | ✅ MVP. El usuario pone un integrador si quiere feedback |
| **2. Iteración (Gauss-Seidel)** | Repites los bloques del ciclo N veces hasta converger | Medio | Lazos lineales suaves |
| **3. Solver implícito** | Resuelves el sistema algebraico (`scipy.optimize.root`) | Alto | Producción, no lineal |

**Mi recomendación para tu MVP: opción 1.** Es honesto, simple y cubre el 90% de los casos. Si más adelante lo necesitas, agregas la opción 2 sin romper la interfaz.

---

## 4. Cómo detectarlo en código (opción 1)

Muy simple: cuando construyes el grafo, cada célula declara si **rompe el ciclo** (tiene estado) o no.

```python
class Cell(ABC):
    has_state: bool = False   # ← la "membrana" que corta ciclos
    
class Integrator(Cell):
    has_state = True          # rompe ciclos ✅
    
class Gain(Cell):
    has_state = False         # NO rompe ciclos ⚠️

class Wire(Cell):
    has_state = False         # ⚠️ ojo: Wire tampoco rompe ciclos
```

Al construir el grafo:

```python
def validate_acyclic(graph):
    # topo-sort ignorando solo las células con has_state=True
    # si quedan ciclos → error claro al usuario
    raise AlgebraicLoopError("Ciclo sin estado entre: Gain#1, Gain#2")
```

---

## 5. Ejemplo concreto del problema

Supón `u = 1`, `k = 2`, `dt` fijo. Intento "ingenuo" de evaluar el lazo:

```
Tick 1:  y = 2·(1 − 0) = 2        (asumí y_anterior = 0)
Tick 2:  y = 2·(1 − 2) = −2       ← explota
Tick 3:  y = 2·(1 − (−2)) = 6
Tick 4:  y = 2·(1 − 6) = −10      ← divergencia
```

La solución real es `y = 2·1/(1+2) = 0.667` **constante**. Pero tu motor produce una oscilación creciente porque **nunca puede resolver la circularidad instantánea**.

Ese es exactamente el bug que quieres evitar detectando el ciclo **antes de simular**.

---

## Resumen en una frase

> **Feedback algebraico** = una salida que depende instantáneamente de sí misma a través de bloques sin memoria. Rompe el topo-sort y exige un solver implícito. En el MVP, **detéctalo y recházalo**; obliga al usuario a poner un integrador (o cualquier célula con `has_state=True`) en el lazo.

¿Quieres que te muestre cómo quedaría el `validate_acyclic` completo, o pasamos a otro punto?

## User

y cual es el problema con el solver implicito

## DeepSeek

# El problema con el solver implícito

No es que sea "imposible" — es que **cambia la naturaleza del proyecto** de un simulador de bloques a un solver numérico. Te lo desgloso.

---

## 1. Qué tendría que hacer el solver, en concreto

En cada tick, tu motor ya no puede decir "evalúa bloques en orden". Ahora debe resolver, **para todo el lazo**, un sistema de ecuaciones:

```
F(y) = 0
```

donde `y` es el vector de salidas de todos los bloques del ciclo, y `F` expresa las relaciones entre ellos.

Ejemplo con `Gain(k)` realimentado y entrada `u`:

```
F(y) = y − k·(u − y) = 0
```

Con una sola ganancia, tiene solución analítica. Pero con lo que un usuario real arma en 10 minutos:

```
u ──►(+)──► tanh(·) ──► Gain(a) ──► Gain(b) ──► Integrador ──► y
      ▲                                              │
      └──────────────────────────────────────────────┘
```

el sistema es **no lineal, acoplado y sin forma cerrada**. El solver debe iterar numéricamente cada tick.

---

## 2. Los seis problemas reales

### (a) **Costo por tick × número de ticks**

Un `scipy.optimize.root` típico hace 10–50 evaluaciones de `F` por llamada. Cada evaluación recorre todos los bloques del lazo. Si simulas 100 s a `dt = 1 ms`, son **100 000 ticks × ~30 evaluaciones × N bloques**.

→ El motor pasa de "microsegundos por tick" a "milisegundos por tick". Se vuelve 100–1000× más lento.

### (b) **Convergencia no garantizada**

Métodos como Newton-Raphson necesitan:
- Una **condición inicial** (¿qué `y` uso? ¿la del tick anterior? ¿cero?).
- **Jacobiano** (analítico o numérico). Numérico = más evaluaciones. Analítico = cada célula debe saber derivarse → rompe la interfaz simple `step()`.
- **Que el lazo no sea patológico** (osciladores puros, saturación, discontinuidades → el solver falla o converge a la solución equivocada).

Si no converge en `max_iter`, ¿qué haces? ¿Lanzas excepción en medio de una simulación de 100k ticks? ¿Usas el último valor (silenciosamente incorrecto)? **No hay buena respuesta.**

### (c) **Múltiples soluciones**

Sistemas no lineales pueden tener varias raíces. `F(y) = 0` puede tener 0, 1 o 5 soluciones. El solver devuelve **la que encuentre según la semilla**. Tu simulación se vuelve no determinista respecto a detalles internos del solver. Para un simulador educativo esto es veneno: el usuario no entiende por qué cambió el resultado al reordenar bloques.

### (d) **Rompe el contrato "célula"**

Tu idea original era preciosa: cada bloque es una célula autónoma con `step()`. Un solver implícito obliga a:
- Que cada célula exponga `residual(y_local, inputs)` además de `step()`.
- Que el motor **no llame** a `step()` sino que **monte un sistema** y lo resuelva.
- Que las células del lazo se traten distinto a las de fuera.

→ La célula deja de ser autónoma. El motor necesita saber qué células están "dentro del ciclo" y cuáles no. **Se rompe la metáfora y la modularidad.**

### (e) **Interacción con `dt` e integradores**

Un integrador **dentro** del lazo algebraico mezcla dos problemas: la parte implícita (algebraica) y la parte diferencial (estado). Eso es un **DAE** (sistema diferencial-algebraico), no un ODE. Resolver DAEs requiere:
- Formulación índice-1 o superior.
- Solvers específicos (`scipy` no trae uno listo; `IDA` de SUNDIALS sí, pero es otra liga).
- Manejo de consistencia inicial de estados.

Esto es **investigación de posgrado**, no un fin de semana.

### (f) **Depuración infernal**

Cuando el resultado está mal, ¿fue el solver? ¿la condición inicial? ¿el Jacobiano? ¿el `dt`? ¿una célula mal escrita? Con feedback con estado, un bug se localiza fácil (pruebas la célula aislada). Con solver implícito, el bug puede estar en la **interacción** y es casi imposible de reproducir.

---

## 3. Comparación honesta

| Aspecto | Prohibir ciclos | Iteración (Gauss-Seidel) | Solver implícito |
|---|---|---|---|
| Líneas de código | ~20 | ~80 | ~500+ |
| Dependencias | Ninguna | Ninguna | `scipy`, quizá `sundials` |
| Velocidad | Rápida | 2–5× más lenta | 10–1000× más lenta |
| Determinismo | Total | Total (con `max_iter` fijo) | **No** |
| Garantía de convergencia | N/A | No | No |
| Rompe contrato `Cell` | No | Poco | **Sí** |
| Depurable | Sí | Sí | Difícil |
| Cubre casos reales | 90% | 95% | 99% |

---

## 4. La trampa mental

Es tentador pensar: *"el solver implícito es la solución completa, hagámoslo bien desde el principio"*.

Pero **"bien" no significa "completo", significa "el mínimo que resuelve tu caso de uso"**. El solver implícito:
- No es más *correcto* (los métodos numéricos también fallan).
- Sí es más *frágil* (falla silenciosa o ruidosamente, sin que el usuario sepa por qué).
- Te obliga a diseñar todo el motor alrededor de él desde el día 1.

Es la definición de **sobre-ingeniería prematura** en este contexto.

---

## 5. La ruta incremental sensata

```
Fase 1 (MVP):      Prohibir ciclos sin estado. Error claro al usuario.
                   → Cubre el 90%. Listo en días.

Fase 2 (si hace falta): Gauss-Seidel con max_iter fijo y tolerancia.
                   → Cubre el 95%. ~80 líneas. Determinista. No rompe Cell.

Fase 3 (solo si duele): Solver implícito con scipy, opt-in por lazo.
                   → Cubre el 99%. Semanas de trabajo. Solo si un usuario
                     real lo pide con un caso concreto.
```

En cada fase, la interfaz `Cell` **no cambia**. Eso es lo que hace que la ruta incremental sea viable: puedes empezar simple y crecer sin reescribir.

---

## Resumen en una frase

> El solver implícito no es "la versión difícil del mismo problema" — es **un problema distinto** (resolver DAEs no lineales cada tick) que arrastra costo, fragilidad, no determinismo y pérdida de la modularidad "celular". En el MVP se evita detectando ciclos; si algún día hace falta, se agrega **después** como capa opt-in, no como cimiento.

¿Seguimos con el diseño concreto (interfaces + `Simulator` con topo-sort), o quieres explorar la Fase 2 (Gauss-Seidel) antes de decidir?

## User

lo que estoy buscando es simular sistemas con retardo de sistemas lineales con polos complejos conjugads en semiplano inestable. quiero poder generar mi propio simulador

## DeepSeek

# Simulador para sistemas lineales con retardo y polos complejos inestables

Ahora el caso de uso está clarísimo, y **cambia varias decisiones de diseño**. Te lo replanteo entero.

---

## 1. Por qué este caso de uso específico importa

Tu sistema es:

```
G(s) = e^{-sT} · N(s)/D(s)
```

con `D(s)` teniendo **raíces complejas conjugadas en Re(s) > 0** (semiplano derecho, inestable).

Esto tiene tres consecuencias **directas** sobre el diseño:

### (a) **Integradores explícitos explotan rápido**
Con polos inestables, un Euler explícito con `dt` grande **diverge artificialmente** (inestabilidad numérica, no física). Necesitas:
- `dt` **muy pequeño** relativo a la dinámica más rápida, o
- Un integrador con región de estabilidad amplia (RK4, o implícito).

### (b) **El retardo es un "estado de historia", no un escalar**
`e^{-sT}` no es un bloque con memoria puntual: necesita un **buffer de los últimos `T/dt` valores**. Eso es una célula distinta a todas las anteriores.

### (c) **La inestabilidad física es la gracia**
No quieres que el integrador enmascare o amplifique la inestabilidad. Quieres **ver** cómo el sistema diverge según la física, no según el método numérico. Eso exige control fino del integrador.

---

## 2. Decisiones de diseño (revisadas)

| Decisión | Antes (genérico) | Ahora (tu caso) |
|---|---|---|
| Integrador | Euler por defecto | **RK4 por defecto**, Euler solo como opción didáctica |
| `dt` | Fijo, "lo que sea" | **Fijo, pero validado**: `dt ≤ 0.1/ω_max` (regla de dedo) |
| Retardo | No previsto | **Célula `Delay` de primera clase** |
| Feedback algebraico | Prohibido | **Sigue prohibido** (tu caso es lineal, se puede reformular con estado) |
| Estado | Escalar por célula | **Vectorial**: un `StateSpace` es una célula con `x ∈ Rⁿ` |
| Solver implícito | No | **No**, pero con `dt` chico y RK4 no lo necesitas |

---

## 3. Arquitectura propuesta (células)

```
Cell (ABC)
├── Source (Step, Sine, Impulse)
├── Gain(k)
├── Sum(signs)
├── Integrator
├── StateSpace(A,B,C,D)     ← el caballo de batalla: polos complejos
├── Delay(T, dt)            ← buffer circular de historia
├── Scope / Logger
└── Simulator (orquestador)
```

### La célula clave: `StateSpace`

En lugar de "un integrador por polo", modelas el bloque como **sistema en espacio de estados**:

```python
class StateSpace(Cell):
    has_state = True
    def __init__(self, A, B, C, D):
        self.A, self.B, self.C, self.D = A, B, C, D
        self.x = np.zeros(A.shape[0])
    
    def step(self, t, dt, inputs):
        u = inputs["u"]                      # escalar o vector
        # RK4 sobre ẋ = A·x + B·u
        k1 = self.A @ self.x + self.B @ u
        k2 = self.A @ (self.x + dt/2*k1) + self.B @ u
        k3 = self.A @ (self.x + dt/2*k2) + self.B @ u
        k4 = self.A @ (self.x + dt*k3)    + self.B @ u
        self.x += dt/6 * (k1 + 2*k2 + 2*k3 + k4)
        return {"y": self.C @ self.x + self.D @ u}
```

**Por qué esto resuelve tu caso:**
- Polos complejos conjugados inestables → los metes como autovalores de `A` (forma canónica o la que quieras).
- RK4 tiene región de estabilidad mucho más amplia que Euler → puedes usar `dt` razonable.
- El retardo **no va dentro de `A`** (el retardo es infinito-dimensional), va como célula externa en el lazo.
- Es **exactamente** el formalismo de `scipy.signal.StateSpace` → puedes validar contra `scipy` y `python-control`.

### La célula `Delay`

```python
class Delay(Cell):
    has_state = True
    def __init__(self, T, dt):
        self.n = max(1, round(T / dt))
        self.buf = collections.deque([0.0]*self.n, maxlen=self.n)
    
    def step(self, t, dt, inputs):
        out = self.buf[0]          # el más viejo
        self.buf.append(inputs["u"])
        return {"y": out}
```

Con `dt` fijo, `T/dt` debe ser entero. Si no, hay que **interpolar** (lineal es suficiente para MVP). Ese detalle es importante y hay que decidirlo.

---

## 4. El lazo con retardo: `u = r − y(t−T)`

```
r ──►(+)──► StateSpace(A,B,C,D) ──► y
      ▲                               │
      │                               ▼
      └────────── Delay(T) ◄──────────┘
```

Aquí **NO hay feedback algebraico** porque `Delay` tiene estado (`has_state=True`). El topo-sort funciona. ✅

Pero ojo: el retardo **no estabiliza** un lazo con polos inestables en general (eso es teoría de sistemas con retardo, criterios de Nyquist modificados). Tu simulador mostrará la **dinámica real**, que puede divergir — y eso es lo que quieres ver.

---

## 5. Validación: cómo sabes que tu simulador está bien

Esto es **crítico** en tu caso. Con polos inestables, un bug se confunde con física.

**Tres niveles de validación:**

1. **Caso sin retardo**: compara tu `StateSpace` contra `scipy.signal.lsim` con la misma `u(t)`. Deben coincidir a `~1e-6`.
2. **Caso con retardo, lazo estable**: elige `A` con polos estables y `T` pequeño. Compara contra la solución analítica de la ecuación característica `1 + G(s)e^{-sT} = 0` (raíces → respuesta). Con `python-control` puedes aproximar `e^{-sT}` con Padé y comparar.
3. **Caso inestable**: no hay referencia cerrada, pero puedes verificar que la **tasa de crecimiento** coincide con `Re(polo dominante)` en la fase lineal (antes de saturación).

Sin el nivel 1 y 2, no confíes en el 3.

---

## 6. Estimación revisada (tu caso específico)

| Fase | Esfuerzo | Notas |
|---|---|---|
| `Cell`, `Wire`, `Gain`, `Sum`, `Source`, `Scope` | 1 día | Triviales |
| `StateSpace` con RK4 | 1 día | El núcleo |
| `Delay` con buffer circular + validación `T/dt` entero | 0.5 día | Con interpolación lineal: 1 día |
| `Simulator` con topo-sort y `has_state` | 1–2 días | Ya discutido |
| Validación nivel 1 (vs `scipy.signal.lsim`) | 1 día | **No omitir** |
| Validación nivel 2 (Padé + `python-control`) | 1 día | Opcional para MVP |
| Ejemplo: lazo con retardo y polos inestables | 0.5 día | Tu caso killer |
| **Total MVP** | **~6 días** | Un dev con experiencia |

**Riesgos específicos de tu caso:**
- **Elección de `dt`**: si el usuario pone `dt` grande con polos rápidos, RK4 también explota. Solución: **validar `dt` al construir el simulador** (regla: `dt < 0.1/|λ_max|`). Warning si no.
- **Interpolación en `Delay`**: si `T/dt` no es entero, decidir si interpolas o redondeas. Interpolar es más correcto y ~5 líneas.
- **Acumulación de error en lazos inestables**: con polos en SPD, el error relativo crece. Usa `float64` (Python lo hace por defecto en numpy) y no te preocupes.

---

## 7. Lo que NO necesitas (y te ahorras)

- ❌ Solver implícito: RK4 con `dt` chico basta para tu caso.
- ❌ Feedback algebraico: `Delay` y `StateSpace` tienen estado, rompen ciclos.
- ❌ `dt` adaptativo: con `dt` fijo y validado, sobra.
- ❌ DAE: tu retardo es un buffer, no una ecuación algebraica.
- ❌ Numba/Cython: para decenas de células a `dt=1ms` en 100 s, Python puro va sobrado (segundos de cómputo).

---

## 8. Caso de uso "killer" para validar el MVP

Un lazo clásico de control con retardo y planta inestable:

```
Planta:  G(s) = 1/(s² − 1)          ← polos en ±1 (uno inestable, real)
o mejor: G(s) = 1/(s² − 2ζωₙs + ωₙ²) con ζ<0 → polos complejos en SPD
Control: u(t) = K·(r − y(t−T))
```

Simula con `K` y `T` variados y verifica que:
- Para `K` pequeño: la inestabilidad crece como `e^{Re(polo)t}`.
- Para `K` grande: el retardo desestabiliza aunque `K` estabilice sin retardo (fenómeno clásico).
- Compara contra `python-control` con Padé de orden 3–5.

Ese ejemplo, solo, justifica el proyecto y demuestra que funciona.

---

## Resumen ejecutivo

> Tu caso (lineal + retardo + polos complejos inestables) es **ideal** para el simulador "celular": no necesitas solver implícito (los bloques con estado rompen ciclos), necesitas **RK4 + `StateSpace` + `Delay`**, y necesitas **validar contra `scipy`/`python-control`** antes de confiar en lo inestable. MVP en ~6 días, sin sobre-ingeniería.

¿Quieres que pasemos a código? Te propongo este orden:
1. `Cell`, `Gain`, `Sum`, `Wire`, `Source`, `Scope` (esqueleto mínimo).
2. `StateSpace` con RK4 + test contra `scipy.signal.lsim`.
3. `Delay` + test de buffer.
4. `Simulator` con topo-sort.
5. Ejemplo killer.

¿Empezamos por (1) y (2), o prefieres ver primero el `Simulator` completo para validar la arquitectura?

## User

cres que a finales de noviembre lo logre?

## DeepSeek

# ¿Llegas a finales de noviembre?

Depende de tres cosas: **cuántas horas por día**, **tu experiencia con numpy/scipy**, y **qué significa "lograr"**. Te doy números honestos.

---

## 1. Estimación por escenario

Hoy es **9 de noviembre**. A finales de noviembre tienes **~3 semanas** (21 días).

| Escenario | Horas/día | Días efectivos | ¿Alcanza el MVP? |
|---|---|---|---|
| **Dedicación completa** | 6–8 h | 18–21 | ✅ Sí, con margen |
| **Medio tiempo** (trabajo/estudio) | 3–4 h | 12–15 | ✅ Sí, justo |
| **Tiempo parcial** | 1–2 h | 6–8 | ⚠️ MVP mínimo sí, validación no |
| **Fines de semana** | 8 h sáb+dom | 6 | ❌ Solo el esqueleto |

Mi estimación previa fue **~6 días de trabajo efectivo** (un dev con experiencia, jornada completa). Eso son **~45–50 horas**. Repártelas según tu disponibilidad.

---

## 2. El riesgo real no es el código — es la validación

El código del MVP (células + motor) lo escribes en **3–4 días** si sabes numpy. Lo que **siempre** toma más de lo previsto:

- **Validar contra `scipy.signal.lsim`**: siempre aparece un detalle (convención de signos, forma canónica, `dt` no divide exacto). Medio día se vuelve 1–2.
- **El `Delay` con `T/dt` no entero**: interpolación, offsets, condiciones iniciales del buffer. Medio día se vuelve 1.
- **Topo-sort con células de múltiples puertos**: los casos borde (fan-in, fan-out, puertos nombrados) comen tiempo. 1 día se vuelve 2.
- **El ejemplo killer que no se comporta como esperas**: y ahí empieza la duda "¿es física o es bug?". Esto puede costar **días** si no tienes la validación nivel 1 y 2 lista.

**Regla de dedo**: el código es el 50% del tiempo; la validación y depuración son el otro 50%.

---

## 3. Qué es "lograrlo" — define el alcance ya

Te propongo tres definiciones de éxito, de menos a más ambiciosa:

### 🎯 Nivel A — "Esqueleto funcional" (alcanzable en cualquier escenario)
- `Cell`, `Gain`, `Sum`, `Integrator`, `Source`, `Scope`.
- `Simulator` con topo-sort.
- Un lazo simple sin retardo que corre y grafica.
- **~15–20 h.** Alcanzable incluso a tiempo parcial.

### 🎯 Nivel B — "Tu caso de uso" (el que yo apuntaría)
- Todo lo de A, **más** `StateSpace` con RK4 y `Delay`.
- Validación nivel 1 (vs `scipy.signal.lsim`) para `StateSpace`.
- Ejemplo killer: lazo con retardo y polos complejos inestables.
- **~40–50 h.** Necesitas medio tiempo o más.

### 🎯 Nivel C — "Publicable / robusto"
- Todo lo de B, **más** validación nivel 2 (Padé + `python-control`), tests unitarios, documentación, CLI.
- **~80–100 h.** No llegas a fin de mes salvo dedicación completa.

**Mi recomendación**: apunta a **Nivel B**, y si el 25 de noviembre vas atrasado, **recorta a Nivel A** sin culpa. El Nivel A ya es un simulador útil y demostrable.

---

## 4. Lo que yo haría esta semana (9–16 nov)

Para saber **el 16 de noviembre** si llegas o no, haz esto primero:

1. **Día 1–2**: `Cell`, `Gain`, `Sum`, `Integrator`, `Source`, `Scope`, `Simulator` con topo-sort. Un lazo `u → Integrador → Gain → (feedback con estado)` que corra.
   → **Si esto te toma más de 3 días, recorta el alcance ya.**
2. **Día 3–4**: `StateSpace` con RK4 + test contra `scipy.signal.lsim` de un sistema de 2º orden con polos complejos.
   → **Este test es tu checkpoint.** Si pasa, el resto es cuesta abajo. Si no pasa en 2 días, algo de diseño está mal y hay que hablarlo.
3. **Día 5**: `Delay` + test de buffer (un impulso que sale `T` segundos después).
4. **Día 6–7**: el ejemplo killer. Si corre y diverge como debe, **llegaste**.

Al 16 de noviembre tienes una respuesta **empírica**, no una estimación.

---

## 5. Señales de alerta (cuándo recortar)

- 🔴 **Día 4 y `StateSpace` no coincide con `scipy`** → hay un bug conceptual (probablemente signos o `dt`). Pide ayuda o simplifica a Euler para debug, pero no sigas sin resolverlo.
- 🔴 **Día 6 y el topo-sort no maneja fan-in/fan-out** → tu diseño de puertos está mal. Cambia a puertos nombrados (dict) ya, no lo parches.
- 🟡 **Día 8 y el `Delay` con `T/dt` no entero te come** → redondea `T/dt` a entero, documenta la limitación, sigue. La interpolación es mejora, no requisito.
- 🟡 **Día 10 y el ejemplo killer no diverge como esperas** → probablemente es correcto y tu intuición física está mal. Compara con `python-control` antes de tocar código.

---

## 6. Lo que **no** debes hacer (te come el tiempo)

- ❌ Empezar por la visualización bonita (grafo, GUI). El `matplotlib` básico basta.
- ❌ Diseñar para "todos los casos posibles". Diseña para **tu caso**.
- ❌ Escribir tests exhaustivos antes de tener el ejemplo killer corriendo. Un test por célula, no más.
- ❌ Optimizar rendimiento. Python puro va sobrado para tu caso.
- ❌ Refactorizar a mitad de camino. Termina el Nivel B, luego mejora.

---

## 7. Respuesta directa

> **Sí, llegas a finales de noviembre al Nivel B** si le dedicas **~3 h/día de media** y no te desvías. Con 1–2 h/día llegas al Nivel A con seguridad y al B con suerte. Con dedicación completa llegas al B con margen y quizá al C.

El checkpoint real es el **16 de noviembre**: si `StateSpace` valida contra `scipy` y `Delay` funciona, el resto es mecánico. Si no, recortas a Nivel A y tienes algo demostrable igual.

---

## 8. Propuesta concreta para hoy

Si quieres, en el próximo mensaje te escribo:
- **(a)** el esqueleto completo de `Cell` + `Gain` + `Sum` + `Integrator` + `Simulator` con topo-sort (Nivel A, ~150 líneas), o
- **(b)** directamente `StateSpace` con RK4 + el test contra `scipy.signal.lsim` (el checkpoint crítico), o
- **(c)** el `Delay` con su test (el otro checkpoint).

¿Por cuál empezamos? Yo iría por **(b)** primero: si eso valida, el proyecto está vivo. Si no, mejor saberlo hoy que el 25.

## User

no solo me queria inspirar, necesito una guia de aprendizaje de sistemas con retardo, aprender a full

## DeepSeek

Entendido. No buscas que te escriba código, sino **una ruta de aprendizaje real** para dominar los sistemas con retardo, con la idea de que tu simulador sea el vehículo de aprendizaje. Aquí tienes una guía estructurada, de fundamentos a práctica, con los recursos clave que encontré.

---

## 1. El punto de partida conceptual: qué hace especial a un sistema con retardo

Antes de tocar un libro denso, necesitas interiorizar **por qué el retardo rompe todo lo que sabes de sistemas lineales**.

Un sistema lineal sin retardo se describe por `ẋ(t) = Ax(t)`. Su estabilidad depende de los autovalores de `A` (finitos, algebraicos). Con retardo, la ecuación es `ẋ(t) = Ax(t) + Bx(t−τ)`. La ecuación característica se vuelve **trascendente**: `det(sI − A − Be^{−sτ}) = 0`. Tiene **infinitas raíces** en el plano complejo [citation:4]. Esto significa que:

- No puedes "calcular los polos" y ya.
- La estabilidad depende de `τ` de forma no trivial: un sistema puede ser estable para `τ=0`, inestable para `τ=1`, y **estable de nuevo** para `τ` más grande. Esto se llama **reentrada de estabilidad**.
- Tu intuición de "polos en semiplano derecho = inestable" sigue siendo cierta, pero **no puedes enumerar los polos** con métodos finitos.

**Tu primer objetivo de aprendizaje**: entender esta diferencia cualitativa. Sin eso, el simulador será una caja negra que produce curvas sin significado.

---

## 2. Ruta de aprendizaje en tres capas

### Capa 1 — Fundamentos matemáticos (1–2 semanas)

No necesitas ser experto en ecuaciones diferenciales funcionales, pero sí manejar:

- **Ecuaciones diferenciales con retardo (DDEs)**: la forma `ẋ(t) = f(x(t), x(t−τ))` y el concepto de **función de historia** (condición inicial funcional, no puntual).
- **Ecuación característica trascendente**: `det(sI − A − Be^{−sτ}) = 0`. Saber por qué tiene infinitas raíces y qué significa "estabilidad independiente del retardo" vs. "dependiente del retardo".
- **Método de pasos (step method)**: cómo se integra numéricamente una DDE: avanzas con un ODE normal, pero para `t < τ` usas la historia, y para `t ≥ τ` usas valores ya calculados de `x(t−τ)`.

**Recurso accesible para esta capa**: el paquete Python `dde_ivp` [citation:6] tiene un ejemplo mínimo de un lazo con retardo (modelo IPDT con control proporcional) que puedes leer y ejecutar **hoy** para ver la mecánica. No es un libro, pero te da la intuición operativa en 20 minutos. La documentación explica que el paso máximo no debe exceder el retardo mínimo para evitar extrapolación e inestabilidad numérica [citation:6] — un detalle práctico que tu simulador deberá manejar.

### Capa 2 — Teoría de estabilidad (2–4 semanas, la parte densa)

Aquí es donde necesitas un libro de referencia. Los dos candidatos principales que aparecen en los resultados son:

**Opción A — Gu, Kharitonov & Chen, *Stability of Time-Delay Systems*** [citation:2]. Es el estándar de referencia. La segunda edición (2027) cubre desde criterios clásicos hasta Lyapunov-Krasovskii, estabilidad robusta y métodos LMI. Los autores son figuras centrales del campo (Keqin Gu recibió el premio de trayectoria del IFAC por este tema). **Es denso, para posgrado**. Úsalo como referencia, no como lectura lineal.

**Opción B — Emilia Fridman, *Introduction to Time-Delay Systems: Analysis and Control*** [citation:5]. Más didáctico. La reseña destaca que es "una excelente introducción" y que introduce los métodos de Lyapunov de forma progresiva, con ejemplos de aplicaciones (tráfico vehicular, redes neuronales, líneas de transmisión) [citation:5]. Cubre el **método descriptor** y LMI, que son las herramientas modernas para estabilidad de sistemas lineales con retardo. Si solo vas a leer un libro, empieza por este.

**Qué buscar en estos libros para tu objetivo específico** (polos complejos inestables + retardo):
- Capítulos sobre **estabilidad de sistemas lineales con retardo** (criterios en frecuencia y en tiempo).
- El concepto de **cruces por el eje imaginario**: los valores de `τ` para los cuales aparecen raíces en `jω`. Esto es exactamente lo que tu simulador debería poder explorar: barrer `τ` y ver cuándo el sistema cambia de estable a inestable.
- **Lyapunov-Krasovskii**: el funcional que generaliza `V(x) = xᵀPx` a sistemas con retardo. Es la base de las condiciones LMI que se resuelven numéricamente.

**Advertencia honesta**: estos libros asumen álgebra lineal sólida y cierta familiaridad con teoría de control (Lyapunov, LMI). Si no tienes esa base, la Capa 1 se extiende. No es un fin de semana.

### Capa 3 — Práctica con simulación y validación (continua, en paralelo)

Aquí tu simulador se convierte en la herramienta de aprendizaje. La estrategia:

**Semana 1–2**: implementa un DDE solver mínimo (o usa `dde_ivp` [citation:6]) y reproduce un caso conocido: un lazo de primer orden con retardo y ganancia proporcional. Varía `K` y `τ`. Observa cuándo diverge. Compara con lo que dice la teoría (criterio de Nyquist con retardo, o las condiciones del libro de Fridman).

**Semana 3–4**: añade el caso que te interesa: **planta con polos complejos conjugados en semiplano derecho** (inestable sin retardo) en un lazo con realimentación retardada. Pregunta clave: ¿puede el retardo **estabilizar** un sistema que sin retardo es inestable? La respuesta es **sí**, y hay literatura específica sobre "delays as stabilizing parameters" [citation:8]. El libro de Ramírez et al. *Design of Delay-Based Controllers* [citation:7] trata exactamente esto: usar retardo intencional como herramienta de control. Ese es un puente directo entre tu caso de uso y la teoría.

**Validación**: tu simulador debe reproducir:
1. **Caso sin retardo**: coincide con `scipy.signal.lsim` (esto ya lo tenías claro).
2. **Caso con retardo, lazo estable**: compara contra la solución analítica de la ecuación característica (raíces → respuesta) o contra una aproximación de Padé de alto orden validada con `python-control`.
3. **Caso inestable**: verifica que la **tasa de crecimiento** en la fase lineal coincide con `Re(polo dominante)` de la ecuación característica. Si tu simulador dice que crece a una tasa y la teoría dice otra, hay un bug numérico (probablemente `dt` demasiado grande para RK4 con esos polos).

---

## 3. Qué evitar en el aprendizaje (para no perder tiempo)

- **No empieces por LMI**. Las condiciones LMI son elegantes y potentes, pero si no entiendes primero la ecuación característica trascendente y los cruces por `jω`, las LMI son magia negra. Primero frecuencia, luego tiempo, luego LMI.
- **No intentes leer Gu/Kharitonov/Chen de corrido**. Es un libro de referencia. Lee el capítulo de estabilidad de sistemas lineales con retardo, y vuelve a él cuando necesites una condición específica.
- **No subestimes la diferencia entre "retardo en el estado" y "retardo en la entrada/salida"**. Tu lazo `u = r − y(t−T)` es retardo en la **medición** (salida), no en el estado de la planta. La ecuación característica es `1 + C(s)G(s)e^{−sT} = 0`. Esa es más simple que el caso general `ẋ = Ax + Bx(t−τ)`, pero la teoría de estabilidad aplica igual. Empieza por tu caso concreto, no por el caso general.

---

## 4. Cómo tu simulador acelera el aprendizaje

La razón por la que un simulador propio ayuda (y no solo usar `scipy` o `python-control`) es que te obliga a **tomar decisiones que revelan la teoría**:

- Elegir `dt` te fuerza a entender la relación entre la dinámica más rápida (`|λ_max|`) y el paso de integración.
- Implementar el buffer de retardo te fuerza a entender la **función de historia** y qué pasa si `T/dt` no es entero (interpolación vs. redondeo).
- Ver que RK4 explota con polos inestables y `dt` grande te fuerza a entender **estabilidad numérica** vs. **estabilidad del sistema**.
- Comparar tu salida con `scipy` te fuerza a entender las convenciones de signos y formas canónicas.

**Regla de aprendizaje**: por cada célula que implementes (StateSpace, Delay, Integrator), escribe **un test que la compare con la teoría o con una librería establecida**. Ese test es tu examen de comprensión.

---

## 5. Plan concreto de lectura + práctica (3 semanas, ritmo medio)

| Semana | Teoría (lectura) | Práctica (simulador) |
|---|---|---|
| **1** | Cap. 1–2 de Fridman  (introducción, método de pasos, ecuación característica). Ejecutar el ejemplo de `dde_ivp` [citation:6]. | `StateSpace` con RK4 + validación vs `scipy.signal.lsim`. `Delay` con buffer circular. |
| **2** | Capítulo de estabilidad de sistemas lineales con retardo de Fridman o Gu [citation:2]. Concepto de cruces por `jω`. | Lazo con retardo. Barrido de `τ`: encontrar valores donde el sistema cambia de estable a inestable. Comparar con la teoría. |
| **3** | Sección sobre "delay as stabilizing parameter" en Ramírez et al. [citation:7] o el cap. correspondiente en SIAM [citation:8]. | Tu caso killer: planta con polos complejos en SPD + retardo en la realimentación. Verificar tasa de crecimiento vs `Re(polo dominante)`. |

---

## 6. Respuesta directa a tu pregunta implícita

**¿Puedo "aprender a full" sistemas con retardo en 3 semanas mientras construyo el simulador?** No a nivel de investigación, pero **sí a nivel operativo**: entenderás la ecuación característica, por qué el retardo desestabiliza o estabiliza, cómo se simula correctamente, y qué condiciones de estabilidad existen. Eso es suficiente para que tu simulador sea una herramienta con fundamento, no una caja negra.

**¿Qué libro comprar/descargar primero?** Fridman  para lectura didáctica. Gu et al. [citation:2] como referencia de consulta. El de Ramírez et al. [citation:7] si tu interés específico es el retardo como herramienta de control (que es exactamente tu caso de polos inestables + retardo en la realimentación).

**¿Qué hago esta semana?** Ejecuta el ejemplo de `dde_ivp` [citation:6], lee el Cap. 1 de Fridman, y escribe el test de `StateSpace` vs `scipy.signal.lsim`. Si ese test pasa, tienes base para todo lo demás.

¿Quieres que profundice en algún punto específico de la ruta (por ejemplo, el criterio de cruces por `jω` para tu caso concreto, o cómo validar el caso inestable contra la teoría)?

## User

mañana tengo que proponer un plan de trabajo para mi asesor el dia de mañana , tengo que salvar mi pellejo demostrando algo para la primera semana de diciembre. seriamente

## DeepSeek

# Plan de trabajo para el asesor: simulador de sistemas lineales con retardo e inestabilidad compleja

**Objetivo central:** Demostrar, en la primera semana de diciembre, un simulador funcional que reproduzca correctamente la dinámica de un lazo con retardo y polos complejos conjugados en el semiplano derecho. La meta no es un producto terminado, sino una **prueba de concepto validada** que justifique el proyecto y asegure tu posición.

La estrategia es evitar la sobreingeniería. El camino más corto y defendible técnicamente es implementar el **método de pasos** (method of steps) para el retardo, acoplado a un integrador Runge-Kutta de cuarto orden (RK4) para la dinámica de la planta. Esto es suficiente para tu caso y es matemáticamente sólido.


## 1. Justificación técnica (lo que dirás al asesor)

El problema que abordas no requiere un solver implícito ni un tratamiento de ecuaciones diferenciales algebraicas (DAE). La razón es directa:

- **La planta (StateSpace)** tiene estado propio. Su salida en el instante actual depende de su estado interno, no de una combinación instantánea de su propia salida. Esto rompe cualquier ciclo algebraico.
- **El retardo (Delay)** es, por definición, un buffer de historia. La señal que entrega en `t` es la que recibió en `t-T`. Tiene memoria, por lo tanto también rompe ciclos instantáneos.
- **El lazo cerrado** con estos dos elementos es topológicamente acíclico si se evalúa en orden: primero se lee la historia del retardo, se calcula la acción de control, se integra la planta, y se escribe el nuevo valor en el buffer. No hay circularidad.

El método de pasos formaliza esto: para `t < T`, el retardo usa la función de historia inicial; para `t ≥ T`, usa valores ya calculados. La implementación práctica es un **buffer circular (FIFO)** [citation:2]. El paso de integración `dt` debe dividir exactamente a `T` (o interpolarse, pero para la demo puedes exigir `T/dt` entero).


## 2. Alcance concreto para el 5 de diciembre (lo que prometerás)

No prometas el simulador completo. Promete esto:

**Un script en Python que:**
1. Defina una planta en espacio de estados con una matriz `A` cuyos autovalores sean un par complejo conjugado con parte real positiva (ej. `λ = 0.5 ± 2j`).
2. Defina un retardo `T` en la realimentación de la salida.
3. Simule el lazo cerrado con RK4 y buffer FIFO.
4. Genere una gráfica de `y(t)` donde se observe el crecimiento oscilatorio.
5. **Valide** ese crecimiento contra la teoría: la tasa de crecimiento exponencial en la fase lineal debe coincidir con la parte real del polo dominante de la ecuación característica trascendente.

**Entregable tangible:** un repositorio (o carpeta) con `simulador.py`, `validacion.py` y un README de media página con la gráfica y la comparación numérica.


## 3. Cronograma inverso (del 9 de noviembre al 5 de diciembre)

| Fecha límite | Entregable | Criterio de éxito |
|---|---|---|
| **Vie 14 nov** | Planta `StateSpace` con RK4 + validación contra `scipy.signal.lsim` para `T=0`. | La respuesta al escalón coincide con `scipy` a `~1e-6`. Si esto falla, no sigas. |
| **Mié 19 nov** | Buffer `Delay` con FIFO + validación: un impulso inyectado en `t=0` emerge intacto en `t=T`. | La señal retardada es idéntica a la original desplazada. |
| **Vie 21 nov** | Lazo cerrado planta+retardo. Primeras gráficas. | La simulación corre sin errores y produce una trayectoria. |
| **Mar 25 nov** | **Validación teórica del caso inestable.** Extraer la tasa de crecimiento de la simulación y compararla con `Re(polo dominante)` de `1 + G(s)e^{-sT}=0`. | Diferencia < 10% en la tasa de crecimiento. Este es el hito que salva el pellejo. |
| **Vie 28 nov** | Documentación y limpieza del código. README con la gráfica clave. | El asesor puede leer y entender qué se hizo y por qué funciona. |
| **Lun 1 – Mié 3 dic** | Colchón para imprevistos. Ensayo de la presentación. | Llegar al 5 dic con margen. |


## 4. Fundamento teórico mínimo (lo que necesitas saber para defenderlo)

No necesitas leer los libros completos antes de diciembre. Necesitas dominar **tres conceptos**:

**a) La ecuación característica trascendente.** Para tu lazo `G(s) = N(s)/D(s)` con realimentación `e^{-sT}`, la estabilidad está dada por las raíces de `1 + G(s)e^{-sT} = 0`. Esta ecuación tiene infinitas raíces. La que tenga mayor parte real domina el crecimiento. Tu simulación debe reproducir esa parte real [citation:3].

**b) Cruces por el eje imaginario.** Los valores críticos de `T` donde el sistema pasa de estable a inestable (o viceversa) son aquellos para los cuales existe una raíz `s = jω`. Sustituyes `s = jω` en la ecuación característica, separas parte real e imaginaria, y resuelves para `ω` y `T`. Esto te da la frontera de estabilidad. No necesitas implementarlo en el simulador para diciembre, pero **debes poder explicarlo** si el asesor pregunta "¿cómo sabes que tu simulación es correcta y no solo un artefacto numérico?" [citation:3][citation:6].

**c) Estabilidad numérica vs. estabilidad del sistema.** Con polos inestables, un Euler explícito con `dt` grande puede divergir *artificialmente* (inestabilidad numérica) y confundirte. RK4 tiene una región de estabilidad mucho más amplia, pero igual necesita `dt` razonable. Regla práctica: `dt < 0.1/|λ_max|`. Si tu simulación diverge más rápido que `e^{Re(λ)t}`, es bug numérico, no física.


## 5. Riesgos y mitigaciones (lo que dirás si el asesor presiona)

| Riesgo | Probabilidad | Mitigación |
|---|---|---|
| RK4 no coincide con `scipy` en la primera semana | Media | Reducir `dt`, verificar convención de signos en `A`, comparar con un caso 1D trivial primero. |
| El buffer de retardo tiene un offset de un índice | Alta | Test unitario: impulso en `t=0`, verificar que sale en `t=T`. Ajustar el buffer hasta que pase. |
| La tasa de crecimiento simulada no coincide con la teoría | Media | Puede ser `dt` grande (artefacto numérico) o que la fase lineal es demasiado corta. Ajustar `dt` y ventana de ajuste exponencial. |
| El asesor pregunta por LMI o Lyapunov-Krasovskii | Baja (para diciembre) | Responder: "Para la prueba de concepto uso el método de pasos, que es exacto para retardo constante. Las condiciones LMI son el siguiente paso teórico, pero no son necesarias para validar la simulación." |


## 6. Lo que NO harás (y por qué)

- **No implementarás el solver implícito.** No lo necesitas: el retardo y la planta tienen estado.
- **No harás una GUI ni un editor de grafos.** El `matplotlib` básico es suficiente para la demo.
- **No leerás Fridman ni Gu completos.** Consultarás el capítulo de estabilidad de sistemas lineales con retardo solo si necesitas la fórmula del cruce por `jω`.
- **No prometerás "aprender a full" la teoría para diciembre.** Prometerás una **prueba de concepto validada** y un **plan de profundización teórica** para enero en adelante.


## 7. Resumen de una frase para el asesor

> "En tres semanas implemento un simulador mínimo de un lazo con retardo usando el método de pasos y RK4, valido la planta contra `scipy`, y demuestro que la tasa de crecimiento simulada de un sistema con polos complejos inestables coincide con la predicción de la ecuación característica trascendente. El objetivo es tener una base numérica sólida antes de profundizar en la teoría de estabilidad de sistemas con retardo."

Eso es defendible, acotado, y demostrable el 5 de diciembre.
