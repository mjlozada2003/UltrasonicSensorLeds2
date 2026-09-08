# Carpeta de Anexos y Evidencias de Pruebas

Esta carpeta contiene los archivos de registro, evidencias y recursos complementarios requeridos por la **Sección 8 (Anexos)** de la rúbrica de la práctica.

---

## 📋 Lista de Evidencias Requeridas para la Entrega Final

Antes de enviar el enlace definitivo del repositorio por el LMS-UCB, los integrantes del grupo deben asegurar que se encuentren cargados en esta carpeta:

### 1. Evidencias Fotográficas del Prototipo Físico
* [ ] **`foto-montaje-general.jpg`:** Fotografía en ángulo cenital o perspectiva donde se aprecie claramente el microcontrolador ESP32 en la protoboard, el sensor ultrasónico HC-SR04, los 3 LEDs con sus resistencias de 220 Ω, el cableado ordenado y la regla métrica fijada al banco de pruebas.
* [ ] **`foto-rango-rojo.jpg`:** Fotografía con un obstáculo a menos de 10 cm (ej. a 5 cm) demostrando que únicamente el LED Rojo se encuentra encendido.
* [ ] **`foto-rango-amarillo.jpg`:** Fotografía con el obstáculo entre 10 y 20 cm (ej. a 15 cm) demostrando que únicamente el LED Amarillo se encuentra encendido.
* [ ] **`foto-rango-verde.jpg`:** Fotografía con el obstáculo entre 20 y 30 cm (ej. a 25 cm) demostrando que únicamente el LED Verde se encuentra encendido.
* [ ] **`foto-fuera-de-rango.jpg`:** Fotografía con el obstáculo a más de 30 cm (o retirado) demostrando que todos los LEDs permanecen apagados.

### 2. Evidencias de Telemetría y Monitor Serie
* [ ] **`captura-monitor-serie.png`:** Captura de pantalla de la terminal serie abierta a 115200 baudios, mostrando la secuencia de transiciones de distancias impresas y el mensaje `"FUERA DE ALCANCE"`.

---

## 📑 Registros Oficiales de Ejecución Automatizada

* **[`logs-pruebas-unitarias.txt`](logs-pruebas-unitarias.txt):** Salida directa generada por PlatformIO al ejecutar `pio test -e native` con el framework Unity (100% de aserciones aprobadas).
* **[`logs-compilacion-esp32.txt`](logs-compilacion-esp32.txt):** Salida directa de compilación de firmware para la placa `esp32doit-devkit-v1` (20.6% Flash, 6.6% RAM, 0 errores).
