
#include "DistanceZone.h"

// Clasifica la distancia en centímetros según los rangos del sistema original
DistanceZone evaluateDistanceZone(float cm) {
    if (cm < 0.0f) {
        return DistanceZone::OutOfRange; // Lectura errónea o sin eco (timeout -1.0f)
    } else if (cm <= 10.0f) {
        return DistanceZone::Near;       // 0.0 a 10.0 cm (Proximidad crítica -> LED Rojo)
    } else if (cm <= 20.0f) {
        return DistanceZone::Medium;     // 10.1 a 20.0 cm (Advertencia -> LED Amarillo)
    } else if (cm <= 30.0f) {
        return DistanceZone::Far;        // 20.1 a 30.0 cm (Zona segura -> LED Verde)
    } else {
        return DistanceZone::OutOfRange; // Mayor a 30.0 cm (Fuera de alcance -> LEDs apagados)
    }
}

