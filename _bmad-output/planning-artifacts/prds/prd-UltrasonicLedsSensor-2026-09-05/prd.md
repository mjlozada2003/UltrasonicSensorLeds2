---
title: "PRD: Sistema de Medición y Alerta Visual de Proximidad (UltrasonicLedsSensor)"
status: final
created: 2026-09-05
updated: 2026-09-05
---

# PRD: Sistema de Medición y Alerta Visual de Proximidad (UltrasonicLedsSensor)

## 0. Propósito del Documento
Este documento de Requerimientos de Producto (PRD) especifica de forma integral y verificable el comportamiento funcional, técnico y arquitectónico del sistema embebido **UltrasonicLedsSensor**, desarrollado sobre el microcontrolador ESP32 y el framework Arduino en PlatformIO.

El proyecto está concebido con un **propósito académico y didáctico**: además de operar como un detector de proximidad físico confiable con señalización visual por semáforo LED, sirve como caso de estudio ejemplar de **buenas prácticas de ingeniería de software embebido**, demostrando Programación Orientada a Objetos (POO) limpia, telemetría y diagnóstico conmutable, y verificación rigurosa mediante pruebas unitarias automáticas (Unity) y manuales.

---

## 1. Visión
El sistema **UltrasonicLedsSensor** proporciona una solución autónoma de monitoreo de distancia en tiempo real que adquiere datos acústicos del entorno mediante un sensor ultrasónico HC-SR04, procesa la cinemática de tiempo de vuelo en el ESP32, clasifica la proximidad en zonas de alerta mutuamente excluyentes y comanda un conjunto de 3 actuadores LED (verde, amarillo y rojo), reportando simultáneamente telemetría y diagnósticos a través de un enlace serie UART a 115200 baudios.

El sistema se distingue por:
1. **Fidelidad funcional rigurosa:** Cumplimiento exacto de los umbrales de proximidad y reglas de hardware preestablecidas.
2. **Claridad pedagógica antes que complejidad:** Código modular, estructurado en clases comprensibles para cualquier estudiante o ingeniero, sin sobreingeniería.
3. **Testabilidad total:** Desacoplamiento de la lógica de decisión para permitir su ejecución y validación automática instantánea en la computadora de desarrollo sin depender de la conexión física del microcontrolador.

---

## 2. Usuarios Objetivo y Casos de Uso

### 2.1 Jobs To Be Done (JTBD)
* **Para el Estudiante / Desarrollador:** Desarrollar e implementar un firmware embebido robusto que trascienda el código secuencial monolítico tradicional, demostrando cómo estructurar clases limpias, gestionar depuración sin saturar el bus de comunicaciones y verificar el software con pruebas unitarias profesionales.
* **Para el Docente / Evaluador Académico:** Disponer de un proyecto con especificaciones claras, trazabilidad completa y capacidad de comprobación dual: ejecución de pruebas unitarias automatizadas en consola (`pio test`) y comprobación física de laboratorio en protoboard.

### 2.2 No-Usuarios (v1)
* Sistemas industriales de misión crítica o automoción certificados bajo estándares ISO 26262 (ASIL) o IEC 61508 (SIL). El presente desarrollo es un prototipo experimental y formativo.

### 2.3 Recorridos de Usuario Clave (Key User Journeys)

* **UJ-1: Verificación de Comportamiento Físico en Banco de Pruebas**
  * **Persona y contexto:** María (estudiante) ensambla el circuito en protoboard, conecta el ESP32 a su computadora por USB y compila el firmware mediante PlatformIO.
  * **Estado inicial:** Sistema alimentado a 5V/3.3V, puerto serie abierto a 115200 baudios.
  * **Secuencia:** 
    1. María coloca un obstáculo a 25 cm: el LED verde se enciende de forma fija y la consola imprime la distancia en centímetros.
    2. Acerca el obstáculo a 15 cm: el LED verde se apaga de inmediato y se enciende el LED amarillo.
    3. Acerca el obstáculo a 8 cm: el LED amarillo se apaga y se enciende el LED rojo.
    4. Retira el obstáculo a más de 35 cm: todos los LEDs se apagan y la consola notifica `"FUERA DE ALCANCE"`.
  * **Resultado:** El semáforo visual responde sin titubeos ni encendidos solapados.

* **UJ-2: Evaluación y Calificación Automatizada sin Hardware**
  * **Persona y contexto:** Carlos (docente evaluador) descarga el repositorio del estudiante en su laptop sin tener una placa ESP32 a la mano.
  * **Estado inicial:** Entorno PlatformIO instalado en la terminal.
  * **Secuencia:** 
    1. Carlos ejecuta el comando `pio test -e native` en la raíz del proyecto.
    2. La suite de pruebas basada en Unity compila y ejecuta en segundos los casos de prueba sobre la lógica de clasificación de distancias.
    3. Todos los asertos (casos límite en 0, 10, 20, 30 cm y fuera de rango) resultan aprobados (PASS).
  * **Resultado:** El docente valida de forma objetiva la corrección algorítmica del código sin requerir montaje físico.

* **UJ-3: Diagnóstico y Depuración Técnica en Laboratorio**
  * **Persona y contexto:** María detecta fluctuaciones imprevistas en la lectura del sensor y requiere diagnosticar la señal cruda.
  * **Estado inicial:** Firmware con directiva `#define DEBUG 1` compilada.
  * **Secuencia:** 
    1. María abre el monitor serie.
    2. El sistema emite, además de la distancia neta, los microsegundos capturados en el pin Echo y la zona de proximidad evaluada.
    3. María identifica si el problema es un rebote acústico o una pérdida de eco (timeout a 30 ms).
  * **Resultado:** Diagnóstico rápido del sensor sin alterar la lógica de los actuadores.

---

## 3. Glosario de Términos
* **Sensor Ultrasónico:** Dispositivo transductor HC-SR04 que emite ondas acústicas de alta frecuencia (40 kHz) y mide el intervalo transcurrido hasta recibir el eco reflejado.
* **Pin Trigger (Disparo):** Terminal digital de salida (GPIO 14) excitada con un pulso positivo de 10 µs para iniciar la ráfaga ultrasónica.
* **Pin Echo (Eco):** Terminal digital de entrada (GPIO 27) cuyo nivel lógico alto refleja la duración del tiempo de vuelo de la señal acústica.
* **Tiempo de Vuelo (Time-of-Flight):** Intervalo de tiempo en microsegundos transcurrido entre la emisión del pulso ultrasónico y la detección del rebote.
* **Constante Acústica:** Factor de escala cinemático ($0.01723\,\text{cm}/\mu\text{s}$) que traduce la duración del pulso a distancia lineal de ida, considerando la velocidad del sonido en el aire a ~20°C ($\approx 343\,\text{m/s}$).
* **DistanceZone (Zona de Proximidad):** Enumerador de estados lógicos discretos que clasifican la distancia: `NEAR` (Cerca), `MEDIUM` (Medio), `FAR` (Lejos) y `OUT_OF_RANGE` (Fuera de Rango).
* **Exclusión Mutua:** Propiedad de diseño por la cual, en cualquier instante, a lo sumo un único LED puede permanecer encendido.
* **Fuera de Alcance:** Condición originada cuando la distancia calculada excede los 30.0 cm o cuando no se recibe eco dentro de la ventana de 30 ms (duración = 0 µs).
* **Telemetría Serie:** Envío periódico de datos formateados al monitor serie a 115200 baudios.
* **Modo Debug:** Mecanismo de preprocesamiento condicional (`#define DEBUG`) que activa o desactiva la emisión de trazas de diagnóstico detalladas.

---

## 4. Requerimientos Funcionales (FR)

### 4.1 Subsistema de Adquisición Ultrasónica (`UltrasonicSensor`)
**Descripción:** Encapsula la interacción directa con el transductor HC-SR04, administrando los tiempos de disparo y la medición de respuesta en microsegundos. Realiza UJ-1 y UJ-3.

* **FR-1:** El sistema debe inicializar el pin `TRIGGER` como salida digital y el pin `ECHO` como entrada digital durante el arranque.
  * *Verificación:* Pines configurados en `pinMode` en la función de inicialización.
* **FR-2:** Para cada ciclo de medición, el sistema debe limpiar la línea Trigger manteniéndola en nivel bajo por al menos 2 µs, y luego generar un pulso de activación en nivel alto de exactamente 10 µs.
  * *Verificación:* Medición de pulso con analizador lógico o temporización de microsegundos.
* **FR-3:** El sistema debe registrar la duración del pulso alto en el pin Echo utilizando un tiempo límite de espera (timeout) de 30.000 µs (30 ms).
  * *Verificación:* Ausencia de bloqueo indefinido en caso de desconexión física del sensor.
* **FR-4:** El sistema debe convertir la duración del eco a distancia métrica en centímetros mediante la fórmula $d = t \times 0.01723$.
  * *Verificación:* Un eco de 580 µs debe retornar aproximadamente $10.0\,\text{cm} \pm 0.1\,\text{cm}$.
* **FR-5:** Si la duración del eco es cero (timeout por falta de rebote), el sistema debe reportar una distancia nula o indicar condición de fuera de alcance.

### 4.2 Lógica de Clasificación de Proximidad
**Descripción:** Algoritmo puro de evaluación que clasifica un valor numérico de distancia en un estado del enumerador `DistanceZone`. Realiza UJ-1 y UJ-2.

* **FR-6 (Zona Cercana / Crítica):** Si la distancia $d$ es mayor a 0 y menor o igual a 10.0 cm ($0 < d \le 10.0$), el sistema debe clasificar el estado como `DistanceZone::NEAR`.
* **FR-7 (Zona Media / Advertencia):** Si la distancia $d$ es mayor a 10.0 cm y menor o igual a 20.0 cm ($10.0 < d \le 20.0$), el sistema debe clasificar el estado como `DistanceZone::MEDIUM`.
* **FR-8 (Zona Lejana / Normal):** Si la distancia $d$ es mayor a 20.0 cm y menor o igual a 30.0 cm ($20.0 < d \le 30.0$), el sistema debe clasificar el estado como `DistanceZone::FAR`.
* **FR-9 (Zona Fuera de Alcance):** Si la distancia $d$ es mayor a 30.0 cm o si el valor es 0 (ausencia de eco), el sistema debe clasificar el estado como `DistanceZone::OUT_OF_RANGE`.
* **FR-10 (Función Pura Testeable):** La lógica de clasificación debe implementarse como una función o método puro, independiente de dependencias directas del microcontrolador (sin llamadas a registros ni `digitalWrite`), permitiendo su prueba unitaria directa en compiladores host.

### 4.3 Subsistema de Señalización Visual (`DistanceIndicator`)
**Descripción:** Gestiona el estado eléctrico de los tres actuadores LED garantizando exclusión mutua. Realiza UJ-1.

* **FR-11:** El sistema debe configurar los pines de los LEDs como salidas digitales durante la inicialización:
  * LED Rojo en **GPIO 33**
  * LED Amarillo en **GPIO 25**
  * LED Verde en **GPIO 26**
* **FR-12:** Ante el estado `DistanceZone::NEAR`, el sistema debe encender exclusivamente el LED Rojo (GPIO 33 en nivel alto) y mantener apagados el Amarillo y el Verde (GPIO 25 y 26 en nivel bajo).
* **FR-13:** Ante el estado `DistanceZone::MEDIUM`, el sistema debe encender exclusivamente el LED Amarillo (GPIO 25 en nivel alto) y mantener apagados el Rojo y el Verde (GPIO 33 y 26 en nivel bajo).
* **FR-14:** Ante el estado `DistanceZone::FAR`, el sistema debe encender exclusivamente el LED Verde (GPIO 26 en nivel alto) y mantener apagados el Rojo y el Amarillo (GPIO 33 y 25 en nivel bajo).
* **FR-15:** Ante el estado `DistanceZone::OUT_OF_RANGE`, el sistema debe apagar simultáneamente los tres LEDs (GPIO 33, 25 y 26 en nivel bajo).
* **FR-16 (Exclusión Mutua):** Bajo ninguna circunstancia operativa debe permitirse que dos o más LEDs permanezcan encendidos simultáneamente durante un ciclo de visualización.

### 4.4 Subsistema de Telemetría y Diagnóstico Serie
**Descripción:** Comunicación serie bidireccional / monitoreo a través de UART0. Realiza UJ-1 y UJ-3.

* **FR-17:** La interfaz serie debe inicializarse a una velocidad de transmisión de **115200 baudios**, sincronizada con el parámetro `monitor_speed` de PlatformIO.
* **FR-18 (Telemetría Estándar):** En operación normal, el sistema debe emitir por el puerto serie:
  * El valor numérico de la distancia con formato `"<valor> cm"` cuando la distancia esté dentro del rango válido ($\le 30.0\,\text{cm}$).
  * La cadena `"FUERA DE ALCANCE"` cuando la distancia supere los 30.0 cm o el eco sea nulo.
* **FR-19 (Diagnóstico Extendido Debug):** Si la macro `#define DEBUG 1` está activa, el sistema debe emitir trazas adicionales en cada ciclo indicando: duración cruda en microsegundos, zona calculada y estado de los actuadores.
* **FR-20 (Silencio de Depuración):** Si `#define DEBUG 0` (o no está definido), las trazas de diagnóstico no deben generar código ejecutable ni consumir ancho de banda en la consola serie.

### 4.5 Ciclo de Control y Temporización
* **FR-21:** El lazo principal debe ejecutar un ciclo de lectura y actualización periódica con una cadencia aproximada de 100 ms (~10 Hz), evitando lecturas ultrasónicas ultrasónicas continuas que generen ecos residuales inter-pulso.

---

## 5. Requerimientos No Funcionales (NFR)

* **NFR-1 (Latencia y Tiempo de Respuesta):** La transición visual de los LEDs tras el cambio de posición de un objeto debe ocurrir en un tiempo menor o igual a 150 ms (tiempo de ciclo de muestreo + medición).
* **NFR-2 (Determinismo y Estabilidad):** El sistema debe comportarse de manera determinista; ningún estado de distancia debe quedar indefinido ni provocar un bloqueo infinito del procesador.
* **NFR-3 (Comprensibilidad y Calidad Didáctica de Código):**
  * Nombres de clases, métodos y variables en inglés/español consistentes y autoexplicativos.
  * Separación estricta de interfaz (`.h`) e implementación (`.cpp`).
  * Ausencia de optimizaciones prematuras o trucos de bajo nivel que oscurezcan la intención del algoritmo.
* **NFR-4 (Restricciones Eléctricas del ESP32):**
  * Los pines GPIO del ESP32 operan a 3.3V de nivel lógico. El circuito debe contemplar resistencias en serie para los LEDs (220 Ω a 330 Ω) garantizando que la corriente por pin se mantenga por debajo de los 12 mA recomendados.
  * [SUPOSICIÓN] Se asume que el sensor HC-SR04 utilizado es compatible con 3.3V (modelo HC-SR04P o RCWL-1601) o que el pin Echo cuenta con un divisor resistivo simple (ej. 1kΩ y 2kΩ) para proteger el GPIO 27 del ESP32 contra tensiones de 5V.

---

## 6. No-Objetivos Explícitos (Non-Goals)

1. **No modulación PWM de intensidad:** Los LEDs operan como salidas booleanas digitales (ON/OFF), no se implementará desvanecimiento gradual ni brillo variable.
2. **No alertas sonoras:** No se incluirá buzzer, generador de tonos ni altavoz piezoeléctrico en esta fase.
3. **No pantallas externas:** No se incluirán librerías para displays OLED (SSD1306) ni pantallas LCD (I2C 1602).
4. **No conectividad de red:** El microcontrolador funcionará como sistema aislado (stand-alone), sin activación de WiFi, Bluetooth ni protocolos IoT (MQTT, HTTP).
5. **No modificación de hardware existente:** No se alterarán los pines físicos preexistentes ni los umbrales de 10, 20 y 30 cm.

---

## 7. Alcance del MVP

### 7.1 En Alcance (In Scope)
* Clase `UltrasonicSensor` (`include/UltrasonicSensor.h`, `src/UltrasonicSensor.cpp`).
* Clase `DistanceIndicator` (`include/DistanceIndicator.h`, `src/DistanceIndicator.cpp`).
* Enumerador `DistanceZone` y función pura de clasificación.
* Archivo `src/main.cpp` refactorizado, limpio y conciso.
* Soporte de diagnóstico conmutable vía `#define DEBUG`.
* Suite de pruebas unitarias automáticas con el framework **Unity** de PlatformIO en directorio `test/`.
* Guía de pruebas manuales para verificación en protoboard.

### 7.2 Fuera de Alcance para el MVP (Deferred)
* Histéresis digital o filtrado por media móvil para mitigar oscilaciones en las fronteras exactas (10.0 cm o 20.0 cm).
* Calibración de temperatura ambiente para la velocidad del sonido.
* Almacenamiento no volátil (NVS/EEPROM) para configuración de umbrales en tiempo de ejecución.

---

## 8. Métricas de Éxito y Contra-Métricas

### Métricas Primarias
* **SM-1 (Cobertura de Pruebas Unitarias):** 100% de aprobación en las pruebas unitarias automáticas sobre todos los casos de prueba de frontera (0, 5, 10, 10.1, 15, 20, 20.1, 30, 30.1, >30 cm). Valida FR-6 a FR-10, FR-20.
* **SM-2 (Preservación de Comportamiento Físico):** Cero discrepancias funcionales observables entre el código original y el código refactorizado en banco de pruebas. Valida FR-1 a FR-16.
* **SM-3 (Velocidad de Verificación en Host):** La suite de pruebas en el entorno nativo (`test`) debe compilar y ejecutarse en menos de 3 segundos en una máquina estándar.

### Contra-Métricas (Lo que no se debe sobreoptimizar)
* **SM-C1 (Complejidad Ciclomática y Abstracción):** La complejidad ciclomática de cualquier método no debe superar 5. Se prohíbe introducir patrones como Abstract Factory, Visitor o inyección de dependencias abstractas que sacrifiquen la comprensión didáctica del código.

---

## 9. Preguntas Abiertas & Puntos a Confirmar
1. **[RESUELTO]** Baud rate serial fijado a 115200.
2. **[RESUELTO]** Arquitectura basada en 2 clases explícitas: `UltrasonicSensor` y `DistanceIndicator`.
3. **[RESUELTO]** Pruebas automáticas nativas en host mediante PlatformIO + Unity.

---

## 10. Índice de Suposiciones y Validaciones
* **§5 NFR-4 (Nivel Lógico y Protección Eléctrica):** Confirmado. La compatibilidad o protección en Echo (GPIO 27) es transparente para el firmware y preserva exactamente la conexión física actual sin modificaciones de hardware.
* **§4.2 FR-10 (Función Pura de Clasificación de Distancias):** Confirmado. La función pura evalúa exactamente las mismas condiciones numéricas ($d \le 10$, $d \le 20$, $d \le 30$, $> 30$), garantizando cero impacto en el comportamiento lógico del semáforo y permitiendo la ejecución de pruebas unitarias en host.
* **Garantía Inmutable:** Ninguna decisión ni suposición técnica altera ni alterará el funcionamiento actual, los pines asignados ni los rangos de distancia establecidos.
