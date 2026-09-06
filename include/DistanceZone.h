#pragma once

// Representa las cuatro zonas de proximidad posibles del sistema
enum class DistanceZone {
    Near,        // Distancia menor o igual a 10 cm (LED Rojo)
    Medium,      // Distancia entre 10 y 20 cm (LED Amarillo)
    Far,         // Distancia entre 20 y 30 cm (LED Verde)
    OutOfRange   // Distancia mayor a 30 cm o sin eco (Todos los LEDs apagados)
};

// Función sencilla que determina la zona de proximidad según los centímetros
DistanceZone evaluateDistanceZone(float cm);
