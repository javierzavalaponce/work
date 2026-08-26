```{=latex}
\clearpage
```


## Ejercicio 2: Analisis espectral

1. Generar un archivo *.wav* de tres segundos de duración

```{=latex}
\[
\begin{aligned}
x(t) &= x_1(t) + x_2(t) + x_3(t) \\
x_1(t) &= 10080sin(2 \pi 180t) \\
x_2(t) &= 11520sin(2 \pi 234t) \\
x_3(t) &= 2240sin(2 \pi 360t) \\
\end{aligned}
\]
```

 o bien:

```{=latex}
\[
x(t)=10080sin(2 \pi 180t)+11520sin(2 \pi 234t) + 2240sin(2 \pi 360t)
\]
```

2. Muestrear a 1Khz. Detectar la componente de 180 Hz 
   (proyectar la señal sobre un subespacio generado por una sinusoide)


Si solamente observo $x(t)$, ¿cómo puedo recuperar $x_1(t)$?
haciendo un producto interno con una señal de referencia de 180 Hz.


Arduino $F_s$ a 1000Hz


Entonces ya no vamos a trabajar directamente con $x(t)$, sino con:

$x[n] = x(nT_s)$

```{=latex}
\[
\begin{aligned}
T_s &= \frac{1}{F_s} \\
T_s &=\frac{1}{1000} \\
T_s &= 0.001s
\end{aligned}
\]
```


nota $180 \less 500$, $234 \less 500$, $360 \less 500$

Por tanto, las tres componentes pueden ser muestreadas.

Hasta aquí todo perfecto.

```{=latex}
\[
x[n]=10080sin(2 \pi 180 \frac{n}{1000})+11520sin(2 \pi 234 \frac{n}{1000}) + 2240sin(2 \pi 360 \frac{n}{1000})
\]
```

Vamos a construir un detector de 180 Hz.


ayuda. es un ejercicio para practicar y aprender fft y dft, por favor ayudame 
quiero procesar esto en un arduino con isr a 1Kilihert
me interesa aprender
y de ser posible vincular con lo que he estado viendo de analisis funcional

quiero saber como calcular senos en arduino de la manera mas eficiente tipo industria DSP . busco aprender al maximo ilumina mi camino


8484: neta?
Quieres extraer la componente de 180 Hz. Esto es un proyector en un espacio de Hilbert:

