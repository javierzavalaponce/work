# tf2ss

$$
G(s)=\frac{1}{s^2-3s+2}
$$

Por tanto, las listas son:
$$
\text{num}=[1],\qquad \text{den}=[1,-3,2]
$$

objetivo es construir:
$$
\dot{x}=Ax+Bu,\qquad y=Cx+Du
$$

La función de transferencia general que estamos considerando es:
$$
G(s)=
\frac{b_0s^n+b_1s^{n-1}+\cdots+b_n}
{s^n+a_1s^{n-1}+\cdots+a_n}
$$

El denominador tiene grado \(n\). Para construir las matrices, queremos expresar el numerador con la misma cantidad de posiciones que el denominador.
En nuestro ejemplo:
$$
G(s)=\frac{1}{s^2-3s+2}
$$

Aunque el denominador tiene grado dos, el numerador tiene grado cero.
Podemos escribir la misma función como:
$$
G(s)=\frac{0s^2+0s+1}{s^2-3s+2}
$$

Observa que no hemos cambiado la función de transferencia: simplemente hemos añadido términos con coeficiente cero.
Así, las listas quedan alineadas:
$$
\underbrace{[0,0,1]}_{\text{num}}
\qquad
\underbrace{[1,-3,2]}_{\text{den}}
$$

El código den[1:] elimina el primer elemento, que es el coeficiente de \(s^2\), y conserva:
$$
a=[-3,2]
$$

Esto debido a que el primer coeficiente ya es uno y no necesitamos introducirlo otra vez en la construcción de la matriz $A$.

## Obtener la matriz $D$: ganancia directa

```python
# Ganancia directa
D = np.array([[num[0]]])
```

La ecuación de salida es:
$$
y=Cx+Du
$$

La matriz $D$ representa una contribución directa de la entrada $u$ a la salida $y$, sin pasar por la dinámica de los estados.
Para una función de transferencia propia de la forma:
$$
G(s)=
\frac{b_0s^n+b_1s^{n-1}+\cdots+b_n}
{s^n+a_1s^{n-1}+\cdots+a_n}
$$

la ganancia directa es:
$$
\boxed{D=b_0}
$$

Después de completar el numerador, tenemos:
$$
\text{num}=[0,0,1]
$$

Así que:
$$
\boxed{D=0}
$$

En este caso, la entrada no aparece directamente en la ecuación de salida. Su efecto llega a través de los estados.
Una precisión importante: si el numerador tuviera el mismo grado que el denominador, 
$D$ podría ser distinto de cero. En ese caso, hay que separar primero la parte de ganancia directa del resto de la función de transferencia.

\newpage

## Construir la matriz $A$: la dinámica de los estados

Este es el bloque central.

```python
A = np.zeros((n, n))

if n > 1:
    A[:-1, 1:] = np.eye(n - 1)

A[-1, :] = -a[::-1]
```

primero debemos elegir los estados.

Partimos de:
$$
G(s)=\frac{1}{s^2-3s+2}
$$

Como el denominador tiene grado dos, necesitamos dos estados. En la forma canónica controlable que estamos construyendo, elegimos:
$$
x_1=y,\qquad x_2=\dot y
$$

La ecuación diferencial original se obtiene multiplicando por el denominador:
$$
(s^2-3s+2)Y(s)=U(s)
$$

Suponiendo condiciones iniciales nulas, en el dominio del tiempo:
$$
\ddot y-3\dot y+2y=u
$$

Despejamos la derivada de mayor orden:
$$
\ddot y=3\dot y-2y+u
$$

Ahora sustituimos nuestros estados:
$$
\begin{aligned}
\dot x_1&=x_2\\
\dot x_2&=-2x_1+3x_2+u
\end{aligned}
$$

Ya podemos identificar las matrices:
$$
\boxed{
A=
\begin{bmatrix}
0&1\\
-2&3
\end{bmatrix}
}
$$


Primero, el programa crea una matriz de ceros:
```python
A = np.zeros((n, n))
```

	Para \(n=2\):
$$
A=
\begin{bmatrix}
0&0\\
0&0
\end{bmatrix}
$$

y despues ejecuta:

```python
A[:-1, 1:] = np.eye(n - 1)
```

En nuestro caso, np.eye(1) produce:
$$
[1]
$$


La asignación coloca ese uno en la parte superior derecha:
$$
A=
\begin{bmatrix}
0&1\\
0&0
\end{bmatrix}
$$

¿Por qué queremos ese uno? Porque definimos los estados de tal forma que:
$$
\dot x_1=x_2
$$

El primer estado tiene como derivada al segundo estado. Ese es el origen matemático del uno.


la ultima fila sale de:

```python
A[-1, :] = -a[::-1]
```


Ya sabemos que:
$$
a=[-3,2]
$$

El operador [::-1] invierte el orden:
$$
a[::-1]=[2,-3]
$$

El signo negativo cambia los signos:
$$
-a[::-1]=[-2,3]
$$

Se coloca ese resultado en la última fila de \(A\):
$$
\boxed{
A=
\begin{bmatrix}
0&1\\
-2&3
\end{bmatrix}
}
$$

La última fila representa la segunda ecuación:
$$
\dot x_2=-2x_1+3x_2+u
$$

En general, para el denominador mónico
$$
s^n+a_1s^{n-1}+\cdots+a_n
$$

la última fila de la matriz $A$, en esta convención, es:
$$
\boxed{
[-a_n,-a_{n-1},\ldots,-a_1]
}
$$

El orden inverso no es arbitrario: se deriva de la forma en que hemos organizado los estados y escrito la ecuación diferencial.


## la matriz $B$: cómo entra la señal

```python
B = np.zeros((n, 1))
B[-1, 0] = 1
```



La entrada aparece en la ecuación:
$$
\ddot y=3\dot y-2y+u
$$

Al expresarla mediante estados:
$$
\begin{aligned}
\dot x_1&=x_2+0u\\
\dot x_2&=-2x_1+3x_2+1u
\end{aligned}
$$

Por eso:
$$
\boxed{
B=
\begin{bmatrix}
0\\
1
\end{bmatrix}
}
$$

Primero creamos una matriz columna de ceros:
$$
B=
\begin{bmatrix}
0\\
0
\end{bmatrix}
$$

Después asignamos un uno en la última posición:
$$
B[-1,0]=1
$$

¿Por qué en la última posición? Porque, con esta elección de estados, la entrada aparece directamente en la ecuación del último estado, $\dot x_2$.
Para un sistema de orden tres, la misma regla daría:
$$
B=
\begin{bmatrix}
0\\
0\\
1
\end{bmatrix}
$$


## Construir la matriz $C$: cómo obtenemos la salida

```python
c = num[1:] - D[0, 0] * den[1:]
C = c[::-1].reshape(1, n)
```


Esta parte requiere distinguir dos cosas: los coeficientes del numerador y la forma en que los estados se relacionan con la salida.
En general, con el numerador completado:
$$
b_0s^n+b_1s^{n-1}+\cdots+b_n
$$

y el denominador:
$$
s^n+a_1s^{n-1}+\cdots+a_n
$$

la matriz $C$, en nuestra convención, se obtiene mediante:
$$
\boxed{
C=
\begin{bmatrix}
b_n- Da_n&
b_{n-1}-Da_{n-1}&
\cdots&
b_1-Da_1
\end{bmatrix}
}
$$

Observa que $b_0$ se utiliza para obtener $D$. Los demás coeficientes se combinan con los del denominador para calcular $C$.
En nuestro ejemplo:
$$
\text{num}=[0,0,1],\qquad D=0
$$

Por tanto, los coeficientes restantes del numerador son:
$$
\text{num}[1:]=[0,1]
$$

Y:
$$
D\cdot \text{den}[1:]=0[-3,2]=[0,0]
$$

La resta produce:
$$
c=[0,1]-[0,0]=[0,1]
$$

Al invertir el orden:
$$
c[::-1]=[1,0]
$$

Finalmente, reshape(1, n) transforma la lista en una matriz de una fila y \(n\) columnas:
$$
\boxed{C=\begin{bmatrix}1&0\end{bmatrix}}
$$

La salida resulta ser:
$$
y=Cx+Du
$$

$$
y=
\begin{bmatrix}1&0\end{bmatrix}
\begin{bmatrix}x_1\\x_2\end{bmatrix}+0u
$$

Es decir:
$$
\boxed{y=x_1}
$$

Esto coincide con nuestra elección inicial del primer estado.

## Resumen: de dónde sale cada matriz

Para la función de transferencia
$$
G(s)=\frac{1}{s^2-3s+2}
$$

obtenemos:

obtenemos:
$$
\boxed{
\begin{aligned}
A&=\begin{bmatrix}0&1\\-2&3\end{bmatrix}\\[6pt]
B&=\begin{bmatrix}0\\1\end{bmatrix}\\[6pt]
C&=\begin{bmatrix}1&0\end{bmatrix}\\[6pt]
D&=\begin{bmatrix}0\end{bmatrix}
\end{aligned}
}
$$

Y las ecuaciones diferenciales correspondientes son:
$$
\boxed{
\begin{aligned}
\dot x_1&=x_2\\
\dot x_2&=-2x_1+3x_2+u\\
y&=x_1
\end{aligned}
}
$$

La idea fundamental es que el programa no está adivinando las matrices. Está aplicando una estructura matemática predeterminada —la forma canónica controlable— a los coeficientes de la función de transferencia.
Una función de transferencia puede representarse mediante diferentes elecciones de estados. Aquí hemos elegido una estructura concreta, lo que permite construir las matrices de manera sistemática a partir de las listas num y den.


