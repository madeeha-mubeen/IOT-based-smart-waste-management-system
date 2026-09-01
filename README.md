
# ♻️ IoT-Based Smart Waste Management System

<p align="center">

![ESP32](https://img.shields.io/badge/ESP32-DevKit-blue?style=for-the-badge&logo=espressif)
![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D?style=for-the-badge&logo=arduino)
![IoT](https://img.shields.io/badge/IoT-Smart%20Waste%20Management-success?style=for-the-badge)
![Blynk](https://img.shields.io/badge/Blynk-IoT-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

</p>

<p align="center">
An ESP32-based Smart Waste Management System that monitors garbage fill levels, detects approaching users, automatically opens the dustbin lid, displays real-time information on an LCD, and sends notifications through Blynk IoT.
</p>

---

# 🌐 Live Wokwi Simulation

🔗 **Project Link**

https://wokwi.com/projects/449653586435836929

---

# 📖 Project Overview

The **IoT-Based Smart Waste Management System** is an intelligent waste monitoring solution developed using **ESP32** and IoT technologies. The system continuously measures the garbage level using ultrasonic sensors, automatically opens the lid when a user approaches, displays live information on a 20×4 LCD, and sends notifications through the **Blynk IoT Cloud**.

Instead of following fixed garbage collection schedules, this smart system enables **real-time monitoring**, helping municipal authorities optimize collection routes, reduce overflowing bins, and improve urban cleanliness.

---

# ✨ Features

- ♻️ Smart garbage fill-level monitoring
- 📏 Dual HC-SR04 ultrasonic sensors
- 🚶 User/object detection
- 🛠 Automatic lid opening using Servo Motor
- 📺 20×4 I2C LCD Display
- ☁️ Blynk IoT Cloud Integration
- 📍 GPS location logic (Simulation)
- 📲 GSM/SMS notification logic (Simulation)
- 🚛 Smart truck notification system
- ⚠️ Overflow detection
- 🔄 Automatic reset after garbage collection
- 🌍 Fully simulated using Wokwi

---

# 🛠 Hardware Components

| Component | Quantity |
|-----------|----------|
| ESP32 DevKit V1 | 1 |
| HC-SR04 Ultrasonic Sensor | 2 |
| Servo Motor SG90 | 1 |
| 20×4 I2C LCD Display | 1 |
| NEO-6M GPS Module | 1 *(Logic Implemented)* |
| SIM900A GSM Module | 1 *(Logic Implemented)* |
| Jumper Wires | As Required |

---

# 🔌 ESP32 Pin Mapping

| Component | GPIO |
|-----------|------|
| Object Sensor Trigger | GPIO 13 |
| Object Sensor Echo | GPIO 14 |
| Fill Level Trigger | GPIO 18 |
| Fill Level Echo | GPIO 19 |
| Servo Motor | GPIO 27 |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |

---

# 💻 Software Requirements

- Arduino IDE
- ESP32 Board Package
- Wokwi Simulator
- Blynk IoT
- Wire Library
- LiquidCrystal_I2C Library
- WiFi Library
- WiFiClient Library

---

# 📁 Repository Structure

```text
iot-based-smart-waste-management-system/
│
├── README.md
├── LICENSE
├── .gitignore
│
├── src/
│   ├── smart_waste_management.ino
│   ├── diagram.json
│   └── libraries.txt
│
├── simulation/
│   └── wokwi_link.md
│
├── docs/
│   ├── Mini_Project_Synopsis.pdf
│   ├── Final_Project_Report.pdf
│   ├── Phase1_Presentation.pdf
│   └── Phase2_Presentation.pdf
│
└── images/
    ├── hardware_setup.jpg
    ├── startup.png
    ├── fill17.png
    ├── fill51.png
    ├── alert75.png
    ├── alert95.png
    └── collection.png
```

---

# ⚙️ System Workflow

```text
User Approaches Dustbin
          │
          ▼
Object Detection Sensor
          │
          ▼
Servo Motor Opens Lid
          │
          ▼
Waste Deposited
          │
          ▼
Fill-Level Sensor Measures Garbage
          │
          ▼
ESP32 Processes Data
          │
          ▼
LCD Displays Fill Percentage
          │
          ▼
Blynk Dashboard Updated
          │
          ▼
75% Alert → Truck Notification
95% Alert → Emergency Notification
100% → Overflow Warning
          │
          ▼
Garbage Collection
          │
          ▼
Bin Reset
```

---

# 🚨 Alert Levels

| Fill Level | Status | Action |
|------------|--------|--------|
| 🟢 0–49% | Normal | Monitoring |
| 🟡 50–74% | Moderate | Continue Monitoring |
| 🟠 75–94% | Almost Full | Notify Collection Truck |
| 🔴 95–99% | Critical | Notify All Trucks |
| ⚫ 100% | Overflow | Immediate Collection |

---

# 📸 Project Gallery

## 🖥️ Wokwi Circuit

<p align="center">
<img src="https://github.com/user-attachments/assets/ca94e86b-1b99-4fe9-8577-b91f106d9356" width="850" alt="Wokwi Circuit"/>
</p>

<p align="center">
<b>Figure 1:</b> Complete ESP32 Smart Waste Management Simulation.
</p>

---

## 🚀 System Startup

<p align="center">
<img src="https://github.com/user-attachments/assets/e07d3e2c-3bf0-4d35-b2e3-e3b76717e98b" width="650" alt="System Startup"/>
</p>

---

## 📊 Fill Level Monitoring

<table align="center">
<tr>

<td align="center">
<b>17% Fill Level</b><br><br>
<img src="https://github.com/user-attachments/assets/8c25a85d-f8af-4b08-b7fc-d17c9f2b0a6c" width="350"/>
</td>

<td align="center">
<b>51% Fill Level</b><br><br>
<img src="https://github.com/user-attachments/assets/caeddb98-282d-4835-ba32-1ab4b6a560f5" width="350"/>
</td>

</tr>
</table>

---

## 🚨 Alert Notifications

<table align="center">
<tr>

<td align="center">
<b>75% Alert</b><br><br>
<img src="https://github.com/user-attachments/assets/1383ba90-7e2a-41ef-9e51-06eda13efccd" width="350"/>
</td>

<td align="center">
<b>95% Alert</b><br><br>
<img src="https://github.com/user-attachments/assets/e5118859-ba5d-4b3b-8224-de004f201b6b" width="350"/>
</td>

</tr>
</table>

---

## ♻️ Garbage Collection

<p align="center">
<img src="https://github.com/user-attachments/assets/8e90faa8-d94d-44fc-9a20-7020fd7f1446" width="650" alt="Garbage Collection"/>
</p>

---

# 📄 Documentation

The **docs** folder contains:

- 📘 Mini Project Synopsis
- 📄 Final Project Report
- 📊 Phase 1 Presentation
- 📊 Phase 2 Presentation

---

# ▶️ How to Run

## Wokwi Simulation

1. Open the Wokwi project.
2. Click **Start Simulation**.
3. Observe the LCD display.
4. Change ultrasonic sensor values.
5. Monitor the Serial Monitor.
6. Observe Blynk dashboard updates.

---

## Arduino IDE

1. Install Arduino IDE.
2. Install the ESP32 Board Package.
3. Install the required libraries.
4. Open `smart_waste_management.ino`.
5. Replace the Blynk credentials with your own.
6. Upload the code to the ESP32.

---

# ☁️ Libraries Used

- LiquidCrystal_I2C
- Wire
- WiFi
- WiFiClient
- BlynkSimpleEsp32

---

# 🚀 Future Scope

- 📱 Android Mobile Application
- ☁️ Cloud Database Integration
- 🤖 AI-Based Waste Prediction
- 🚛 Smart Route Optimization
- 📍 Real-Time GPS Tracking
- 📲 Real GSM SMS Alerts
- 🌞 Solar-Powered Smart Dustbin
- 🏙 Smart City Dashboard

---

# 👥 Team Members

- **Isra Zainab**
- **Madeeha Mohammed Mubeen**
- **Saniya Naz**
- **Shamma Shirin M. A.**

---

# 👨‍🏫 Project Guide

**Akshata Dange**

---

# 🏫 Institution

**Yenepoya Institute of Technology**

Department of Computer Science and Engineering

**Specialization:** IoT, Cyber Security with Blockchain Technology

**Academic Year:** 2025–2026

---

# 📜 License

This project is licensed under the **MIT License**.

See the **LICENSE** file for more information.

---

# 🙏 Acknowledgements

- Arduino
- Espressif Systems
- Blynk IoT
- Wokwi Simulator
- Open Source Community

---

<p align="center">

⭐ If you found this project useful, consider giving it a **Star ⭐** on GitHub!

Made with ❤️ by **Madeeha Mohammed Mubeen and Team**

</p>
````


</p>
