#include <Arduino.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// ============================================================================
// CONFIGURACIÓN DE PINES
// ============================================================================

// --- Pines LCD Keypad Shield (100% compatibles con capture_a0.ino) ---
const int RS = 8;
const int EN = 9;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
const int pin_BL = 10; // Backlight

LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

// Pin analógico con escalera de resistencias de los 5 botones del Keypad Shield
const int pinKeypad = A0;

// --- Pines UART por Software hacia los reproductores MP3 YX5300 ---
// Pin 2: RX (Recibe retorno/feedback desde el pin COM del CD74HC4067)
// Pin 3: TX (Emite broadcast en paralelo hacia los pines RX de los 6 MP3)
const int PIN_MP3_RX = 2;
const int PIN_MP3_TX = 3;

SoftwareSerial mp3Serial(PIN_MP3_RX, PIN_MP3_TX);

// --- Pines de Selección del Multiplexor CD74HC4067 (S0 a S3) ---
// El pin ~EN del CD74HC4067 debe conectarse directamente a GND (siempre habilitado)
const int PIN_MUX_S0 = A1;
const int PIN_MUX_S1 = A2;
const int PIN_MUX_S2 = A3;
const int PIN_MUX_S3 = A4;

const uint8_t NUM_MODULES = 6;
const uint8_t MAX_TRACKS  = 10; // Ajustable según la cantidad de temas en la SD

// ============================================================================
// BOTONES DEL LCD KEYPAD SHIELD (Entrada analógica A0)
// ============================================================================
enum KeypadButton {
  BTN_NONE,
  BTN_RIGHT,
  BTN_UP,
  BTN_DOWN,
  BTN_LEFT,
  BTN_SELECT
};

// Lee A0 y clasifica según los umbrales típicos de voltaje del LCD Shield
KeypadButton readKeypadButton() {
  int adcValue = analogRead(pinKeypad);

  if (adcValue < 60)   return BTN_RIGHT;
  if (adcValue < 220)  return BTN_UP;
  if (adcValue < 390)  return BTN_DOWN;
  if (adcValue < 600)  return BTN_LEFT;
  if (adcValue < 820)  return BTN_SELECT;
  return BTN_NONE;
}

// ============================================================================
// FUNCIONES DE CONTROL DEL MULTIPLEXOR CD74HC4067
// ============================================================================
void muxSelect(uint8_t channel) {
  if (channel > 15) return;
  digitalWrite(PIN_MUX_S0, (channel & 0x01) ? HIGH : LOW);
  digitalWrite(PIN_MUX_S1, (channel & 0x02) ? HIGH : LOW);
  digitalWrite(PIN_MUX_S2, (channel & 0x04) ? HIGH : LOW);
  digitalWrite(PIN_MUX_S3, (channel & 0x08) ? HIGH : LOW);
  delayMicroseconds(5); // Retardo de conmutación del multiplexor
}

// ============================================================================
// PROTOCOLO YX5300 (Tramas UART a 9600 bps)
// ============================================================================
void mp3Broadcast(uint8_t cmd, uint8_t dataH, uint8_t dataL, uint8_t feedback = 0x00) {
  uint8_t packet[8] = {
    0x7E,       // Start byte
    0xFF,       // Version
    0x06,       // Length
    cmd,        // Command
    feedback,   // 0x00 = No feedback, 0x01 = Feedback
    dataH,      // Param MSB
    dataL,      // Param LSB
    0xEF        // End byte
  };
  mp3Serial.write(packet, 8);
  delay(25); // Breve espera para procesamiento en todos los chips
}

void multitrackInit() {
  mp3Serial.begin(9600);
  delay(500); // Espera a que los 6 módulos arranquen

  // Comando 0x09: Selección de dispositivo de almacenamiento (TF Card = 0x02)
  mp3Broadcast(0x09, 0x00, 0x02);
  delay(200);

  // Comando 0x06: Fijar volumen maestro en 30 (0x1E = máx)
  mp3Broadcast(0x06, 0x00, 0x1E);
  delay(100);
}

void multitrackPlay(uint16_t track) {
  // Comando 0x03: Play track con índice
  mp3Broadcast(0x03, (uint8_t)(track >> 8), (uint8_t)(track & 0xFF));
}

void multitrackStop() {
  // Comando 0x16: Stop
  mp3Broadcast(0x16, 0x00, 0x00);
}

void multitrackPause() {
  // Comando 0x0E: Pause
  mp3Broadcast(0x0E, 0x00, 0x00);
}

// Diagnóstico de un módulo individual usando el CD74HC4067
bool checkModuleOnline(uint8_t moduleIdx) {
  muxSelect(moduleIdx);
  while (mp3Serial.available()) mp3Serial.read(); // Vaciar buffer previo

  // Comando 0x42: Query status con feedback habilitado (0x01)
  mp3Broadcast(0x42, 0x00, 0x00, 0x01);

  unsigned long start = millis();
  while (millis() - start < 150) {
    if (mp3Serial.available() >= 8) {
      while (mp3Serial.available()) mp3Serial.read();
      return true;
    }
  }
  return false;
}

// ============================================================================
// GESTIÓN DE PANTALLA Y MENÚ
// ============================================================================
uint8_t currentTrack = 1;
bool isPlaying = false;

void showSplash() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ESIME CULHUACAN");
  lcd.setCursor(0, 1);
  lcd.print(" smpl multitrack");
  delay(2000);

  // Escaneo y reporte rápido de los 6 módulos en la cortinilla
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando 6 MP3s");
  lcd.setCursor(0, 1);
  lcd.print("Mux:");

  uint8_t okCount = 0;
  for (uint8_t i = 0; i < NUM_MODULES; i++) {
    bool ok = checkModuleOnline(i);
    lcd.setCursor(5 + i, 1);
    lcd.print(ok ? (char)('1' + i) : '-');
    if (ok) okCount++;
    delay(40);
  }
  delay(1200);
}

void updateMenuDisplay() {
  lcd.clear();
  // Línea 0: Pista seleccionada y estado de reproducción
  lcd.setCursor(0, 0);
  lcd.print("Track: <");
  if (currentTrack < 10) lcd.print('0');
  lcd.print(currentTrack);
  lcd.print(">");

  lcd.setCursor(11, 0);
  if (isPlaying) {
    lcd.print("[PLAY]");
  } else {
    lcd.print("[STOP]");
  }

  // Línea 1: Guía de los 2 botones asignados
  lcd.setCursor(0, 1);
  if (isPlaying) {
    lcd.print("SEL:Trk LFT:STOP");
  } else {
    lcd.print("SEL:Trk LFT:PLAY");
  }
}

// ============================================================================
// SETUP Y LOOP PRINCIPAL
// ============================================================================
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Configurar pines de selección del CD74HC4067
  pinMode(PIN_MUX_S0, OUTPUT);
  pinMode(PIN_MUX_S1, OUTPUT);
  pinMode(PIN_MUX_S2, OUTPUT);
  pinMode(PIN_MUX_S3, OUTPUT);
  muxSelect(0);

  // Iniciar LCD
  lcd.begin(16, 2);

  // Iniciar UART de depuración hacia PC (Pines 0 y 1)
  Serial.begin(115200);
  Serial.println(F("=== ESIME CULHUACAN - SISTEMA AUTONOMO MULTITRACK ==="));

  // Inicializar UART y módulos MP3 ANTES de la cortinilla
  // (necesario para que checkModuleOnline() pueda comunicarse con los chips)
  multitrackInit();
  pinMode(PIN_MP3_RX, INPUT_PULLUP); // Evita lecturas flotantes al conmutar el multiplexor

  // Cortinilla inicial con diagnóstico de los 6 módulos
  showSplash();

  // Mostrar menú principal
  updateMenuDisplay();
}

void loop() {
  static KeypadButton lastReading = BTN_NONE;
  static KeypadButton debouncedButton = BTN_NONE;
  static unsigned long lastDebounceTime = 0;
  const unsigned long debounceDelay = 50; // ms de anti-rebote

  KeypadButton currentReading = readKeypadButton();

  // Si cambió la lectura del ADC (por ruido o pulsación), reiniciar temporizador
  if (currentReading != lastReading) {
    lastDebounceTime = millis();
    lastReading = currentReading;
  }

  // Si la lectura se mantuvo estable más del tiempo de debounce
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Si el estado estable cambió respecto al último estado procesado
    if (currentReading != debouncedButton) {
      debouncedButton = currentReading;

      // --- ACCIONES AL PRESIONAR BOTÓN (Flanco positivo) ---

      // BOTÓN SELECT: Cambiar de pista
      if (debouncedButton == BTN_SELECT) {
        currentTrack++;
        if (currentTrack > MAX_TRACKS) {
          currentTrack = 1;
        }
        Serial.print(F("Pista seleccionada: "));
        Serial.println(currentTrack);

        // Si estaba sonando, cambiar de pista reinicia la reproducción en la nueva pista
        if (isPlaying) {
          multitrackPlay(currentTrack);
        }
        updateMenuDisplay();
      }

      // BOTÓN LEFT: Trigger / Toggle orden a los MP3 (Play / Stop)
      else if (debouncedButton == BTN_LEFT) {
        if (!isPlaying) {
          Serial.print(F("DISPARANDO MULTITRACK - Pista: "));
          Serial.println(currentTrack);
          multitrackPlay(currentTrack);
          isPlaying = true;
          digitalWrite(LED_BUILTIN, HIGH);
        } else {
          Serial.println(F("DETENIENDO MULTITRACK"));
          multitrackStop();
          isPlaying = false;
          digitalWrite(LED_BUILTIN, LOW);
        }
        updateMenuDisplay();
      }
    }
  }
}




