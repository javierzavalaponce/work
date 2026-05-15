\newpage
### Polos y ceros

Definición:
En una **funcion de transferencia** $ft=H(s)$:

* Los ceros de una $ft$ son las $frecuencias$ (valores de $s$) para los
        cuales el *numerador* de $H(s)=0$

* Los polos de una $ft$ son las $frecuencias$ (valores de $s$) para los
        cuales el *denominador* de $H(s)=0$

Forma general de una $ft$:

```{=latex}
\begin{equation}
\begin{aligned}
  H(s)=k \cdot \frac{(s - z_1)(s - z_2)...(s - z_m)}{(s - p_1)(s - p_2)...(s - p_n)}= k \cdot \frac{\displaystyle\prod_{i=1}^{m} (s - z_i)}{\displaystyle\prod_{j=1}^{n} (s - p_j)}
\end{aligned}
\end{equation}
```

La función de transferencia $H(s)$ en el dominio de Laplace se relaciona con la respuesta temporal $h(t)$ mediante la transformada inversa:

```{=latex}
\begin{equation}
\begin{aligned}
h(t) = \mathcal{L}^{-1}\{H(s)\}
\end{aligned}
\end{equation}
```

* Los polos determinan directamente los *modos naturales* (un modo = una pieza elemental de comportamiento temporal). 
* Los ceros no crean modos nuevos; más bien moldean, cancelan o enfatizan esos modos.

Relación entre ubicación de polos y comportamiento temporal:

| Ubicación del polo | Respuesta temporal asociada |
|---|---|
| $s < 0$ real | decaimiento estable |
| Más a la izquierda | respuesta más rápida |
| Cerca del origen | respuesta lenta / memoria larga |
| $s = 0$ | integración / acumulación |
| Polos complejos | oscilación |
| Parte imaginaria grande | oscilación más rápida |
| Parte real negativa pequeña | oscilación persistente |
| $s > 0$ real | crecimiento inestable |

Relación general de los ceros:

| Ubicación del cero | Efecto típico |
|---|---|
| Cero cercano a polos dominantes | modifica fuertemente la forma de la respuesta |
| Ceros lejanos | efecto pequeño |
| Cero en semiplano derecho | puede producir respuesta inversa o sobreimpulso |


En el plano complejo, la ubicación de polos y ceros codifica directamente la manera en que un sistema evoluciona en el tiempo.
