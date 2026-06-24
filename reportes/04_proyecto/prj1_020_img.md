```{=latex}
\clearpage
```
# Diagrama general: banco de controladores

La siguiente figura representa dentro de la linea punteada el 
bando de controladores, se presenta un diagrama reducido por claridad:

\begin{figure}[H]
\centering
\includegraphics[width=1.0\textwidth,trim=0cm 3cm 0cm 3cm,clip]{../img/proyecto4_investigacion.pdf}
\caption{Banco de controladores supervisado}
\label{fig:switching_ctrl}
\end{figure}


El comportamiento del sistema conmutado no es la simple suma de los comportamientos de sus partes:

* ***Conmutación destructiva:*** Es posible que un sistema conmutado sea inestable incluso si todos y cada uno de sus subsistemas son estables. La conmutación en sí misma puede generar inestabilidad

* ***Conmutación constructiva:*** A la inversa, se puede estabilizar un sistema que es inestable en todos sus modos, simplemente conmutando entre ellos de manera adecuada


El diseño de la ley de conmutación es tan crítico como el diseño de los controladores individuales.