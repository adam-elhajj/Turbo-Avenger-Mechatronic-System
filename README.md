# Turbo Avenger: Autonomous Mechatronic Payload Delivery System
[![Platform: Arduino & ESP32](https://shields.io)](https://github.com/adam-elhajj/Turbo-Avenger-Mechatronic-System)
[![CAD: AutoCAD](https://shields.io)](https://github.com/adam-elhajj/Turbo-Avenger-Mechatronic-System)
[![Status: Functional Prototype](https://shields.io)](https://github.com/adam-elhajj/Turbo-Avenger-Mechatronic-System)

A high-precision, multi-actuator mechatronic system engineered for autonomous, search-and-rescue inspired payload delivery. Developed as a milestone cornerstone engineering project at the **University of Windsor**, this system automates the storage, sequencing, and deployment of three separate payloads to a static target under real-world constraints.

---

### 📺 System Verification & Demo
Click the player below to watch the **Turbo Avenger** execute its fully autonomous 3-stage delivery sequence:

[![Turbo Avenger Verification Demo](https://youtube.com)](https://www.youtube.com/watch?v=t6WQirkNGkE)

---

## 🎯 Engineering & Performance Benchmarks
* **Targeting Precision:** Achieved an empirical accuracy of **±5 cm at a 3-meter range** (1.6% variance).
* **Autonomous Sequence:** 100% deterministic, human-out-of-the-loop sorting and deployment sequence.
* **Component Reliability:** Eliminated jamming bottlenecks using a custom dual-servo escapement architecture.
* **Fiscal Optimization:** Fully prototyped, value-engineered, and deployed within a strict **\$328 budget limit**.

## 🛠️ System Architecture & Implementation

### ⚙️ Mechanical & Actuation Architecture
* **Energy Storage & Release:** Features a synchronized servo-driven energy storage system paired with a rotating latch mechanism for instantaneous power release.
* **Automated Autoloading:** Designed a dual-servo mechanical escapement subsystem to prevent multi-payload feeding failures and isolate system jams.
* **Design Validation:** Validated kinematic constraints and assembly interfaces via iterative **3D CAD modeling** and stress verification.

### 🔌 Embedded Control Systems & Firmware
* **Dual-MCU Architecture:** Implemented an **Arduino Uno R3** alongside an **ESP32** to handle strict real-time control, parallel processing constraints, and high-frequency state machine management.
* **State Machine & Timing Logic:** Programmed asynchronous timing models for precise actuator triggering, transition validation, and deterministic safety overrides.

---

## 📂 Repository Tree Structure
```text
├── CAD-Models/                # Production Engineering Schematics
│   ├── Final Catapult assembly Team 221.dwg
│   ├── Top plate.dwg
│   └── Part_1_through_6.dwg   # Individual component layouts
├── Firmware/                  # Microcontroller Source Code
│   ├── Arduino_Control/       # Actuator management & timing scripts
│   └── ESP32_Logic/           # State machine & sensor management
├── Documentation/             # Engineering Specifications
│   ├── RobotCar_Part_List.pdf # Complete Bill of Materials (BOM)
│   ├── Final Proposal Report  # Technical design documentation
│   └── RFP_Amendments.pdf     # Engineering constraint compliances
└── Media/                     # Visual Assets
    └── Turbo Avenger - Team#221 Poster.jpg
```

---

## 🛠️ Tools & Technologies Used
* **Languages:** C++, C (Embedded Arduino)
* **Hardware:** Arduino Uno R3, ESP32, High-Torque Servos, Electro-Mechanical Actuators
* **Software/CAD:** Autodesk AutoCAD, Git Version Control, Serial Data Analysis
