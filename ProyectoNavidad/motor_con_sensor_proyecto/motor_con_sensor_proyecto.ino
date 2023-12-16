#include <Arduino.h>

// Definir los pines del motor
#define PIN_A 2
#define PIN_B 4
#define PIN_C 5
#define PIN_D 14

// Definir los pines del sensor ultrasónico
#define TRIG_PIN 19
#define ECHO_PIN 13

// Definir los umbrales de distancia para activar/desactivar el motor
#define DISTANCE_THRESHOLD_CLOSE 10  // Ajusta este valor según sea necesario
#define DISTANCE_THRESHOLD_FAR 30    // Ajusta este valor según sea necesario

// Tiempo de espera entre pasos (microsegundos)
#define DELAY 2000

void setup() {
  // Configurar los pines del motor como salida
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);

  // Configurar los pines del sensor ultrasónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void stepForward() {
  digitalWrite(PIN_D, HIGH);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_A, HIGH);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_B, HIGH);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_C, HIGH);
  delayMicroseconds(DELAY);

  digitalWrite(PIN_D, LOW);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_A, LOW);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_B, LOW);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_C, LOW);
  delayMicroseconds(DELAY);
}

void stepBackward() {
  digitalWrite(PIN_C, HIGH);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_B, HIGH);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_A, HIGH);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_D, HIGH);
  delayMicroseconds(DELAY);

  digitalWrite(PIN_C, LOW);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_B, LOW);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_A, LOW);
  delayMicroseconds(DELAY);
  digitalWrite(PIN_D, LOW);
  delayMicroseconds(DELAY);
}

int getDistance() {
  // Generar pulso ultrasónico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Medir el tiempo de vuelo del pulso ultrasónico
  int duration = pulseIn(ECHO_PIN, HIGH);

  // Calcular la distancia en centímetros
  int distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  // Obtener la distancia utilizando el sensor ultrasónico
  int distance = getDistance();

  // Realizar acciones en función de la distancia
  if (distance < DISTANCE_THRESHOLD_CLOSE) {
    // Girar en sentido horario (avance)
    for (int i = 0; i < 200; i++) {
      stepForward();
    }
  } else if (distance > DISTANCE_THRESHOLD_FAR) {
    // Girar en sentido antihorario (retroceso)
    for (int i = 0; i < 200; i++) {
      stepBackward();
    }
  }
  // Si la distancia está entre los umbrales, el motor se detendrá.

  // Esperar un segundo antes de realizar la próxima medición
  delay(1000);
}