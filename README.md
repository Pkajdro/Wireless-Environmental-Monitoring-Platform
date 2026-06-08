# Wireless Environmental Monitoring Platform

A remotely operated mobile robotics platform engineered for live atmospheric data acquisition and exploration. The system enables real-time tracking of ambient temperature, humidity, and barometric pressure while under remote operator control.

---

## 🚀 System Architecture Overview

* **Teleoperation:** Remotely controlled via `[Wi-Fi / Bluetooth / RF 2.4GHz]` using a `[custom mobile app / web interface / gamepad]`.
* **Environmental Telemetry:** Real-time sensor data acquisition for temperature, humidity, and barometric pressure (utilizing the `[e.g., BME280 / DHT22]` sensor via `[e.g., I2C / SPI]`).
* **Custom Power & Control:** Integrated custom PCB designed in KiCad for power distribution, motor driving, and sensor decoupling.
* **Modular Chassis:** Custom 3D-printed mechanical enclosures and structural chassis elements optimized for weight and component access.

---

## 🛠️ Tech Stack

| Category | Technology Used |
| :--- | :--- |
| **Microcontroller** | `[e.g., ESP32 / STM32 / Arduino Nano]` |
| **Firmware Language** | `[C++ / Python]` via `[Arduino IDE / PlatformIO]` |
| **ECAD (Electronics)** | KiCad `[e.g., Version 8.0]` |
| **MCAD (Mechanical)** | `[e.g., Fusion360 / SolidWorks]` |

---

## 📸 Media & Visuals

### The Final Robot
> **Drop your best photo or a short moving GIF of the robot right here!** (Just drag and drop the image file from your computer directly into this line of text inside the GitHub editor).

### Electronics & Schematics
> **Drag and drop a screenshot of your KiCad PCB 3D view or your main schematic sheet here.**

### 3D CAD Models
> **Drag and drop a screenshot of your 3D printing schemes/CAD model assembly here.**

---

## 💻 Firmware Architecture & Contributions

The project firmware is written in C++ (Arduino) and utilizes a modular, multi-file structure (`.h` and `.cpp` files) to handle sensor polling, remote teleoperation data, and motor control. 

This firmware was developed collaboratively as part of a university team project. While the overall code repository was structured and refactored into a unified style by my teammate, my primary responsibilities and core codebase contributions included:

* **Sensor Data Acquisition:** Wrote the drivers and polling logic for the environmental sensors (temperature, humidity, and pressure) utilizing the `[e.g., I2C]` bus.
* **Telemetry Data Packaging:** Developed the logic to format the raw sensor data into strings/packets to be sent wirelessly to the operator interface.
* **Motor Control Integration:** (If applicable) Implemented the PWM motor speed logic and direction control algorithms to translate operator inputs into physical movement.

---

## 📂 Repository Structure

* `/firmware` - Source code for the microcontroller.
* `/hardware` - KiCad schematic and PCB layout files.
* `/mechanical` - `.STL` or `.STEP` files for the 3D-printed chassis.
