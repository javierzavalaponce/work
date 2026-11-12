# To-do lista:


1. Que la input soporte espacios y comas en modo texto
2. entender bien lo que paas con webapp
3. que webapp pueda detectar tanto espacios como comas
4. terminar version en local deb13
5. pasar a rpi
6. montar en remoto

# Todos
[ ] Paso 3: romper una prueba a propósito para aprender a leer fallos de pytest
[ ] Paso 4: más pruebas de resultados (1/s, (s+1)/(s+2) con D≠0, den no mónico)
[ ] Paso 5: pruebas de errores con pytest.raises
[ ] Paso 6: probar leer_coeficientes con monkeypatch
[ ] Declarar dependencias en el repo (requirements.txt o pyproject.toml), con versiones probadas: numpy 2.5.x, pytest 9.1.x, Python 3.13
[ ] Crear .gitignore (__pycache__, .pytest_cache, .venv)
[ ] README + guía de usuario: clonar, crear venv, instalar dependencias, ejecutar programa, ejecutar pruebas (usuario es quien clona, no usa su venv personal)
[ ] Más adelante: instalación en un solo comando desde GitHub (pipx / install.sh)



Lo que quedó apuntado
Para la guía de usuario, cuando llegue el momento, el README cubrirá:
1. Requisitos (Python 3.13 probado).
2. Clonar el repo y crear un entorno virtual propio (python -m venv .venv).
3. Instalar dependencias con un solo comando (necesita un requirements.txt o pyproject.toml, que aún no existen).
4. Ejecutar el programa y un ejemplo de uso, con la salida esperada.
5. Ejecutar las pruebas.
6. Qué hacer si algo falla. Aquí entrarán los problemas que ya vimos: el venv equivocado y ejecutar desde la carpeta equivocada.
Esa guía la escribiremos al final, cuando el proyecto esté más completo. Así no habrá que rehacerla.
Una nota: la prueba pasó con NumPy 2.5.0 y pytest 9.1.1. Esas versiones irán en las dependencias como las probadas.
Siguiente paso
Como ya usas tu venv con pytest, puedes ir directamente al paso 3, ejecutando siempre desde ~/mytf2ss. Es romper una prueba a propósito para aprender a leer un fallo. Sería cambiar un número esperado en tu test, por ejemplo el -2 de A por -5, y ejecutar:
python -m pytest -v
Antes de hacerlo, intenta predecir qué mensaje aparecerá y en qué posición de la matriz señalará el error. Luego me cuentas qué viste y lo analizamos juntos. ¿Lo haces tú, o prefiero ejecutarlo yo y explicarte la salida?

-----


