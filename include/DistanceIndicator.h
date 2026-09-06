#pragma once

#include <Arduino.h>
#include "DistanceZone.h"

// Clase para controlar el semáforo de tres LEDs
class DistanceIndicator {
public:
    // Constructor: recibe los pines de cada LED
    DistanceIndicator(int redPin, int yellowPin, int greenPin);

    // Configura los pines como salidas y los apaga inicialmente
    void begin();

    // Actualiza qué LED debe encenderse según la zona evaluada
    void update(DistanceZone zone);

    // Apaga simultáneamente los tres LEDs
    void allOff();

private:
    int redPin;
    int yellowPin;
    int greenPin;
};
