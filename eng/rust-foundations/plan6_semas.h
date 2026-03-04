ETAPA 0 — Mentalidad Rust (1–2 días)

Antes de código complejo, entiende esto:

Rust no trata sobre:

sintaxis

punteros

rendimiento

Rust trata sobre:

modelos de propiedad

garantías en tiempo de compilación

invariantes del programa

Lee y entiende profundamente:

¿Qué es ownership?

¿Qué problema resuelve?

¿Por qué no hay GC?

¿Por qué no hay null?

🔹 ETAPA 1 — Ownership y Borrowing (La base real)

Este es el 60% de Rust.

Debes dominar:

Move semantics

&T vs &mut T

Borrow checker

Dangling references

Stack vs heap

Drop

Ejercicios recomendados:

Implementar funciones que:

toman ownership

toman referencia

retornan referencia

Jugar con:

let s1 = String::from("hola");
let s2 = s1;

Romper el compilador intencionalmente.

Tu meta:
👉 Entender por qué el error ocurre.

🔹 ETAPA 2 — Structs, Enums y Pattern Matching

Aquí empiezas a pensar en diseño.

Domina:

struct

impl

métodos asociados

enum con datos

match exhaustivo

if let

while let

Ejercicio clave:
Implementar un pequeño sistema de estados con enum.

🔹 ETAPA 3 — Result y Option (Diseño profesional)

Rust se vuelve elegante aquí.

Debes dominar:

Option<T>

Result<T, E>

?

map / and_then

error propagation

Ejercicio serio:
Construir una mini CLI que:

lea archivo

parse contenido

maneje errores correctamente

🔹 ETAPA 4 — Traits (Aquí empieza el nivel intermedio)

Esto es fundamental.

Domina:

trait

impl Trait for Type

trait bounds

generics

where clauses

Default / Debug / Clone / Copy

Ejercicio:
Crear un trait propio y aplicarlo a varios tipos.

🔹 ETAPA 5 — Lifetimes (Sin miedo)

No memorices reglas.

Entiende:

qué problema resuelven

cuándo el compilador las infiere

lifetime elision

referencias en structs

Ejercicio:
Implementar una función que retorna referencia con lifetime explícito.

🔹 ETAPA 6 — Collections y Smart Pointers

Domina:

Vec

HashMap

Box

Rc

Arc

RefCell

Aquí empiezas a entender:
Interior mutability.

🔹 ETAPA 7 — Concurrencia básica

Rust brilla aquí.

Domina:

thread::spawn

move closures

Arc + Mutex

Send y Sync

Ejercicio:
Programa multi-thread que comparte estado correctamente.

🔹 ETAPA 8 — Ecosistema real

Ahora sí:

serde

reqwest

tokio (async)

clap (CLI)

tracing

Construye algo real:

CLI que consuma API

mini servidor

parser de logs

📚 Recursos correctos (orden recomendado)

The Rust Book (oficial)

Rust by Example

Rustlings (ejercicios interactivos)

Escribir proyectos reales

No dependas solo de videos.

🧠 Método de aprendizaje óptimo

Haz esto:

30% lectura

70% escribir código

Rompe cosas intencionalmente

Lee errores del compilador con atención

El compilador es tu profesor.

🏗 Plan de 6 semanas realista

Semana 1:
Ownership + Borrowing

Semana 2:
Structs + Enums + Pattern Matching

Semana 3:
Result + Traits

Semana 4:
Lifetimes + Generics

Semana 5:
Smart pointers + Concurrency

Semana 6:
Proyecto real

⚠️ Errores comunes que debes evitar

❌ Intentar aprender async demasiado pronto
❌ Copiar código sin entender ownership
❌ Frustrarte con lifetimes
❌ Pensar en Raspberry antes de dominar base

🎓 Cómo sabes que ya tienes bases sólidas

Puedes:

Explicar ownership sin mirar libro

Diseñar un struct sin dudar

Resolver errores de borrow sin pánico

Usar Result correctamente

Entender cuándo usar & vs &mut

🚀 Siguiente paso inmediato

Si quieres empezar ya mismo, te propongo:

Te doy un micro–ejercicio progresivo de ownership
y lo resolvemos juntos paso a paso.

Eso es mucho más efectivo que teoría sola.

¿Quieres empezar con eso ahora?