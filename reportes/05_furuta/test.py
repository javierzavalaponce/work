import pybullet as p

# Intenta obtener la versión por varios métodos
try:
    ver = p.getVersion()
    major = ver // 1000
    minor = (ver // 100) % 10
    patch = ver % 100
    print(f"PyBullet versión (getVersion): {major}.{minor}.{patch}")
except AttributeError:
    try:
        import importlib.metadata
        print("PyBullet versión (pip):", importlib.metadata.version("pybullet"))
    except Exception:
        print("No se pudo obtener la versión. Atributos disponibles:")
        print([attr for attr in dir(p) if not attr.startswith("_")])


