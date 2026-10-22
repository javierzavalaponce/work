
```{=latex}
\clearpage
```

# Introduccion



| Capa | Descripción |
|:---------|:------------|
| Aplicaciones de audio  | Mixxx · Qtractor · reproductores · sintetizadores| 
| ____________________  | ____________________| 
| PipeWire / PulseAudio / JACK | Mezcla, conexiones, enrutamiento y reproducción |  
| ____________________  | ____________________| 
| ALSA — Advanced Linux Sound Architecture | Interfaz del kernel para acceder al hardware de audio |
| ____________________  | ____________________| 
| Hardware | Tarjeta de sonido · entradas · salidas · convertidores|

:  Las Capas del Audio en Linux

* *ALSA* es la infraestructura de audio de bajo nivel de Linux
* *PipeWire* es un servidor de audio moderno que puede integrar las funciones de *PulseAudio* y *JACK.*
* ***PipeWire*** es recomendado y predeterminado en la mayoría de los entornos de escritorio


## Comandos exploracion

```bash
pactl info | grep "Server Name"
```

Indica qué servidor atiende la interfaz compatible con PulseAudio;

```bash
wpctl status
```
Muestra el estado de PipeWire y sus dispositivos, si está activo.


```bash
aplay -l
```
enumera las tarjetas de sonido detectadas por ALSA


## Reproducción de una pista de audio

Abres un reproductor de música y pulsas *Play*:

Reproductor $\rightarrow$ Sistema de Audio $\rightarrow$ Tarjeta de Sonido









\newpage
