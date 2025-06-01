# DeCycler 🚮🤖

DeCycler is a smart servo-powered waste sorting mechanism built using an **ESP32-C3 SuperMini**, capable of moving on an XY axis and opening a lid for dumping waste. It communicates via **serial commands** over RS232 from a host system like an **NVIDIA Jetson Nano**.

---

## 🛠 Hardware Overview

### 🎯 Components:
- **ESP32-C3 SuperMini**
- **3x Servo Motors**
  - M1: Servo X Axis (horizontal movement)
  - M2: Servo Y Axis (tilt/dumping)
  - M3: Servo Lid (door/lid opener)
- **Camera Module** (optional for feedback/vision)
- **NVIDIA Jetson Nano** (or any PC with RS232/USB UART)
- **5V Power Supply**

### 📦 Pin Mapping (ESP32-C3)

| GPIO | Function           | Description       |
|------|--------------------|-------------------|
| GPIO6 | `X_PIN`           | Horizontal axis   |
| GPIO7 | `Y_PIN`           | Vertical/tilt     |
| GPIO8 | `LID_PIN`         | Lid open/close    |
| TX/RX| Serial Comm        | RS232 to Jetson   |

### 🖥️ Communication
- RS232 UART from Jetson Nano to ESP32-C3.
- Commands sent via serial (USB/RS232 adapter or native port).

---

## 💻 Command Protocol

The ESP32 receives **single-character serial commands** to perform actions:

| Command | Action                  |
|---------|-------------------------|
| `'1'`   | Dump in Sector 1        |
| `'2'`   | Dump in Sector 2        |
| `'3'`   | Dump in Sector 3        |
| `'4'`   | Open lid manually       |
| `'5'`   | Close lid manually      |

Example (from Jetson Nano):
```python
import serial

ser = serial.Serial('/dev/ttyUSB0', 115200)
ser.write(b'1')  # Dumps in Sector 1
