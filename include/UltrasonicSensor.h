#pragma once

/**
 * @file UltrasonicSensor.h
 * @brief Controlador del sensor ultrasónico HC-SR04.
 * 
 * Proyecto: Objeto Inteligente de Medición de Distancia y Semáforo LED
 * Microcontrolador: DOIT ESP32 DevKit v1
 */

#include <Arduino.h>

// Clase para controlar el sensor ultrasónico HC-SR04
class UltrasonicSensor {
public:
    /**
     * @brief Constructor del sensor ultrasónico.
     * @param triggerPin Pin GPIO conectado al Trigger del sensor.
     * @param echoPin Pin GPIO conectado al Echo del sensor.
     * @param timeoutMicros Tiempo límite en microsegundos para pulseIn (por defecto 30000 µs = 30 ms).
     */
    UltrasonicSensor(int triggerPin, int echoPin, long timeoutMicros = 30000);

    /**
     * @brief Configura los modos de los pines (OUTPUT para Trigger, INPUT para Echo).
     */
    void begin();

    /**
     * @brief Emite el pulso de disparo de 10 µs y mide la duración del eco.
     * @return Duración del pulso de eco en microsegundos, o 0 si ocurrió timeout.
     */
    long measureEchoTime();

    /**
     * @brief Mide el eco y calcula la distancia en centímetros usando la velocidad del sonido.
     * @return Distancia en centímetros, o -1.0f si no hubo eco (timeout).
     */
    float measureDistanceCm();

private:
    int triggerPin;
    int echoPin;
    long timeoutMicros;
};

