## Clases de Dr. Basilio


La ecuación caracteristica de un sistema de segundo orden se escribe como:

```{=latex}
\begin{equation}
\begin{aligned}
s^2 + 2\zeta \omega_n s + \omega_n^2 = 0
\end{aligned}
\end{equation}
```

Sus polos son:
\
```{=latex}
\begin{equation}
\begin{aligned}
s = -\zeta \omega_n \pm j\,\omega_n \sqrt{1 - \zeta^2}
\end{aligned}
\end{equation}
```
\

* El denominador de la función de transferencia define la ecuación característica

* La ecuación característica define los polos

* Los polos definen el comportamiento del sistema


**Ejemplo:** Sea el siguiente sistema en lazo abierto, diseñar un control por retroalimentación
estatica de la salida. Es decir, una ganancia constante que retroalimente la salida

```{=latex}
\begin{equation}
\begin{aligned}
G(s) = \frac{1}{s^2 + 4s + 1}
\end{aligned}
\end{equation}
```

El root locus analiza cómo cambian los polos del sistema en lazo cerrado al variar la ganancia K, partiendo de la función G(s) en trayectoria directa y asumiendo retroalimentación unitaria.
