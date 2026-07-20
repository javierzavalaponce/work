curl -fsSL https://ollama.com/install.sh | sh

 curl -fsSL https://ollama.com/install.sh | sh
 ollama pull llama3.2:3b
 ollama run llama3.2:3b "Soy un investigador novato. Dame 5 consejos para leer papers científicos de forma eficiente"
 ollama pull nomic-embed-text


implementar un RAG completamente "a mano" usando:

sentence-transformers para embeddings,
FAISS como índice vectorial,
Ollama como LLM local.


