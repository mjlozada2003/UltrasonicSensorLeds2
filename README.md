# Práctica 1 — Integración de Sensores y Actuadores en un Objeto Inteligente

[![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32%20%26%20Native-orange.svg)](https://platformio.org/)
[![Framework](https://img.shields.io/badge/Framework-Arduino%20C%2B%2B-blue.svg)](https://www.arduino.cc/)
[![Unit Tests](https://img.shields.io/badge/Unity%20Tests-100%25%20PASS-brightgreen.svg)]()
[![Build](https://img.shields.io/badge/Firmware%20Build-SUCCESS-success.svg)]()

Repositorio oficial para la entrega de la **Práctica 1: Integración de Sensores y Actuadores en un Objeto Inteligente** en la asignatura de **Internet de las Cosas** de la **Universidad Católica Boliviana "San Pablo" (UCB)**.

---

## 📑 Informe Técnico Principal

El informe técnico completo requerido por la rúbrica (§4.2) con sus **8 secciones obligatorias** redactadas de manera clara y sencilla se encuentra disponible en:

👉 **[INFORME TÉCNICO OFICIAL (Markdown)](INFORME_TECNICO.md)**

---

## 👥 Integrantes del Grupo

* **María Jesús Lozada Peralta**
* **Samuel Jarro Rodriguez**
* **Katherine Montaño Mejia**

* **Microcontrolador:** DOIT ESP32 DevKit v1 (240 MHz, 4MB Flash)
* **Fecha de Entrega:** 10 de Septiembre de 2026

---

## 🎯 ¿Qué hace este Objeto Inteligente?

El sistema **UltrasonicLedsSensor** mide la distancia de objetos en tiempo real mediante un sensor ultrasónico **HC-SR04** y avisa visualmente mediante un semáforo de tres luces (**LED Rojo, Amarillo y Verde**). Cumple con una regla estricta de **exclusión mutua** (solo una luz puede estar encendida a la vez) y envía las lecturas continuamente por el cable USB a la computadora.

### Comportamiento del Semáforo según la Distancia

| Distancia Medida ($d$) | Zona | Estado de los LEDs | Luz Visible | Mensaje en Computadora |
| :---: | :---: | :---: | :---: | :---: |
| De $0.0$ a $10.0\text{ cm}$ | `Near` (Cerca) | Rojo = HIGH, Otros = LOW | 🔴 Solo luz Roja (Peligro / Proximidad crítica) | `"<d> cm"` |
| De $10.1$ a $20.0\text{ cm}$ | `Medium` (Medio) | Amarillo = HIGH, Otros = LOW | 🟡 Solo luz Amarilla (Advertencia) | `"<d> cm"` |
| De $20.1$ a $30.0\text{ cm}$ | `Far` (Lejos) | Verde = HIGH, Otros = LOW | 🟢 Solo luz Verde (Zona segura) | `"<d> cm"` |
| Mayor a $30.0\text{ cm}$ | `OutOfRange` | Todos = LOW | ⚫ Todas las luces apagadas (Fuera de rango) | `"<d> cm"` + `"FUERA DE ALCANCE"` |
| Sin eco / Error ($-1.0\text{ cm}$) | `OutOfRange` | Todos = LOW | ⚫ Todas las luces apagadas (Sin eco) | `"FUERA DE ALCANCE"` |

---

## 🔌 Conexiones de Pines en el ESP32

| Componente | Pin del Componente | Pin en la Placa ESP32 | Dirección | ¿Qué señal transporta? |
| :--- | :---: | :---: | :---: | :--- |
| **Sensor HC-SR04** | Trigger | **GPIO 14** | Salida | Pulso de disparo de $10\,\mu\text{s}$ para emitir sonido |
| **Sensor HC-SR04** | Echo | **GPIO 27** | Entrada | Tiempo de rebote del eco acústico |
| **LED Rojo** | Ánodo (+) | **GPIO 33** | Salida | Señal de alerta para distancia $\le 10\text{ cm}$ |
| **LED Amarillo** | Ánodo (+) | **GPIO 25** | Salida | Señal de advertencia para distancia de $10\text{ a }20\text{ cm}$ |
| **LED Verde** | Ánodo (+) | **GPIO 26** | Salida | Señal de distancia segura de $20\text{ a }30\text{ cm}$ |
| **Alimentación** | VCC / GND | VIN (5V) / GND | Alimentación | $5\text{ V}$ para el sensor / Tierra común del circuito |

> **Nota de seguridad:** Cada LED tiene una resistencia limitadora de $220\,\Omega$ conectada en serie hacia GND para no quemar el LED ni dañar la placa.

---

## 📁 Estructura del Repositorio

```text
UltrasonicLedsSensor/
├── README.md                           # Portada y presentación del proyecto
├── INFORME_TECNICO.md                  # Informe técnico con las 8 secciones de la rúbrica
├── platformio.ini                      # Configuración para compilar en ESP32 y en PC
├── include/
│   ├── DistanceZone.h                  # Definición de las 4 zonas y la función de cálculo
│   ├── UltrasonicSensor.h              # Declaración de la clase del sensor
│   └── DistanceIndicator.h             # Declaración de la clase del semáforo LED
├── src/
│   ├── main.cpp                        # Programa principal (setup, loop y lecturas)
│   ├── DistanceZone.cpp                # Lógica pura que compara si es < 10, 20 o 30 cm
│   ├── UltrasonicSensor.cpp            # Disparo del sensor y cálculo de distancia en cm
│   └── DistanceIndicator.cpp           # Control de los LEDs con exclusión mutua
├── test/
│   └── test_distance/
│       └── testMain.cpp                # 5 pruebas automáticas con Unity en PC (100% aprobadas)
└── docs/
    ├── anexos/                         # Fotos del circuito, logs y evidencias
    │   ├── README.md                   # Lista de fotos y capturas requeridas
    │   ├── logs-pruebas-unitarias.txt   # Resultado real de las pruebas automáticas
    │   └── logs-compilacion-esp32.txt  # Resultado real de compilación para la placa
    └── documentacion-tecnica-sistema.md# Memoria técnica detallada complementaria
```

---

## 🚀 Cómo Ejecutar y Probar el Proyecto

Para compilar y probar con **PlatformIO**, abre una terminal en la carpeta del proyecto:

### 1. Correr las Pruebas Automáticas en la Computadora (sin placa conectada)
```bash
pio test -e native
```
*Resultado:* **5 pruebas exitosas en menos de 4 segundos (100% SUCCESS)**.

### 2. Compilar el Programa para la Placa ESP32
```bash
pio run -e esp32doit-devkit-v1
```
*Resultado:* **SUCCESS (0 errores, memoria Flash ocupada al 20.6%, RAM al 6.6%)**.

### 3. Cargar el Programa al ESP32 (con la placa conectada por USB)
```bash
pio run -e esp32doit-devkit-v1 -t upload
```

### 4. Abrir la Pantalla para ver las Lecturas en Vivo
```bash
pio device monitor -b 115200
```

---

## 📊 Cumplimiento de los Requerimientos de la Rúbrica

| Atributo Evaluado | Meta de la Guía | Lo que demostró el proyecto | Estado |
| :--- | :---: | :---: | :---: |
| **Estabilidad** | $\ge 10\text{ min}$ sin reiniciarse | **15 minutos continuos** (más de 8,500 lecturas, 0 fallos) | **Aprobado** |
| **Exactitud** | Error menor a $\pm 3.0\text{ cm}$ | **Error máximo de solo $\pm 0.28\text{ cm}$** (menos de 3 mm) | **Aprobado** |
| **Tiempo de respuesta** | Reaccionar en $\le 1.0\text{ s}$ | **$0.13\text{ segundos}$** (reacción inmediata) | **Aprobado** |
| **Lecturas por segundo** | Al menos $2\text{ lecturas/s}$ | **$\approx 9.5\text{ lecturas/s}$** | **Aprobado** |
| **Pruebas de software** | 100% comprobable | **5 de 5 pruebas unitarias aprobadas** | **Aprobado** |
