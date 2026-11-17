```{=latex}
\clearpage
```

## Transformada Z


La transformada Z convierte una secuencia temporal en una expresión algebraica.

Su definición bilateral es:
$$
X(z)=\sum_{k=-\infty}^{\infty}x[k]z^{-k}
$$



| Dominio temporal  | Dominio Z |
|:---------|:------------|
| x[k] | X(z)    | 
| x[k-1] | z^{-1}X(z)|  
| x[k-2] | z^{-2}X(z)   |

: la variable z es compleja

permite convertir ecuaciones en diferencias en ecuaciones algebraicas, facilitando el análisis de sistemas discretos. El índice $k$ no es el tiempo físico, el tiempo sería $t=kT_s$ con $T_s$ como el tiempo de muestreo.

### Ecuaciones en diferencias


Consideremos esta sucesión:

$$
x[k]=\{1,2,3,4,5,\ldots\}
$$

Podemos describirla de dos maneras.

1. mediante una fórmula directa
$$
x[k]=k+1
$$

1. mediante su valor anterior
$$
x[k]=x[k-1]+1
$$


Una ecuación como $y[k]=0.5y[k-1]+u[k]$
se denomina:

| Elemento   | Significado |
|:---------|:------------|
| y[k] | Salida actual   | 
| y[k-1] | Salida anterior|  
| u[k] | Entrada actual  |
| 0.5| Factor que pondera la salida anterior  |

: ecuación en diferencias

### la variable $z$

$z$ es una variable compleja que nos permite representar y estudiar el comportamiento de señales y sistemas discretos.

Tomemos una sucesión:
$$
x[k]=1,\ 2,\ 3,\ 4,\ 5,\ldots
$$

podemos construir una serie multiplicando cada elemento por una potencia de algún número $a$:

$$
X(a)=x[0]+x[1]a^{-1}+x[2]a^{-2}+\cdots
$$

Para nuestra sucesión:
$$
X(a)=1+2a^{-1}+3a^{-2}+4a^{-3}+\cdots
$$

Convertimos una lista de números en una expresión que depende 
de una variable. La idea central: podemos evaluar esa expresión para distintos valores de $a$.

En la transformada Z, simplemente llamamos $z$ a esa variable:
$$
\boxed{
X(z)=\sum_{k=0}^{\infty}x[k]z^{-k}
}
$$

tomemos por ejemplo una secuencia de solamente tres elementos:
$$
x[0]=1,\quad x[1]=2,\quad x[2]=3
$$

Su expresión será:
$$
X(z)=1+2z^{-1}+3z^{-2}
$$

Ahora vamos a darle diferentes valores a $z$

| z   | X(z) |
|:---------|:------------|
| 1 | X(1)=1+2(1)+3(1)=6  | 
| 2 | X(2)=1+2(1/2)+3(1/4)=2.75|  
| 0.5 | X(0.5)=1+2(2)+3(4)=17  |

: El valor de z modifica el peso matemático que recibe cada elemento de la sucesión.

$z$ puede ser una variable compleja  $z=a+jb$ o en forma polar: $z=re^{j\theta}$  con $\theta = \omega T_s$



\newpage



| Laplace | Transformada Z |
|---|---|
| $s=\sigma+j\omega$ | $z=re^{j\theta}$ con $\theta = \omega T_s$|
| Sistemas continuos | Sistemas discretos |
| $e^{-sT}$ representa un retardo temporal T | $z^{-1}$ representa un retardo de una muestra |

: Una analogia

Hay una relación matemática muy importante:
$$
\boxed{z=e^{sT_s}}
$$

**Ejercicio**

Para $y[k]=3y[k-1]+2y[k-2]+u[k]$ ¿Cuál sería su representación en el dominio $Z$?
$$
Y(z)=3z^{-1}Y(z)+2z^{-2}Y(z)+U(z)
$$

\newpage 

### Región de Convergencia


La definición de la transformada Z es una suma infinita:
$$
X(z)=\sum_{k=0}^{\infty}x[k]z^{-k}
$$
Una suma infinita no siempre da un número finito: depende del valor de $z$. 
El conjunto de valores de $z$ para los cuales la suma converge se llama 
\textbf{región de convergencia} (ROC). Sin especificar la ROC, la expresión 
algebraica de $X(z)$ está incompleta.

#### Ejemplo: secuencia causal

Tomemos la secuencia más simple que no es finita:
$$
x[k]=a^k \quad\text{para } k\ge 0,
$$
es decir,
$$
x[k]=\{1,\ a,\ a^2,\ a^3,\ \dots\}.
$$
Su transformada Z (unilateral, desde $k=0$) es:
$$
X(z)=\sum_{k=0}^{\infty}a^k z^{-k}
    =\sum_{k=0}^{\infty}\left(\frac{a}{z}\right)^{k}.
$$
Esta es una serie geométrica de razón $q=a/z$. Recordemos el criterio 
de convergencia de la serie geométrica:
$$
\sum_{k=0}^{\infty}q^k=\frac{1}{1-q}
\quad\textbf{solo si } |q|<1.
$$
Si $|q|\ge 1$, la serie diverge (no da un número finito).

#### Aplicando la condición de convergencia

Aquí $q=a/z$. La condición $|q|<1$ significa:
$$
\left|\frac{a}{z}\right|<1
\;\Longleftrightarrow\;
|a|<|z|
\;\Longleftrightarrow\;
|z|>|a|.
$$
Entonces, \textbf{solo para} $|z|>|a|$ podemos escribir:
$$
X(z)=\frac{1}{1-a/z}=\frac{z}{z-a}.
$$
Y la ROC es:
$$
\boxed{\text{ROC}:\ |z|>|a|}
$$

### Tabla resumen de ROC

| Tipo de secuencia | Vive en | Razón de la geométrica | ROC | Ejemplo |
|:------------------|:--------|:-----------------------|:----|:--------|
| **Causal** | $k\ge 0$ | $a/z$ ($z$ en el denominador) | $\lvert z\rvert>\lvert a\rvert$ | $a^k u[k]$ |
| **Anticausal** | $k\le -1$ | $z/a$ ($z$ en el numerador) | $\lvert z\rvert<\lvert a\rvert$ | $-a^k u[-k-1]$ |
| **Bilateral** | $-\infty<k<\infty$ | ambas | $\lvert a\rvert<\lvert z\rvert<\lvert b\rvert$ (anillo) | $a^{k}u[k]+b^{k}u[-k-1]$ |
| **Finita** | intervalo finito | — | todo el plano salvo $0$ y/o $\infty$ | $\{1,2,3\}$ |

: Región de convergencia según el tipo de secuencia


### Respuesta impulsional

La respuesta impulsional $h[k]$ es la salida del filtro cuando la entrada es un impulso $\delta[k]$ (un $1$ en $k=0$, ceros después), partiendo del reposo. 
Para el filtro exponencial, $h[k]=(1−\alpha) \alpha^k u[k]$. El polo de 
$H(z)$ es $z=\alpha$, que es la base de esa exponencial: 
si $∣\alpha∣<1$ la respuesta decae (estable), 
si $∣\alpha∣>1$ explota (inestable).