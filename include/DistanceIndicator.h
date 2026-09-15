#pragma once

/**
 * @file DistanceIndicator.h
 * @brief Controlador del semáforo visual de 3 LEDs con exclusión mutua.
 * 
 * Proyecto: Objeto Inteligente de Medición de Distancia y Semáforo LED
 * Microcontrolador: DOIT ESP32 DevKit v1
 */

#include <Arduino.h>
#include "DistanceZone.h"

// Clase para controlar el semáforo de tres LEDs
class DistanceIndicator {
public:
    /**
     * @brief Constructor del semáforo de distancia.
     * @param redPin Pin GPIO para el LED Rojo.
     * @param yellowPin Pin GPIO para el LED Amarillo.
     * @param greenPin Pin GPIO para el LED Verde.
     */
    DistanceIndicator(int redPin, int yellowPin, int greenPin);

    /**
     * @brief Inicializa los pines GPIO como salidas digitales (OUTPUT) y los apaga.
     */
    void begin();

    /**
     * @brief Conmuta los LEDs garantizando exclusión mutua según la zona de proximidad.
     * @param zone Zona evaluada (Near -> Rojo, Medium -> Amarillo, Far -> Verde, OutOfRange -> Todos apagados).
     */
    void update(DistanceZone zone);

    /**
     * @brief Apaga simultáneamente los tres LEDs.
     */
    void allOff();

private:
    int redPin;
    int yellowPin;
    int greenPin;
};

