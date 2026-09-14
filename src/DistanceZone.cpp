#include "DistanceZone.h"

// Clasifica la distancia en centímetros según los rangos del sistema original
DistanceZone evaluateDistanceZone(float cm) {
    if (cm < 0.0f) {              //ahora: cm<=-1.0f antes: if (cm <= 0.0f)
        return DistanceZone::OutOfRange;
    } else if (cm <= 10.0f) {
        return DistanceZone::Near;
    } else if (cm <= 20.0f) {
        return DistanceZone::Medium;
    } else if (cm <= 30.0f) {
        return DistanceZone::Far;
    } else {
        return DistanceZone::OutOfRange;
    }
}
