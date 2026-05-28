## Espacio y estados (control moderno)

### Ejercicio


Encuentre la representacion en espacio de estados del siguiente sistema:


```{=latex}
\begin{equation}
\begin{aligned}
\frac{Y(s)}{U(s)} = \frac{(s+1)(s+2)}{(s-1)(s-2)}
\end{aligned}
\end{equation}
```

Una de varias alternativas de solución sería
separar la ecuacion de esta manera:



```{=latex}
\begin{equation}
\begin{aligned}
\frac{Y(s)}{U(s)} = G_1(s) G_2(s) = \frac{(s+1)}{(s-1)} \cdot \frac{(s+2)}{(s-2)}
\end{aligned}
\end{equation}
```


\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth,trim=0cm 8cm 0cm 5cm,clip]{./img/espacio_edos00.pdf}
\caption{Alternativamente en bloques}
\label{fig:ejercicio_espedos0}
\end{figure}


Para $G_1$ utilizando variable auxiliar $W(s)$:

```{=latex}
\begin{equation}
\begin{aligned}
G_1(s) = \frac{Y_1(s)}{U_1(s)} = \frac{(s+1)}{(s-1)} \cdot  \frac{W(s)}{W(s)}
\end{aligned}
\end{equation}
```

Aplicando transformada inversa: 

```{=latex}
\begin{equation}
\begin{aligned}
\mathcal{L}^{-1}\{Y_1(s)\} = \mathcal{L}^{-1}\{sW(s)+W(s)\} = \boxed{y_1 = \dot{w}+w}
\end{aligned}
\end{equation}
```

Para $U_1$
```{=latex}
\begin{equation}
\begin{aligned}
\mathcal{L}^{-1}\{U_1(s)\} = \mathcal{L}^{-1}\{sW(s)-W(s)\} = u_1 = \dot{w}-w
\end{aligned}
\end{equation}
```

O bien:

```{=latex}
\begin{equation}
\begin{aligned}
\boxed{\dot{w} = u_1+w}
\end{aligned}
\end{equation}
```


Analogamente, para $G_2$ utilizando variable auxiliar $W_2(s)$:


```{=latex}
\begin{equation}
\begin{aligned}
G_2(s) = \frac{Y_2(s)}{U_2(s)} = \frac{(s+2)}{(s-2)} \cdot  \frac{W_2(s)}{W_2(s)}
\end{aligned}
\end{equation}
```

Aplicando transformada inversa: 


```{=latex}
\begin{equation}
\begin{aligned}
\mathcal{L}^{-1}\{Y_2(s)\} = \mathcal{L}^{-1}\{sW_2(s)+2W_2(s)\} = \boxed{y_2 = \dot{w_2}+2w_2}
\end{aligned}
\end{equation}
```

Para $U_1$
```{=latex}
\begin{equation}
\begin{aligned}
\mathcal{L}^{-1}\{U_2(s)\} = \mathcal{L}^{-1}\{sW_2(s)-2W_2(s)\} = u_2 = \dot{w_2}-2w_2
\end{aligned}
\end{equation}
```


O bien:

```{=latex}
\begin{equation}
\begin{aligned}
\boxed{\dot{w_2} = u_2+2w_2}	
\end{aligned}
\end{equation}
```



\newpage
