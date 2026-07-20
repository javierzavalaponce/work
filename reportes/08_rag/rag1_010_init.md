```{=latex}
\clearpage
```

# Introducción, mapa de avance

Retrieval-Augmented Generation (RAG)

El plan de trabajo consistirá en construir un sistema RAG desde sus componentes más básicos. 
Desde la lectura de los documentos hasta la recuperación de información relevante y la generación de respuestas fundamentadas en ese conocimiento.

0. A partir de uno o varios documento PDF, se extrae y divide el texto en pequeños fragmentos
con $pypdf$.
* Tamaño del fragmento: 500 caracteres(tokens..)
* Solapamiento (overlap): 100 caracteres

1. Se convierte cada fragmento en un vector numérico ($embedding$) usando sentence-transformers (texto $\rightarrow$ vectores). Estos vectores representan el significado semántico del texto. 

2. Construir un índice vectorial usando $HNSWlib$ que permita recuperar los fragmentos más similares a una consulta.

3. Recuperar los k fragmentos más similares.

Construir un prompt compuesto por:

* instrucciones
* contexto recuperado
* pregunta del usuario

Enviar ese prompt al LLM (llama-cpp-python)

# Bitácora de implementación RAG - Proyecto "a mano"

**Fecha de inicio:** [Pon tu fecha]
**Objetivo:** Construir un sistema RAG (Retrieval-Augmented Generation) desde cero, usando únicamente herramientas locales y acopladas directamente en Python, sin orquestadores externos (como LangChain) ni bases de datos pesadas.

---

## 1. Decisión Arquitectónica (El qué y el por qué)

- **Embeddings:** `sentence-transformers` (por su facilidad para generar vectores semánticos en local).
- **Índice Vectorial:** `hnswlib` (porque es liviano, corre en memoria, se guarda en un archivo `.bin` y no necesita instalar servidores externos como PostgreSQL). *Descarto pgvector para esta fase para mantener el foco en el algoritmo de RAG.*
- **LLM Local:** `llama-cpp-python` (por su eficiencia en CPU y soporte para modelos GGUF).

---

## 2. Mapa de Avance (Plan de trabajo detallado)

El flujo se divide en 3 grandes fases: **Indexación (offline)**, **Búsqueda (online)** y **Generación (online)**.

### FASE 0: Preparación del corpus (Pre-procesamiento)

- **0.1 Extracción de texto**: Usaré `pypdf` para leer los PDFs y extraer todo el texto plano.
- **0.2 Fragmentación estratégica (Chunking)**: 
  - No dividiré por páginas, sino por bloques semánticos.
  - **Tamaño del fragmento:** `512` caracteres (para que quepan bien en el contexto del LLM).
  - **Solapamiento (Overlap):** `50` caracteres. Esto evita que las oraciones se corten a la mitad y se pierda el contexto entre fragmentos contiguos.
  - *(Herramienta: escribiré una función manual con `textwrap` o usaré el `RecursiveCharacterTextSplitter` de LangChain únicamente para esta tarea auxiliar, pero sin arrastrar todo el ecosistema LangChain).*

---

### FASE 1: Indexación (Convertir texto a vectores y almacenarlos)

- **1.1 Modelo de Embeddings:** Usaré `all-MiniLM-L6-v2` de `sentence-transformers`. 
  - *Razón:* Genera vectores de 384 dimensiones, es rápido y tiene buena calidad para un prototipo en CPU.
- **1.2 Generación de vectores:** Pasaré todos los fragmentos de texto por el modelo para obtener una matriz de numpy de tamaño `(cantidad_fragmentos, 384)`.
- **1.3 Construcción del índice HNSW:**
  - Inicializaré el índice con la dimensión 384 y la métrica de similitud `cosine` (o `l2`).
  - Añadiré los vectores al índice.
  - **Guardaré el índice en disco** usando `index.save_index("mi_hnsw_index.bin")` para no tener que re-indexar cada vez que ejecute el programa.

---

### FASE 2: Recuperación (Búsqueda de contexto relevante)

- **2.1 Carga del índice:** Al iniciar el chat, cargaré `mi_hnsw_index.bin` en memoria.
- **2.2 Conversión de la pregunta:** Cuando el usuario haga una pregunta, la pasaré por el mismo `sentence-transformers` para convertirla en vector (embedding).
- **2.3 Búsqueda por similitud:** Usaré `index.knn_query()` para obtener los `top_k = 4` fragmentos más parecidos a la pregunta.
- **2.4 Gestión del contexto (Token Management):** 
  - Como mi modelo local (ej. `Llama-2-7B.Q4_K_M`) tiene un contexto limitado (ej. 4096 tokens), implementaré una lógica que mida los tokens de los fragmentos recuperados y los trunque (cortando por el medio) si suman más de `2000` tokens, dejando espacio para la pregunta y la instrucción del sistema.

---

### FASE 3: Generación (Respuesta del LLM)

- **3.1 Construcción del Prompt:** Usaré una plantilla estricta para que el LLM **no alucine**. El prompt tendrá este formato exacto:


## pypdf
