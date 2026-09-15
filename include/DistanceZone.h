#pragma once

/**
 * @file DistanceZone.h
 * @brief Definición de las zonas de proximidad y función de evaluación.
 * 
 * Proyecto: Objeto Inteligente de Medición de Distancia y Semáforo LED
 * Microcontrolador: DOIT ESP32 DevKit v1
 */

// Representa las cuatro zonas de proximidad posibles del sistema
enum class DistanceZone {
    Near,        // Distancia menor o igual a 10.0 cm (LED Rojo)
    Medium,      // Distancia entre 10.0 y 20.0 cm (LED Amarillo)
    Far,         // Distancia entre 20.0 y 30.0 cm (LED Verde)
    OutOfRange   // Distancia mayor a 30.0 cm o sin eco/negativa (Todos los LEDs apagados)
};

/**
 * @brief Evalúa y clasifica una distancia en centímetros dentro de una zona de proximidad.
 * @param cm Distancia medida en centímetros (o valor negativo si ocurrió error/timeout).
 * @return DistanceZone Zona correspondiente (Near, Medium, Far, OutOfRange).
 */
DistanceZone evaluateDistanceZone(float cm);

