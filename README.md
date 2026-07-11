# AntiVE-BehaviorWatch

![Language](https://img.shields.io/badge/language-C-00599C?logo=c&logoColor=white)
![Platform](https://img.shields.io/badge/platform-Windows-0078D6?logo=windows&logoColor=white)
![AI](https://img.shields.io/badge/AI-GRU%20Neural%20Network-purple)
![Inference](https://img.shields.io/badge/inference-Embedded%20AI-success)
![Detection](https://img.shields.io/badge/detection-Behavioral%20Verification-orange)
![Status](https://img.shields.io/badge/status-Active%20Research-red)

<img width="1408" height="768" alt="AntiVE_BehaviorWatch" src="https://github.com/user-attachments/assets/09bc71d0-f1b3-4231-b9de-75c387484072" />


> **Embedded AI-powered human behavior verification for cybersecurity research.**

---

# What is AntiVE-BehaviorWatch?

**AntiVE-BehaviorWatch** is a Windows-based cybersecurity research project that explores a new approach to execution control using **embedded artificial intelligence**.

Instead of relying on traditional anti-analysis techniques such as virtual machine detection, sandbox detection, debugger checks, or hardware fingerprinting, the project uses an embedded **GRU (Gated Recurrent Unit) neural network** to determine whether a **real human** is interacting with the system.

The model analyzes real-time mouse behavior—including cursor movement, velocity, acceleration, jerk, angular velocity, idle patterns, and motion characteristics—to make an intelligent runtime decision before allowing the protected execution path to continue.

---

<img width="1919" height="1035" alt="AntiVE" src="https://github.com/user-attachments/assets/4e5fd10f-2241-4c3e-9847-f6f84ad23298" />

---

# Architecture

  ```
  Mouse Movement
         │
         ▼
  Feature Extraction
         │
         ▼
  Embedded GRU Neural Network
         │
         ▼
  Behavior Classification
         │
   ┌─────┴────────┐
   │              │
   ▼              ▼
  Human      Idle / Artificial
  Verified      Behavior
   │              │
   ▼              ▼
  Continue     Abort
  Execution

  ```

---

# Behavioral Features

The embedded model analyzes multiple behavioral features:

- Cursor Distance
- Cursor Velocity
- Acceleration
- Jerk
- Mouse Angle
- X-axis Movement
- Y-axis Movement
- Idle State
- Idle Streak Length

These features are collected continuously over multiple observation phases before inference.

---

# Features

- Embedded GRU neural network
- Offline AI inference
- No external AI runtime required
- Real-time behavioral telemetry
- Human interaction verification
- Multi-phase analysis
- Majority voting decision engine
- Lightweight C implementation
- Windows-native application
- Embedded model weights
- Runtime behavior classification

---

# Disclaimer

This project is intended **strictly for cybersecurity research, machine learning experimentation, education, and authorized security testing**.

It demonstrates how embedded AI can be used for behavioral verification and runtime decision-making. It is not intended for unauthorized or malicious use.

---

# Author

**Nirvana (0xNirSec)**

*"Trust behavior, not the environment."*


