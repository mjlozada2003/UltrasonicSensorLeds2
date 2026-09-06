#include "DistanceIndicator.h"

DistanceIndicator::DistanceIndicator(int redPin, int yellowPin, int greenPin) {
    this->redPin = redPin;
    this->yellowPin = yellowPin;
    this->greenPin = greenPin;
}

void DistanceIndicator::begin() {
    pinMode(redPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    allOff();
}

void DistanceIndicator::allOff() {
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
}

void DistanceIndicator::update(DistanceZone zone) {
    switch (zone) {
        case DistanceZone::Near:
            // Cerca (menor o igual a 10 cm): únicamente el LED rojo encendido
            digitalWrite(redPin, HIGH);
            digitalWrite(yellowPin, LOW);
            digitalWrite(greenPin, LOW);
            break;

        case DistanceZone::Medium:
            // Distancia media (entre 10 y 20 cm): únicamente el LED amarillo encendido
            digitalWrite(redPin, LOW);
            digitalWrite(yellowPin, HIGH);
            digitalWrite(greenPin, LOW);
            break;

        case DistanceZone::Far:
            // Lejos (entre 20 y 30 cm): únicamente el LED verde encendido
            digitalWrite(redPin, LOW);
            digitalWrite(yellowPin, LOW);
            digitalWrite(greenPin, HIGH);
            break;

        case DistanceZone::OutOfRange:
        default:
            // Fuera de alcance (mayor a 30 cm o sin eco): todos los LEDs apagados
            allOff();
            break;
    }
}
