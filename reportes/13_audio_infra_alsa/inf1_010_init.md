
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

```bash
pw-link -l
alsa_output.pci-0000_05_00.6.analog-stereo:playback_FL  |<- parole:output_FL
alsa_output.pci-0000_05_00.6.analog-stereo:playback_FR  |<- parole:output_FR
parole:output_FL  |-> alsa_output.pci-0000_05_00.6.analog-stereo:playback_FL
parole:output_FR  |-> alsa_output.pci-0000_05_00.6.analog-stereo:playback_FR

```

PipeWire organiza el audio como un grafo de conexiones: los programas y dispositivos tienen puertos, y los enlaces indican por dónde circula el audio.



## Reproducción de una pista de audio

Abres un reproductor de música y pulsas *Play*:

Reproductor $\rightarrow$ Sistema de Audio $\rightarrow$ Tarjeta de Sonido


## Carpeta por cada proyecto

```bash
mi_sesion/
proyecto.json
audio/
  01_base.mp3
  02_percusion.mp3
  03_bajo.mp3
  04_textura.mp3
  05_ambiente.mp3
```

UMC1820 
python 
etc
Archivos WAV

5 pistas mono

NumPy

Organiza las muestras de las cinco pistas

sounddevice

Un flujo de audio, cinco canales de salida

Acceso al dispositivo de audio en Debian

UMC1820

Cinco conectores físicos independientes

python -m pip install numpy sounddevice soundfile



\newpage
