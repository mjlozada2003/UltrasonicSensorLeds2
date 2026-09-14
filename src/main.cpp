#include <Arduino.h>
#include "UltrasonicSensor.h"
#include "DistanceIndicator.h"
#include "DistanceZone.h"

// =====================================================================
// Configuración de Salidas de Depuración (Debugging)
// =====================================================================
// Esta variable booleana controla si se muestran mensajes de ayuda
// en el monitor serie para diagnosticar el estado del sensor y los LEDs.
// - true: Muestra mensajes detallados de depuración.
// - false: Muestra únicamente la salida estándar limpia.
const bool debugActivo = false;

// =====================================================================
// Pines del Microcontrolador (Variables en camelCase, sin guiones bajos)
// =====================================================================
const int ledRojo = 33;
const int ledAmarillo = 25;
const int ledVerde = 26;

const int pinTrigger = 14;
const int pinEcho = 27;
const unsigned long intervaloLecturaMs = 100;   // intervalo de tiempo entre lecturas del sensor en milisegundos
unsigned long ultimaLecturaMs = 0;              // guarda el momento de la última lectura

// =====================================================================
// Creación de los Objetos
// =====================================================================
UltrasonicSensor sensor(pinTrigger, pinEcho);
DistanceIndicator indicator(ledRojo, ledAmarillo, ledVerde);

// Función sencilla para explicar en la consola serie el estado del sistema
void imprimirDepuracion(float cm, DistanceZone zone) {
  if (debugActivo) {
    Serial.print("[Depuración] Distancia leída: ");
    Serial.print(cm);
    Serial.print(" cm | Zona evaluada: ");
    if (zone == DistanceZone::Near) {
      Serial.println("Cerca (Activo: LED Rojo)");
    } else if (zone == DistanceZone::Medium) {
      Serial.println("Media (Activo: LED Amarillo)");
    } else if (zone == DistanceZone::Far) {
      Serial.println("Lejos (Activo: LED Verde)");
    } else {
      Serial.println("Fuera de rango (Todos los LEDs apagados)");
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Inicializar el sensor ultrasónico y el semáforo LED
  sensor.begin();
  indicator.begin();
}

void loop() {
  unsigned long ahora = millis();

  if (ahora - ultimaLecturaMs >= intervaloLecturaMs) {
    ultimaLecturaMs = ahora;

    // 1. Obtener la distancia medida en centímetros
    float cm = sensor.measureDistanceCm();

    // 2. Salida estándar idéntica al código original
    if (cm <= 0.0f) {
      Serial.println("FUERA DE ALCANCE");
    } else {
      Serial.print(cm);
      Serial.println(" cm");
      if (cm > 30.0f) {
        Serial.println("FUERA DE ALCANCE");
      }
    }

    // 3. Determinar la zona de proximidad correspondiente
    DistanceZone zone = evaluateDistanceZone(cm);

    // 4. Actualizar el semáforo LED con exclusión mutua
    indicator.update(zone);

    // 5. Imprimir información de depuración si debugActivo es true
    imprimirDepuracion(cm, zone);
  }
}
