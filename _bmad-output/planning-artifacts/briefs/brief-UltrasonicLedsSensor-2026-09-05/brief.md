---
title: "Product Brief: Refactorización a POO, Testing y Debugging para UltrasonicLedsSensor"
status: complete
created: 2026-09-05
updated: 2026-09-05
---

# Product Brief: UltrasonicLedsSensor (POO, Testing y Debugging)

## 1. Resumen Ejecutivo (Executive Summary)
El proyecto **UltrasonicLedsSensor** cuenta con una base de hardware y software funcional en ESP32 (PlatformIO) que mide distancias mediante un sensor ultrasónico HC-SR04 y notifica la proximidad activando de forma mutuamente excluyente tres LEDs (rojo, amarillo y verde).

El objetivo de esta iniciativa es refactorizar el código fuente actual desde una estructura secuencial/monolítica en `main.cpp` hacia un diseño **Orientado a Objetos (POO)** limpio y didáctico, incorporar **salidas de depuración configurables** mediante flags sencillos de preprocesador y dotar al proyecto de **pruebas automáticas y manuales**. Todo esto se realiza bajo la restricción inmutable de **preservar el 100% de la funcionalidad actual, los pines asignados y los umbrales de distancia exactos**, priorizando la legibilidad para que cualquier desarrollador o estudiante pueda comprenderlo sin sobreingeniería.

## 2. El Problema (The Problem)
Actualmente, el archivo `src/main.cpp` concentra todas las responsabilidades: control de tiempos de pulso, conversión matemática de microsegundos a centímetros, lógica condicional de umbrales y manejo directo de pines GPIO de salida.
* **Falta de modularidad:** No es fácil reutilizar el sensor o el indicador LED de forma independiente.
* **Dificultad de prueba automática:** La lógica de clasificación de rangos está fuertemente acoplada a las lecturas físicas de hardware (`pulseIn`) y a las escrituras en pines (`digitalWrite`), lo que impide validar el software sin hardware conectado.
* **Depuración invasiva y desajuste de baudios:** La información se imprime directamente en la salida serie estándar compartida a 9600 baudios, existiendo un desfase con la configuración de 115200 de PlatformIO.

## 3. La Solución (The Solution)
Reestructurar la base de código respetando la arquitectura estándar de PlatformIO en módulos comprensibles y testeables:

1. **Diseño Orientado a Objetos Comprensible:**
   * **`UltrasonicSensor`:** Clase responsable del sensor ultrasónico (Trigger y Echo). Encapsula el pulso de disparo de $10\,\mu\text{s}$, medición y conversión a centímetros.
   * **`DistanceIndicator`:** Clase responsable del semáforo de 3 LEDs. Recibe los pines y actualiza el estado de los LEDs según la matriz de umbrales.
   * **`DistanceZone`:** Tipo enumerado sencillo (`NEAR`, `MEDIUM`, `FAR`, `OUT_OF_RANGE`) que permite que la clasificación lógica sea pura y desacoplada del hardware para facilitar los tests unitarios.

2. **Sistema de Depuración Flexible:**
   * Estandarización de velocidad serie a **115200 baudios**.
   * Uso de directivas sencillas (`#define DEBUG 1` o `0`) que permitan habilitar o silenciar detalles técnicos (tiempos de eco, zona detectada, estados GPIO) manteniendo una salida limpia para uso normal.

3. **Estrategia Integral de Pruebas:**
   * **Pruebas Automáticas (Unity en PlatformIO):** Entorno de pruebas (`test/`) ejecutable de forma nativa en la computadora (o en placa) que inyecta valores de distancia simulados (ej. 5 cm, 10 cm, 15 cm, 20 cm, 25 cm, 30 cm, 35 cm, timeout 0) y valida que la zona calculada y el LED correspondiente sean exactamente los esperados.
   * **Pruebas Manuales Guiadas:** Procedimiento documentado y checklist paso a paso con obstáculos a distancias conocidas para validación física en protoboard.

## 4. Hardware y Reglas Funcionales Intocables
* **Pines ESP32:**
  * Sensor Ultrasónico: Trigger = **GPIO 14**, Echo = **GPIO 27**.
  * LEDs: Rojo = **GPIO 33**, Amarillo = **GPIO 25**, Verde = **GPIO 26**.
* **Matriz de Comportamiento:**
  * $\le 10\text{ cm} \rightarrow$ Solo LED Rojo encendido.
  * $> 10\text{ cm}$ y $\le 20\text{ cm} \rightarrow$ Solo LED Amarillo encendido.
  * $> 20\text{ cm}$ y $\le 30\text{ cm} \rightarrow$ Solo LED Verde encendido.
  * $> 30\text{ cm}$ o eco nulo ($0\,\mu\text{s}$) $\rightarrow$ Todos apagados + mensaje `"FUERA DE ALCANCE"`.

## 5. Alcance (Scope)
* **Dentro del alcance (In Scope):**
  * Creación de clases `UltrasonicSensor` y `DistanceIndicator` con archivos `.h` y `.cpp` separados.
  * Simplificación de `src/main.cpp` para actuar como orquestador claro y legible.
  * Salidas serie formateadas y conmutables mediante `#define DEBUG`.
  * Tests automáticos unitarios en `test/` usando el framework Unity de PlatformIO.
  * Guía de verificación manual.
* **Fuera del alcance (Out of Scope):**
  * Cambios en la asignación física de pines o en el circuito.
  * Modificación de los umbrales de distancia (10, 20, 30 cm).
  * Patrones de diseño complejos o sobrecargados (sin abstracciones innecesarias ni inyección de dependencias pesada).
  * Componentes de hardware adicionales (sin buzzer, sin pantallas por ahora).

## 6. Criterios de Éxito (Success Criteria)
1. **Preservación funcional al 100%:** El circuito físico responde idénticamente al código original en todos los rangos de distancia.
2. **Comprensibilidad:** Código autoexplicativo, con nombres claros de métodos y variables, legible para principiantes e intermedios.
3. **Tests automáticos exitosos:** Ejecución de pruebas unitarias con 100% de aserciones aprobadas para todos los casos límite (0, 10, 20, 30, >30 cm).
4. **Depuración bajo demanda:** Posibilidad de compilar con o sin trazas detalladas modificando un único flag.
