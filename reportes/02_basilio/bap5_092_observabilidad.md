```{=latex}
\clearpage
```

### Observabilidad

La retrolimentación de estados no siempre es posible.
El *observador* es un modelo del sistema que corre en paralelo, 
pero que se corrige continuamente con el error entre la salida real y la salida estimada.
Es para aquellos casos en que los estados internos no estan disponibles.
La observabilidad responde a esta pregunta: *¿Puedo confiar en lo que creo que sé de mi sistema?*


Partiendo de un modelo de sistema como:

```{=latex}
\[
\begin{aligned}
\dot{x}&=Ax + Bu \\
y&=Cx
\end{aligned}
\]
```

Si el observador fuera únicamente una copia del modelo:

```{=latex}
\[
\dot{\hat{x}}=A\hat{x} + Bu 
\]
```
entonces produciría exactamente la misma evolución que el modelo inicial.

La salida real del sistema es $y=Cx$ y la salida estimada es $\hat{y}=C\hat{x}$.
La diferencia es:

```{=latex}
\[
e_y = y-\hat{y}=y-C\hat{x}.
\]
```

si el error de salida $e_y$ es distinto de cero, el observador debe corregir su estimación.
Por esta razón se añade un término de corrección: $L(y-C\hat{x})$,
Este término compara continuamente la salida medida del sistema con la salida que predice el observador.


```{=latex}
\[
\begin{aligned}
\dot{\hat{x}}&=A\hat{x} + Bu + L(y-C\hat{x})\\
\end{aligned}
\]
```

El término $L(y-C\hat{x})$ es una realimentación del observador. No es una realimentación del sistema físico.

\newpage


El observador no puede comparar estados $(x-\hat{x})$, porque los estados reales son *desconocidos*. 
Pero sí puede comparar salidas, porque la salida real sí está disponible:

\begin{figure}[H]
\centering
\includegraphics[width=1.0\textwidth,trim=0cm 4cm 0cm 4cm,clip]{../img/observabilidad.pdf}
\caption{Modelo y observador}
\end{figure}


#### Pausa de reflexión:

Supongamos un sistema con 3 estados $(x_1,x_2,x_3)$ y una única salida $y$

***Conclusión:*** $L$ tiene las dimensiones transpuestas de $C$
