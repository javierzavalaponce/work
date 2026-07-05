```{=latex}
\clearpage
```

### Observabilidad

La realimentación de estados requiere conocer el vector de estados $x$. Sin embargo, en muchos sistemas sólo es posible medir algunas salidas mediante sensores. En estos casos es necesario estimar los estados internos mediante un observador.

Existe una propiedad del sistema denominada ***observabilidad***, que determina si los estados internos pueden reconstruirse únicamente a partir de la entrada y de las salidas medidas. En otras palabras, un *sistema observable* contiene suficiente información en sus salidas para reconstruir completamente su estado interno.

El *observador* es un modelo del sistema que corre en paralelo, 
pero que se corrige continuamente con el error entre la salida real y la salida estimada.
Es útil cuando los estados internos del sistema no pueden medirse directamente mediante sensores.
La observabilidad responde a esta pregunta: *¿Puedo confiar en lo que creo que sé de mi sistema?*


Partiendo de un modelo de sistema como:

```{=latex}
\begin{equation}
\begin{aligned}
\label{eq:sist00}
\dot{x}&=Ax + Bu \\
y&=Cx
\end{aligned}
\end{equation}
```

Si el observador fuera únicamente una copia del modelo y además partiera del mismo estado inicial que el sistema, produciría exactamente la misma evolución. En la práctica esto rara vez ocurre, ya que normalmente el estado inicial del sistema es desconocido.

```{=latex}
\[
\begin{aligned}
\dot{\hat{x}}&=A\hat{x} + Bu \\
\hat{y}&=C\hat{x}
\end{aligned}
\]
```
Entonces, la salida real del sistema es $y=Cx$ y la salida del observador es $\hat{y}=C\hat{x}$. La diferencia (el *error*) es:

```{=latex}	
\[
e_y = y-\hat{y}=y-C\hat{x}
\]
```

\newpage

El observador no puede comparar estados porque los estados reales son *desconocidos* (dentro de la caja punteada). Ver figura. Pero sí puede comparar salidas, porque la salida real sí está disponible:

\begin{figure}[H]
\centering
\includegraphics[width=1.0\textwidth,trim=0cm 4cm 0cm 5cm,clip]{../img/observabilidad.pdf}
\caption{$L(y-C\hat{x})$ es una retroalimentación del observador. No del sistema.}
\end{figure}



```{=latex}
\begin{equation}
\begin{aligned}
\label{eq:sist01}
\dot{\hat{x}}&=A\hat{x} + Bu + L(y-C\hat{x})\\
\hat{y}&=C\hat{x}
\end{aligned}
\end{equation}
```

Si el error de salida $e_y$ es distinto de cero, el observador debe corregir su estimación.


Por esta razón se añade un término de corrección: $L(y-C\hat{x})$, el término $(y-C\hat{x})$ representa el error entre la salida real y la salida estimada. La matriz $L$ transforma dicho error en una señal de corrección que se incorpora a la dinámica del observador.  


El observador sigue continuamente tres pasos:

* Predice el comportamiento mediante el modelo.
* Compara la salida estimada con la salida real.
* Corrige la estimación utilizando el error de salida.

\newpage

#### Dinámica del error de estimación. 

El error de estimación: $e=x-\hat{x}$ representa la diferencia entre el estado real y el estado estimado por el observador:

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth,trim=0cm 5cm 0cm 5cm,clip]{../img/observabilidad01.pdf}
\caption{Error de estimación $(x-\hat{x})$}
\end{figure}


Obteniendo la *dinámica del error*, (la derivada, simplemente). Sustituyendo las ecuaciones \ref{eq:sist00} y \ref{eq:sist01} del sistema y del observador en 
 $\dot{e}=\dot{x}-\dot{\hat{x}}$


```{=latex}	
\[
\dot{e} = Ax + Bu - A\hat{x} - Bu - L(y-C\hat{x}) 
\]
```




```{=latex}
\begin{equation}
\begin{aligned}
\dot{e} &= Ax - A\hat{x} - L(Cx-C\hat{x}) \\
 &= A(x - \hat{x}) - LC(x-\hat{x}) \\
 &= Ae - LCe
\end{aligned}
\end{equation}
```


En conclusión, el error de estimación se comporta como un sistema dinámico independiente cuya evolución depende únicamente de la matriz $(A−LC)$

```{=latex}	
\[
\boxed{\dot{e} = (A - LC)e}
\]
```

El problema del diseño del observador consiste entonces en elegir la matriz $L$ de forma que la dinámica del error sea estable. En otras palabras: si los
valores propios de $(A - LC)$ tienen parte real negativa, el error tenderá a $0$. 

### Matriz de Observabilidad

Para reconstruir los estados internos, las salidas medidas deben contener suficiente información acerca del estado del sistema. Esta propiedad recibe el nombre de 
**observabilidad**. Tomemos nuevamente la ecuación de salida:

```{=latex}
\[
y=Cx
\]
```
Derivandola,

```{=latex}
\[
\dot{y}=C\dot{x}
\]
```

Sustituyendo el modelo dinámico del sistema,

```{=latex}
\[
\dot{x}=Ax+Bu
\]
```

```{=latex}
\[
\dot{y}=C(Ax+Bu)=CAx+CBu.
\]
```

Si la información disponible aún no fuera suficiente, podría derivarse nuevamente la salida.
La segunda derivada conduce a términos que contienen la matriz

```{=latex}
\[
CA^2.
\]
```


