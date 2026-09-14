#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin, long timeoutMicros) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
    this->timeoutMicros = timeoutMicros;
}

void UltrasonicSensor::begin() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(triggerPin, LOW);
}

long UltrasonicSensor::measureEchoTime() {
    // 1. Limpiar el pin de disparo
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);

    // 2. Enviar pulso de 10 microsegundos para activar el ultrasonido
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // 3. Medir duración del eco en el pin de recepción con tiempo límite
    return pulseIn(echoPin, HIGH, timeoutMicros);
}

float UltrasonicSensor::measureDistanceCm() {
    long duracion = measureEchoTime();

    if (duracion == 0) {
        return -1.0f;   // antes: return 0.0f;
    }

    // Conversión a centímetros usando la velocidad del sonido en el aire
    return duracion * 0.01723f;
}