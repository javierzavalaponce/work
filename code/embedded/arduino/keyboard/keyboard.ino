#include <LiquidCrystal.h>
#include <Keypad.h>

// --- LCD ---
const int RS = 8;
const int EN = 9;
const int D4 = 4;
const int D5 = 5;
const int D6 = 6;
const int D7 = 7;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// --- Keypad ---
const byte FILAS = 4;
const byte COLUMNAS = 3;

char keys[FILAS][COLUMNAS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[FILAS] = {A0, A1, A2, A3};    // Ajusta según tu conexión
byte colPins[COLUMNAS] = {A4, A5, 2};       // Ajusta según tu conexión

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, FILAS, COLUMNAS);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Presiona un boton");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Boton presionado:");
    lcd.setCursor(0, 1);
    lcd.print(key);
  }
}