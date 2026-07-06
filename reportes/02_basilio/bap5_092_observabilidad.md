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
\caption{Observador de Luenberger. $L(y-C\hat{x})$ es una retroalimentación del observador. No del sistema.}
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

La matriz $L$ es la matriz de *ganancia del observador*, se encarga de ponderar el error de salida para corregir la estimación de estados. Dicho de otro modo: La matriz $L$ determina la intensidad con la que el error entre la salida medida y la salida estimada corrige la estimación de los estados. Su elección fija la dinámica del error de estimación, ya que los polos del observador corresponden a los autovalores de la matriz $(A−LC)$. Esta corrección puede interpretarse como una ***inyección*** estática del error de salida en la dinámica del observador.


En resumen, el observador sigue continuamente tres pasos:

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

\newpage

### Matriz de Observabilidad


Para reconstruir los estados internos, las salidas medidas deben contener suficiente información acerca del estado del sistema. Esta propiedad recibe el nombre de 
**observabilidad**. Consideremos el sistema lineal continuo:

```{=latex}
\[
\begin{aligned}
\dot{x} &= Ax + Bu,\\
y &= Cx.
\end{aligned}
\]
```

A partir de la ecuación de salida. Si la matriz $C$ no mide directamente todos los estados, es necesario obtener información adicional a partir de la evolución temporal de la salida.
Derivando la ecuación de salida:

```{=latex}
\[
\dot{y}=C\dot{x}
\]
```

Sustituyendo el modelo dinámico del sistema,


```{=latex}
\[
\begin{aligned}
\dot{y}&=C(Ax+Bu)\\
&=\boxed{CAx}+CBu
\end{aligned}
\]
```

Obsérvese que la primera derivada de la salida ya no depende únicamente de la matriz $C$, sino que también introduce el producto $CA$, proporcionando nueva información sobre el estado del sistema. Derivando nuevamente,

```{=latex}
\[
\ddot{y}
=CA\dot{x}+CB\dot{u}.
\]
```

y sustituyendo una vez más,

```{=latex}
\[
\begin{aligned}
\ddot{y}&=CA(Ax+Bu)+CB\dot{u}\\
\ddot{y}&=\boxed{CA^2x}+CABu+CB\dot{u}
\end{aligned}
\]
```
\newpage
Cada nueva derivada incorpora una potencia adicional de la matriz $A$:

```{=latex}
\[
\begin{aligned}
y      &= Cx,\\
\dot{y}&= CAx+\cdots,\\
\ddot{y}&= CA^2x+\cdots,\\
&\ \vdots\\
y^{(n-1)}&=CA^{n-1}x+\cdots
\end{aligned}
\]
```

donde los términos indicados mediante *"..."* dependen de la entrada $u$ y de sus derivadas, las cuales se consideran conocidas. Agrupando únicamente los términos que dependen del estado, se obtiene:

```{=latex}
\[
\begin{bmatrix}
y\\
\dot{y}\\
\ddot{y}\\
\vdots\\
y^{(n-1)}
\end{bmatrix}
=
\underbrace{
\begin{bmatrix}
C\\
CA\\
CA^2\\
\vdots\\
CA^{n-1}
\end{bmatrix}
}_{\mathcal{O}}
x
+\text{(términos conocidos)}.
\]
```	

La matriz

```{=latex}
\[
\mathcal{O}=
\begin{bmatrix}
C\\
CA\\
CA^2\\
\vdots\\
CA^{n-1}
\end{bmatrix}
\]
```

se denomina matriz de observabilidad. Si esta matriz tiene rango completo,

```{=latex}
\[
\boxed{\operatorname{rank}(\mathcal{O})=n}
\]
```
entonces el estado inicial del sistema puede reconstruirse de forma única a partir de las entradas conocidas y de las salidas medidas. En consecuencia, el sistema se dice ***completamente observable***.

\newpage
Maestra Nancy

Converse con el Dr.
me señalo que mi calificacion no aprobatoria corresponde a una
cuestión de actitud de mi parte. Me dijo que reconoce 
mis capacidades técnicas y acádemicas
Yo comprendo su punto pero discrepo.

Yo por mi parte le solicite que no utilizara palabras 
Si bien preferiria una relación mas relajada
considero que 
esta muy arraigado en esta institucion el trato
despotico. No es raro el caso 
del Dr.








