
#include <Arduino.h>

// --------------------------------------------------
// Maquina de estados
// --------------------------------------------------

enum states {
    STATE_0,
    STATE_1,
    STATE_2,
    STATE_3,
    MAX_STATES
};

enum events {
    EVENT_1,
    EVENT_2,
    MAX_EVENTS
};

states current_state = STATE_0;
events new_event;

// --------------------------------------------------
// Encoder manual
// --------------------------------------------------

const int ENC_A = 9;
const int ENC_B = 10;
const int PIN_SW = 11;
const int ENC_LED = 12;

int A;
int B;

// Estado fisico anterior y actual del encoder
int state;
int cuadrature_cnt;

// Contador de posicion
long encoder = 0;

// Acumulador de transiciones de cuadratura
int quarter_steps = 0;

// --------------------------------------------------
// Prototipos de funciones
// --------------------------------------------------

void action_s0_e1(void);
void action_s0_e2(void);
void action_s1_e1(void);
void action_s1_e2(void);
void action_s2_e1(void);
void action_s2_e2(void);
void action_s3_e1(void);
void action_s3_e2(void);

enum events get_new_event(void);

// --------------------------------------------------
// Tabla de estados y eventos
// --------------------------------------------------

void (*const state_table[MAX_STATES][MAX_EVENTS])(void) = {
    { action_s0_e1, action_s0_e2 },
    { action_s1_e1, action_s1_e2 },
    { action_s2_e1, action_s2_e2 },
    { action_s3_e1, action_s3_e2 }
};

// --------------------------------------------------
// Inicializacion
// --------------------------------------------------

void setup()
{
    Serial.begin(115200);

    pinMode(ENC_A, INPUT_PULLUP);
    pinMode(ENC_B, INPUT_PULLUP);
    pinMode(PIN_SW, INPUT_PULLUP);

    pinMode(ENC_LED, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(ENC_LED, LOW);
    digitalWrite(LED_BUILTIN, LOW);

    A = digitalRead(ENC_A);
    B = digitalRead(ENC_B);

    state = A + 2 * B;

    Serial.println("START");
    //Serial.print("Estado inicial: ");
    Serial.println(state);
}

// --------------------------------------------------
// Ciclo principal
// --------------------------------------------------

void loop()
{
    new_event = get_new_event();

    if (new_event < MAX_EVENTS &&
        current_state < MAX_STATES) {

        state_table[current_state][new_event]();
    }
}

// --------------------------------------------------
// Acciones de la maquina de estados
// --------------------------------------------------

void action_s0_e1(void) {current_state = STATE_1;}
void action_s0_e2(void) {current_state = STATE_2;}
void action_s1_e1(void) {current_state = STATE_3;}
void action_s1_e2(void) {current_state = STATE_0;}
void action_s2_e1(void) {current_state = STATE_0;}
void action_s2_e2(void) {current_state = STATE_3;}
void action_s3_e1(void) {current_state = STATE_2;}
void action_s3_e2(void) {current_state = STATE_1;}

// --------------------------------------------------
// Lectura y decodificacion del encoder
// --------------------------------------------------

enum events get_new_event(void)
{
    A = digitalRead(ENC_A);
    B = digitalRead(ENC_B);

    cuadrature_cnt = A + 2 * B;

    // No hubo cambio en los canales.
    if (state == cuadrature_cnt) {
        return (events)MAX_EVENTS;
    }

    int previous_state = state;
    state = cuadrature_cnt;

    // Sentido positivo:
    // 3 -> 2 -> 0 -> 1 -> 3
    if ((previous_state == 3 && cuadrature_cnt == 2) ||
        (previous_state == 2 && cuadrature_cnt == 0) ||
        (previous_state == 0 && cuadrature_cnt == 1) ||
        (previous_state == 1 && cuadrature_cnt == 3)) {

        quarter_steps++;

        //Serial.print("Estado: ");
        //Serial.println(cuadrature_cnt);

        if (quarter_steps >= 4) {
            encoder++;
            quarter_steps = 0;
            Serial.println(encoder);
        }

        return EVENT_1;
    }

    // Sentido contrario:
    // 3 -> 1 -> 0 -> 2 -> 3
    if ((previous_state == 3 && cuadrature_cnt == 1) ||
        (previous_state == 1 && cuadrature_cnt == 0) ||
        (previous_state == 0 && cuadrature_cnt == 2) ||
        (previous_state == 2 && cuadrature_cnt == 3)) {

        quarter_steps--;

        //Serial.print("Estado: ");
        //Serial.println(cuadrature_cnt);

        if (quarter_steps <= -4) {
            encoder--;
            quarter_steps = 0;
            Serial.println(encoder);
        }

        return EVENT_2;
    }

    // Transicion invalida: cambiaron ambos bits.
    // Se actualiza el estado anterior para resincronizar.
    quarter_steps = 0;

    //Serial.print("Transicion invalida: ");
    //Serial.print(previous_state);
    //Serial.print(" -> ");
    //Serial.println(cuadrature_cnt);

    return (events)MAX_EVENTS;
}
