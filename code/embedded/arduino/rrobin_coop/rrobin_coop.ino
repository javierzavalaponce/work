#define TASKS 3

uint8_t currentTask = 0;

void task1() {
  PORTB ^= (1 << PB0); // toggle pin 8
}

void task2() {
  PORTB ^= (1 << PB1); // toggle pin 9
}

void task3() {
  // tarea dummy
}

void (*taskTable[TASKS])() = {task1, task2, task3};

void setup() {
  DDRB |= (1 << PB0) | (1 << PB1);
}

void loop() {

  taskTable[currentTask]();

  currentTask++;
  if (currentTask >= TASKS)
    currentTask = 0;

  delay(200);  // cede voluntariamente
}

