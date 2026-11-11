```{=latex}
\clearpage
```

# Introduccion


Los sistemas con retardo (también conocidos como sistemas con tiempo muerto, retraso temporal o *time-delay systems*) son aquellos en los que existe un intervalo de tiempo entre el momento en que se aplica una acción (entrada) y el momento en que se empieza a observar su efecto en el sistema (salida).




## Exploracion Inicial *Python* (librerias)


| Librería | Descripción |
|:---------|:------------|
| tdcpy o YALTAPy | Análisis de estabilidad (polos, abscisa espectral)| 
| python-control + Padé | Simulación de control con retardo (aproximado) |  
| Skogestad-Python(InternalDelay) | Simulación exacta con operaciones algebraicas|
| jitcsim | EDEs estocásticas con retardo|
| DelaySSA | Reacciones bioquímicas estocásticas con retardo|
| Brian 2 | Redes neuronales con retardo sináptico |

: Librerias Python relacionadas con sistemas con retardo

\newpage

## Exploracion Inicial *Julia*  (librerias)

En el ecosistema de Julia, el soporte para sistemas con retardo es bastante sólido, aunque está distribuido en librerías más especializadas que en Python. Aquí tienes una tabla equivalente con las opciones principales:



| Librería | Descripción |
|:---------|:------------|
| ControlSystems.jl | Análisis y simulación de sistemas de control con retardo (aproximación de Padé, discretización, respuesta temporal/frecuencial) |
| SemiDiscretizationMethod.jl | Análisis de estabilidad de ecuaciones diferenciales con retardo (DDEs) lineales y periódicas mediante semi-discretización |
| StochasticDelayDiffEq.jl  | EDEs estocásticas con retardo (SDDEs) con soporte para retardos constantes y dependientes del estado |
| DelaySSAToolkit.jl |  Reacciones bioquímicas estocásticas con retardo (algoritmo de Gillespie con retardos no markovianos) |
| DifferentialEquations.jl |  Ecosistema base que incluye solvers para DDEs deterministas y estocásticas, con callbacks para eventos |
| PadeDelay (Dyad/BlockComponents) | Aproximación de Padé para retardos en modelos acausal de Modelica, útil para simulación de sistemas físicos con retardo |


: Librerias Julia relacionadas con sistemas con retardo


