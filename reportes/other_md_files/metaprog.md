#### Metaprogramacion: El código que escribe código

La **metaprogramación** es una técnica
donde un programa tiene la capacidad de tratarse a si mismo yu a otros programas como datos, pudiendo generar, analizar o modificar código en tiempo de compilación o ejecución.

```c
;; En Common Lisp, una macro simple
(defmacro cuando (condicion &body cuerpo)
  `(if ,condicion (progn ,@cuerpo)))
```
Decoradores en python:

```python
def loggear(funcion):
	asdf
	asdf
	asdf

    def envoltura(*args, **kwargs):
        print(f"Llamando a {funcion.__name__}")
        return funcion(*args, **kwargs)
    return envoltura

@loggear
def saludar(nombre):
    print(f"Hola {nombre}")


```

Templates en C++

```c
template<int N>
struct Factorial {
    static const int valor = N * Factorial<N-1>::valor;
};

template<>
struct Factorial<0> {
    static const int valor = 1;
};
// Factorial<5>::valor se calcula en tiempo de compilación
```

\newpage



