================================================================================
PLAN DE ACCION Y APRENDIZAJE: CONTROL DEL PENDULO DE FURUTA
================================================================================

Objetivo:
Estructurar el proceso de comprension, modelado, simulacion e implementacion
del pendulo de Furuta en 4 fases progresivas, evitando la sobrecarga cognitiva
y avanzando paso a paso con criterios de exito verificables.

--------------------------------------------------------------------------------
FASE 1: LA BASE INSTRUMENTAL (Sentir y Mover)
--------------------------------------------------------------------------------
Objetivo:
Lograr que el sistema sensorial mida de forma limpia y confiable, y que el
actuador responda de manera predecible antes de cerrar cualquier lazo.

Actividades clave:
1. Lectura del angulo del brazo (theta_1):
   - Configurar encoder optico incremental (LPD3806, 600 PPR).
   - Verificar decodificacion en cuadratura (modo 4x) y conteo bidireccional.
2. Lectura del angulo del pendulo (theta_2):
   - Configurar sensor magnetico absoluto (AS5600, 12 bits via I2C/PWM).
   - Calibrar la posicion de cero (vertical inestable vs colgado estable).
3. Estimacion de velocidades angulares (omega_1 = dot{theta}_1, omega_2 = dot{theta}_2):
   - Implementar diferenciacion numerica con filtro pasa-bajas digital para
     evitar amplificar el ruido de cuantizacion.
4. Caracterizacion del actuador:
   - Control de modulacion PWM hacia el driver de potencia (Puente H BTS7960).
   - Determinar zona muerta (deadband) del motor y sentido de giro coherente.

Conocimientos a adquirir paso a paso:
- Interrupciones por temporizador (sample time fijo Ts) y lectura de encoders.
- Filtrado digital basico (filtro IIR de primer orden / EMA / filtro Savitzky-Golay).
- Relacion entre ciclo de trabajo PWM, voltaje efectivo y torque del motor.

Criterio de exito de la Fase 1:
- Al mover manualmente el brazo y el pendulo, las graficas en pantalla reflejan
  fielmente las posiciones reales.
- Las senales de velocidad angular son suaves y no presentan oscilaciones ruidosas.
- El motor se mueve suavemente en ambas direcciones respondiendo a consignas basicas.

--------------------------------------------------------------------------------
FASE 2: EL LABORATORIO VIRTUAL (Simular para entender la fisica)
--------------------------------------------------------------------------------
Objetivo:
Construir y utilizar un entorno simulado en software para entender la dinamica
acoplada no lineal sin riesgo de danar el hardware fisico.

Actividades clave:
1. Exploracion del modelo no lineal (Euler-Lagrange):
   - M(q)*ddq + C(q, dq)*dq + G(q) = B*u.
   - Observar el acoplamiento: como la aceleracion del brazo genera torque
     inercial sobre el pendulo no actuado.
2. Simulacion del sistema en bucle abierto:
   - Dejar caer el pendulo libremente y observar la frecuencia natural y
     el amortiguamiento viscoso (b_1, b_2).
   - Simular pulsos de torque en el brazo y ver la respuesta inducida.
3. Representacion en Espacio de Estados:
   - Definir el vector de estados x = [theta_1, dot{theta}_1, theta_2, dot{theta}_2]^T.
   - Linealizar el sistema alrededor del punto de equilibrio inestable (arriba).

Conocimientos a adquirir paso a paso:
- Formulacion basica de Euler-Lagrange para sistemas mecanicos acoplados.
- Concepto de sistema subactuado (1 actuador, 2 grados de libertad).
- Linealizacion en torno a un punto de operacion y analisis matricial (dot{x} = Ax + Bu).

Criterio de exito de la Fase 2:
- La simulacion responde de forma intuitiva a perturbaciones.
- Se comprende con claridad por que el equilibrio arriba es inestable y que
  fuerzas inerciales produce el movimiento del brazo.

--------------------------------------------------------------------------------
FASE 3: EL BALANCEO ARRIBA (Control Local / Estabilizacion)
--------------------------------------------------------------------------------
Objetivo:
Implementar el lazo de estabilizacion que mantiene el pendulo en la vertical
invertida, asumiendo inicialmente que el pendulo se coloca alli de forma manual.

Actividades clave (Mapeo directo con el diagrama de bloques en 'fig.png'):
1. Identificacion de lazos:
   - Lazo K2 (Pendulo): Lazo rapido para contrarrestar la caida de theta_2.
   - Lazo K1 (Brazo): Lazo de centrado para que theta_1 regrese a la referencia R
     sin desbordar los limites fisicos del mecanismo.
2. Diseno del controlador lineal:
   - Sintesis LQR (Linear Quadratic Regulator) o ubicacion de polos.
   - Obtencion del vector de ganancias K = [k_1, k_2, k_3, k_4].
   - Ley de control: u = R - (K1 * x_brazo + K2 * x_pendulo).
3. Evaluacion del retardo de muestreo:
   - Incorporar el retraso digital tau = Ts (bloque H en el diagrama).
   - Validar margenes de estabilidad ante el tiempo de computo del microcontrolador.
4. Pruebas experimentales:
   - Colocar el pendulo verticalmente a mano dentro de una ventana (+- 10 a 15 deg)
     y verificar que el lazo se active y estabilice el sistema.

Conocimientos a adquirir paso a paso:
- Teoria de control por realimentacion de estados (LQR y matrices Q y R).
- Particion de ganancias: compensacion balanceo vs posicion del brazo.
- Efecto desestabilizador del retardo de muestreo digital (Pade / discretizacion z).

Criterio de exito de la Fase 3:
- El pendulo es colocado verticalmente a mano, se suelta, y el motor ejecuta
  correcciones rapidas y precisas manteniendolo en equilibrio sin que el brazo
  se desplace indefinidamente.

--------------------------------------------------------------------------------
FASE 4: EL SWING-UP Y LA CONMUTACION (Control Global y Ciclo Completo)
--------------------------------------------------------------------------------
Objetivo:
Lograr la operacion completamente autonoma del sistema, desde el reposo colgado
hasta el balanceo vertical invertido.

Actividades clave:
1. Diseno del controlador de levantamiento (Swing-Up):
   - Estrategia basada en bombeo de energia: inyectar energia cinetica y
     potencial hasta alcanzar la energia requerida en la cima (E_target).
   - Consigna de torque: u_swing = k_E * (E - E_target) * sgn(dot{theta}_2 * cos(theta_2)).
2. Logica de transicion (Switching):
   - Definir la ventana angular y de velocidad para conmutar:
     |theta_2| < epsilon_theta  Y  |dot{theta}_2| < epsilon_omega.
   - Desconectar suavemente el Swing-Up y activar el controlador LQR (Fase 3).
3. Maquina de estados del firmware:
   - Estado 0: IDLE / REPOSO (espera de comando o inicio seguro).
   - Estado 1: SWING-UP (bombeo oscilatorio de energia).
   - Estado 2: BALANCEO (LQR activo alrededor de la vertical).
   - Estado 3: FALLO / EMERGENCIA (si theta_2 cae mas alla del limite recuperable,
     apagar motor inmediatamente para proteger mecanica y electronica).

Conocimientos a adquirir paso a paso:
- Metodos de control basados en funcion de Lyapunov y balance de energia mecanica.
- Diseno de maquinas de estados finitos (FSM) deterministicas en tiempo real.
- Tecnicas de conmutacion suave para evitar transitorios bruscos de corriente.

Criterio de exito de la Fase 4:
- Partiendo del reposo (pendulo colgado a 180 deg), el sistema balancea el brazo
  2 o 3 veces acumulando energia, levanta el pendulo hasta la cima, conmuta al
  lazo de balanceo y permanece perfectamente estable de forma continua.
================================================================================
