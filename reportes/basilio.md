## Clases de Dr. Basilio: Espacio de estados

# Repaso de Control Clàsico


La derivada no es un invento humano, sino un descubrimiento de cómo el universo opera.

1. Cuando vas manejando y miras el velocímetro, ese número es una derivada: 

v=dx/dt 
(qué tan rápido cambia la posición)

Cuando llenas un vaso y ves que el agua sube, lo que "ves" es dh
h = dh/dt

El futuro de un sistema está determinado ÚNICAMENTE por su estado PRESENTE, 
no por su historia.

2. Un capacitor NO "recuerda" cuánta corriente recibió hace un minuto. Solo "sabe" cuál es su voltaje AHORA y cuánta corriente está entrando AHORA.

* El agua en el vaso NO "recuerda" que antes entraba más rápido. Solo "sabe" cuál es su altura AHORA y cuál es el caudal AHORA.








Es mi presente lo que no me va bien.
No es mi historia contigo
nuestro presente es bueno.
Yo he logrado un presente sin carencia economica.
Tu apoyo ha sido fundamental clarametne. Pero no encuentro paz a tu lado.
perdon por todo lo malo, gracias por todo lo bueno.
Quiero ser feliz y espero que tu tambien lo seas,
espero que mi hija no deje de contar con tu apoyo nunca,
el mio lo tendra por siempre.
Gracias por todo, Gracias por quererme cuando me quisiste.
Lamento no haber estado a la altura de tus ilusiones
ni de los espejismos que dreiste ver en mi.











La derivada es la forma que tenemos los humanos de describir un hecho fundamental del universo:





Cuando llenas un vaso y ves que el agua sube, lo que "ves" es dhdtdtdh​



Definición de Corriente (ii): La corriente eléctrica no es más que el flujo de carga a través del tiempo. En otras palabras, la corriente (ii) es la tasa de cambio instantánea de la carga (QQ). El cálculo nos da la herramienta precisa para expresar esto:
i=dQdt
i=dtdQ​

Esto significa "la corriente es la derivada de la carga con respecto al tiempo"

.

Combinando las Ideas: Si un capacitor tiene una capacitancia CC constante, y en todo momento se cumple que Q=C⋅VQ=C⋅V, entonces podemos sustituir la QQ en la definición de corriente:
i=d(C⋅V)dt
i=dtd(C⋅V)​

El Resultado Final: Como CC es una constante, puede salir de la derivada, llegando a la ecuación que buscamos:

 i = C (dV/dt)
 


El Significado Profundo de la Ecuación

Esta fórmula no es solo una curiosidad matemática. Tiene un significado físico muy profundo que responde a tu curiosidad inicial:

    ¿Por qué un cambio de voltaje? La ecuación nos dice que, para que fluya corriente a través de un capacitor, el voltaje entre sus placas debe estar cambiando. Si el voltaje es constante (dV/dt=0dV/dt=0), la corriente es cero. El capacitor se comporta como un circuito abierto para la corriente continua (DC)

.

El rol de la Resistencia: En un circuito RC, es la resistencia la que controla "qué tan rápido" puede cambiar ese voltaje. El producto R⋅CR⋅C es la constante de tiempo (ττ), que define la velocidad de carga y descarga. No es que el capacitor dependa de di/dtdi/dt, sino que la resistencia limita la corriente, y esa corriente, a su vez, determina dv/dtdv/dt.


-------------









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
