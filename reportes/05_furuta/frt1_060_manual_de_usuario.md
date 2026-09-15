```{=latex}
\clearpage
```
	
# Manual de Usuario e informacion operativa

Esta sección contiene información de como 
utilizar y poner en funcionamiento el robot pendulo de Furuta
La mayoria de este trabajo ha sido desarrollada sobre equipo de
computo con Debian13 instalado.

En robótica, online/offline se refiere principalmente a si se esta interactuando directamente con el robot físico o trabajando sin él.


## Offline  

Control manual


## Online

El robot online necesita el sw
```drive_fur``` 
que es un programa hecho en python
envia comandos via serial al 
arduino 
para interactuar 

---
TCP Tool Center Point

Frame sistema de coordenadas

Base frame sistema de coordenadas de la base

Tool frame

Joints / joint space
espacio articular

Cartesian space
espacio cartesiano

Forward kinematics (FK)
cinemática directa

Inverse kinematics (IK)
cinemática inversa

Jogging
mover manualmente los ejes

Teach pendant

Controller

Post processor

Robot driver

OLP — Offline Programming

Collision checking

Reachability

Singularity

Path planning


El flujo:

modelo → joints → frames → TCP → FK → IK → trayectoria → simulación → postprocesador → controlador → robot físico.

Ese es prácticamente el idioma conceptual del área.
