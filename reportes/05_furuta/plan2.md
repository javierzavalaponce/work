# BITÁCORA Y PLAN DE TRABAJO - CONTROL PÉNDULO DE FURUTA
**Archivo:** `plan2.md`  
**Fecha:** 2026-11-21  
**Sesión:** Cierre de jornada - Diagnóstico Mecánico e Instrumental

---

## 1. Datos Generales de la Sesión
* **Operador / Investigador:** [ _______________________________ ]
* **Hora de inicio:** [ _______ ] | **Hora de cierre:** [ _______ ]
* **Hardware bajo prueba:** Motor Wiper 12V + Driver BTS7960 + AS5600 + Encoder LPD3806
* **Estado general del prototipo al inicio:** [ ] Desarmado  [ ] Montado en banco  [ ] En calibración

---

## 2. Eje 1: Alineación y Centrado Físico del Encoder Magnético (AS5600)

El sensor AS5600 mide el campo magnético de un **imán diametral**. Si el imán está descentrado, inclinado o con entrehierro (*air gap*) incorrecto, la lectura introduce un error sinusoidal sistemático que falsea la velocidad y el balanceo.

### Criterios Físicos de Montaje:
* **Tipo de imán:** Diametral (polos N-S en las caras curvas, no axial).
* **Entrehierro (*air gap*):** $0.5\,\text{mm} \le z \le 1.5\,\text{mm}$ entre la cara superior del imán y el encapsulation del chip.
* **Tolerancia de descentramiento radial:** Menor a $0.25\,\text{mm}$ del centro óptico del integrado.

### Procedimiento de Centrado en Banco (Completar):
- [ ] **Alineación axial (Concentricidad):**
  - Método de montaje utilizado: [ ] Buje impreso en 3D  [ ] Acoplamiento con prisionero  [ ] Pegamento epóxico guiado
  - Observación visual del cabeceo (*runout*) al girar a mano: [ ] Nulo  [ ] Leve (<0.5mm)  [ ] Severo (requiere rediseño)
- [ ] **Verificación de intensidad de campo (Registro de Registros AS5600):**
  - Lectura del pin `MD` (Magnet Detected): [ ] HIGH (OK)  [ ] LOW (Imán ausente o muy lejos)
  - Lectura del registro `STATUS` (0x0B) / Pines `MH` y `ML`:
    - `MH` (Magnet too Strong / muy cerca): [ ] Sí  [ ] No
    - `ML` (Magnet too Weak / muy lejos):  [ ] Sí  [ ] No
- [ ] **Mapeo de Linealidad (Prueba de 4 cuadrantes estáticos):**

| Posición física real del péndulo | Cuentas leídas (0 a 4095) | Grados calculados | Error estimado |
| :--- | :--- | :--- | :--- |
| Vertical Arriba ($0^\circ$) [Equilibrio] | [ _______ ] | [ _______ ]$^\circ$ | [ _______ ] |
| Horizontal Derecha ($+90^\circ$) | [ _______ ] | [ _______ ]$^\circ$ | [ _______ ] |
| Vertical Abajo ($180^\circ$) [Reposo] | [ _______ ] | [ _______ ]$^\circ$ | [ _______ ] |
| Horizontal Izquierda ($-90^\circ$ / $270^\circ$) | [ _______ ] | [ _______ ]$^\circ$ | [ _______ ] |

* **Solución de software temporal para hoy:**
  Definir el offset del cero vertical para no frenar pruebas:  
  `Offset_vertical = [ ________ ] cuentas`.

---

## 3. Eje 2: Efecto de la Reducción Mecánica (Motor de Limpiaparabrisas / Wiper)

Los motores de limpiaparabrisas usan típicamente un mecanismo de **tornillo sinfín y corona (worm gear)** con reducción aproximada $30:1$ a $50:1$. 

### Implicaciones críticas para el control del Furuta:
1. **Holgura mecánica (*Backlash*):** Ángulo muerto en el que el motor invierte el giro pero el brazo no se mueve hasta que los dientes vuelven a hacer contacto.
2. **Irreversibilidad (*Non-backdrivability*):** El motor puede mover el brazo con facilidad, pero las fuerzas que el péndulo ejerce sobre el brazo difícilmente mueven el motor hacia atrás.
3. **Inercia reflejada multiplicada ($J_{\text{ref}} = N^2 \cdot J_m$):** El motor se siente sumamente rígido; requiere pares de arranque elevados y frena en seco cuando se corta la tensión.
4. **Fricción interna alta:** Provoca una zona muerta ancha y asimétrica.

### Mediciones de Diagnóstico de la Reducción (Completar hoy):
- [ ] **Medición manual del Backlash (Holgura entre dientes):**
  - Con el motor apagado y bloqueado mecánicamente, mover suavemente el brazo horizontal con los dedos:
  - ¿Cuántos grados o pulsos de encoder se mueve libremente antes de encontrar resistencia?
  - **Backlash medido en el brazo:** [ _______ ] grados / [ _______ ] cuentas del encoder LPD3806.
  - *Diagnóstico preliminar:* [ ] Aceptable (< 1°)  [ ] Moderado (1° a 3°)  [ ] Crítico (> 3°, requerirá precarga elástica)
- [ ] **Prueba de arranque y zona muerta en vacío:**
  - $PWM_{\text{arranque}}$ hacia la DERECHA: [ _______ ] / 255
  - $PWM_{\text{arranque}}$ hacia la IZQUIERDA: [ _______ ] / 255
  - ¿Existe asimetría notable? [ ] Sí  [ ] No (Diferencia: [ ____ ] cuentas)

---

## 4. Plan Específico de Cierre de Jornada (Checklist de hoy)

Objetivo: Terminar el día con el hardware caracterizado y listo para trabajar en código y filtros mañana sin incertidumbre mecánica.

- [x] **Paso 1: Delimitar el alcance conceptual** (Fases 1 a 4 plasmadas en `plan.txt`).
- [ ] **Paso 2: Inspección y fijación mecánica del AS5600**
  - Asegurar que el soporte del imán no tenga juego axial.
  - Ajustar entrehierro a $\approx 1\,\text{mm}$ (usar una tarjeta de plástico/calza como referencia rápida).
- [ ] **Paso 3: Tomar las 4 lecturas estáticas del AS5600** y anotar en la tabla de la Sección 2.
- [ ] **Paso 4: Prueba manual de holgura (*backlash*) del brazo** y registrar el valor en la Sección 3.
- [ ] **Paso 5: Respaldo y desconexión segura del banco:**
  - Desconectar fuente de 12V del puente BTS7960.
  - Dejar cables rotulados y el microcontrolador en modo reposo.

---

## 5. Conclusiones y Tareas Prioritarias para la Próxima Sesión

### Conclusiones del día:
* *Alineación sensor:* [ _________________________________________________________________ ]
* *Comportamiento del motor/reductor:* [ _________________________________________________ ]
* *Mayor obstáculo detectado hoy:* [ ____________________________________________________ ]

### Primeras 2 tareas para mañana:
1. [ ] Implementar el filtro digital de velocidad angular con la frecuencia de corte definida ($\omega_c \approx 30\,\text{Hz}$).
2. [ ] Programar la rutina de compensación de zona muerta en firmware usando los valores medidos en esta bitácora.
