#include <Arduino.h>

float cm = 0;

// Pines LEDs
const int LED_ROJO = 33;
const int LED_AMARILLO = 25;
const int LED_VERDE = 26;

// Pines Sensor Ultrasónico
const int TRIGGER = 14;
const int ECHO = 27;


long readUltrasonicDistance()
{
  // Limpiar Trigger
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  // Enviar pulso ultrasónico
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  // Leer duración del eco
  return pulseIn(ECHO, HIGH, 30000);
}


void setup()
{
  // Configurar LEDs
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  // Configurar sensor
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  Serial.begin(9600);
}


void loop()
{
  long duracion = readUltrasonicDistance();

  // Si no se recibe respuesta
  if (duracion == 0)
  {
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_AMARILLO, LOW);
    digitalWrite(LED_VERDE, LOW);

    Serial.println("FUERA DE ALCANCE");
  }
  else
  {
    // Convertir a centímetros
    cm = duracion * 0.01723;

    Serial.print(cm);
    Serial.println(" cm");

    if (cm <= 10)
    {
      // Cerca
      digitalWrite(LED_ROJO, HIGH);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_VERDE, LOW);
    }
    else if (cm <= 20)
    {
      // Distancia media
      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_AMARILLO, HIGH);
      digitalWrite(LED_VERDE, LOW);
    }
    else if (cm <= 30)
    {
      // Lejos
      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_VERDE, HIGH);
    }
    else
    {
      // Fuera de alcance (>30 cm)
      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_VERDE, LOW);

      Serial.println("FUERA DE ALCANCE");
    }
  }

  delay(100);
}