# Addendum: Notas Técnicas y Opciones Consideradas

## 1. Notas sobre PlatformIO y Pruebas Unitarias
* **Configuración Serial:** Se identificó que `main.cpp` original usaba `9600` mientras `platformio.ini` especificaba `115200`. La decisión acordada es unificar a `115200` para optimizar velocidad y evitar caracteres corruptos en el monitor.
* **Entorno de Tests (`env:native`):** Para correr pruebas con Unity sin hardware físico conectado, la lógica de cálculo y clasificación de distancias debe estar libre de dependencias de `Arduino.h` (como `digitalWrite` o `pulseIn`). La clase `DistanceIndicator` puede exponer un método puro de cálculo de estado/zona que sea 100% testeable en PC.

## 2. Opciones de Depuración Evaluadas
* Se descartaron frameworks de logging pesados o librerías externas de terceros para no introducir dependencias innecesarias ni consumir recursos del microcontrolador.
* Se eligió la macro directa `#define DEBUG` / `#if DEBUG` o funciones inline sencillas como la alternativa más transparente y comprensible para cualquier programador.

## 3. Matriz de Casos de Prueba (Automáticos y Manuales)
| Caso | Distancia Simulada / Real | Comportamiento Esperado | Verificación |
|---|---|---|---|
| Timeout | Eco = 0 µs | Todos los LEDs apagados, "FUERA DE ALCANCE" | Automática + Manual |
| Límite Cercano | 5.0 cm | Solo LED Rojo encendido | Automática + Manual |
| Frontera Roja | 10.0 cm | Solo LED Rojo encendido | Automática + Manual |
| Frontera Amarilla | 10.1 cm - 20.0 cm | Solo LED Amarillo encendido | Automática + Manual |
| Frontera Verde | 20.1 cm - 30.0 cm | Solo LED Verde encendido | Automática + Manual |
| Fuera de Alcance | > 30.0 cm | Todos los LEDs apagados, "FUERA DE ALCANCE" | Automática + Manual |
