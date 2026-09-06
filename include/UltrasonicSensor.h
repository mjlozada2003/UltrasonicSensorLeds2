#pragma once

#include <Arduino.h>

// Clase para controlar el sensor ultrasónico HC-SR04
class UltrasonicSensor {
public:
    // Constructor: recibe los pines de disparo (trigger) y recepción (echo)
    UltrasonicSensor(int triggerPin, int echoPin, long timeoutMicros = 30000);

    // Configura los pines de entrada y salida del sensor
    void begin();

    // Mide y devuelve el tiempo del eco en microsegundos
    long measureEchoTime();

    // Calcula y devuelve la distancia directamente en centímetros
    float measureDistanceCm();

private:
    int triggerPin;
    int echoPin;
    long timeoutMicros;
};
