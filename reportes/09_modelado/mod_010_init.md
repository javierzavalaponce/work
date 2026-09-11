```{=latex}
\clearpage
```

# Modelado


\vspace{1.5cm}


## Modelado de circuitos electricos

\vspace{1cm}

### Netlist y ngspice

Un netlist es una descripción textual de un circuito: lista los componentes 
(resistores, fuentes, capacitores, etc.) y cómo están conectados entre sí mediante nodos. 

*NGspice* (simulador open source) lo lee, genera el sistema de ecuaciones (por ejemplo, por análisis nodal modificado) y lo resuelve numéricamente.

La extensión *.cir* es solo una convención. El contenido es lo importante.

#### Reglas básicas de sintaxis

* La primera línea es siempre el título (ngspice la ignora como comentario, pero es obligatoria).

* Los comentarios empiezan con * al inicio de línea.

* Los nodos se nombran con números o palabras (1, 2, in, out, 0).

* El nodo 0 es *siempre* tierra (*GND*) — obligatorio.

* Cada línea describe un componente: ```nombre + nodos + valor```

* Las unidades: se pueden omitir (MKS) 
	1k = 1000, 1u = 1e-6, 1meg = 1e6 (m es mili, meg es mega).

* Las directivas empiezan con . (ej: ```.tran, .dc, .ac, .end```)
    
* La última línea debe ser ```.end```

\newpage 

**Prefijos de componentes (letra inicial):**

```bash

Letra Componente
------------------
R	  Resistencia
C	  Capacitor
L	  Inductor
V	  Fuente de voltaje independiente
I	  Fuente de corriente independiente
D	  Diodo
Q	  Transistor BJT
M	  Transistor MOSFET
E/G	  Fuentes dependientes (VCVS/VCCS)
F/H	  Fuentes dependientes (CCCS/CCVS)
```

\vspace{2cm}

**Ejemplo *divisor_de_voltage.cir***

```c
* Barrido DC de V1
V1 in 0 DC 0
R1 in out 1k
R2 out 0 1k

.dc V1 0 10 0.5
.print dc v(out) i(V1)
.end
```
\newpage

### Ejercicio (7)


Obtener una ecuacion diferencial para v2

1. Version esquematico visual

\begin{figure}[H]
\centering
\includegraphics[width=0.3\textwidth,trim=0cm 0cm 0cm 0cm,clip]{../img/cir_ejer07.png}
\caption{Circuito fig 7}
\label{fig:ejer07_tarea}
\end{figure}

\vspace{0.8cm}
2. Tambien se puede expresar asi: 

```bash
in---[R_1|C_1]---v_1---[R_2]---v_2---[C_2]---0
```
\vspace{0.8cm}
3. Tambien se puede expresar asi (): 

```bash
* EJER7 - Respuesta al escalon 
V1 in 0 PWL(0 0 1n 5)
R1 in v3 1k
C1 in v3 1u
R2 v3 v2 1k
C2 v2 0 1u

.tran 1u 20m
.print v(in) v(v3) v(v2)
.end
``` 

\newpage

**Solución**
LCK en nodo v1

```{=latex}
\begin{equation}
\frac{V-v_1}{R_1} + C_1(\dot{V}-\dot{v_1}) = \frac{v_1-v_2}{R_2}
\label{eq:eq_uno}
\end{equation}
```

LCK en nodo v2

```{=latex}
\begin{equation}
\frac{v_1-v_2}{R_2} = C_2 \dot{v_2}
\label{eq:eq_dos}
\end{equation}
```

A partir de la ecuacion \ref{eq:eq_dos} se despeja $v_1$, se deriva para obtener $\dot{v_1}$ y se sustituye en la ecuacion \ref{eq:eq_uno}

se llega a la ecuacion

```{=latex}
\[
\underbrace{R_1 C_1 R_2 C_2}_{\text{coef. de } \ddot{v_2}} \ddot{v_2}
+ \underbrace{\left( R_2 C_2 + R_1 C_1 + R_1 C_2 \right)}_{\text{coef. de } \dot{v_2}} \dot{v_2}
+ v_2
= V + R_1 C_1 \dot{V}
\]
```




