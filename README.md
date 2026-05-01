# 🚘 Smart Automotive Body Control Module (BCM)

## 📌 Project Overview
This project simulates an automotive **Body Control Module (BCM)** using the NXP LPC1768 microcontroller. It is designed based on the **AUTOSAR Layered Architecture** and utilizes a strictly **Event-Driven** model powered by CMSIS-RTOS2 Message Queues. 

To closely reflect real-world automotive software standards, all physical state changes are abstracted and broadcasted over a simulated **CAN Bus network** to notify other ECUs in the vehicle (e.g., Instrument Cluster).

## 🛠️ Technologies & Hardware
*   **Microcontroller:** NXP LPC1768 (ARM Cortex-M3)
*   **RTOS:** CMSIS-RTOS2 (Keil RTX5)
*   **Language:** Embedded C
*   **Architecture:** AUTOSAR-inspired (App SWC, RTE, ECUAL, MCAL, Services)
*   **Peripherals Used:** CAN, UART, ADC, DMA, PWM, GPIO

## 🧩 Software Architecture
The codebase is strictly modularized into distinct layers:
1.  **APP (Software Components - SWCs):** Contains core logic for Door, Wiper, and Light control. Tasks sleep efficiently (`osWaitForever`) until an event occurs.
2.  **RTE (Runtime Environment):** Acts as the communication bridge. SWCs interact with hardware solely through RTE macros.
3.  **ECUAL & MCAL:** Abstracts hardware components and handles direct microcontroller register manipulation.
4.  **Services (CAN Interface - CanIf):** Abstracts the CAN stack. App layer sends semantic signals (e.g., `CAN_SIGNAL_DOOR_OPEN`), and `CanIf` translates them into specific CAN IDs and Data Payloads.

## 📡 CAN Network Matrix & Workflows
Every state change triggers a CAN broadcast to synchronize the vehicle's network.

| Feature | Trigger Event | Physical Action | CAN ID | Payload (DataA) | Meaning |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Smart Door** | Physical switch pressed | Toggle Warning LED | `0x100` | `0x0001` / `0x0000` | Door Open / Closed |
| **Auto Wiper** | Wiper Joystick interacted | GPIO Motor Control | `0x200` | `0x0001` / `0x0000` | Wiper INT / OFF |
| **Auto Headlight** | ADC light sensor drops | Activate Headlight | `0x300` | `0x0001` / `0x0000` | Headlight ON / OFF |
| **Interior Dimmer**| Dimmer Joystick interacted| PWM Smooth Fade In/Out | `0x400` | `0x0001` / `0x0000` | Dimmer ON / OFF |

## ⚙️ RTOS Implementation Details
*   **Producer-Consumer Model:** Replaced all `osDelay()` polling mechanisms in control tasks.
*   **Input Monitor Task (Producer):** A dedicated background task that polls sensors, performs edge detection, and pushes standard `SystemEvent_t` messages into specific Message Queues.
*   **Control Tasks (Consumers):** Isolated tasks that pend on dedicated Queues (`doorQueue`, `wiperQueue`, `lightQueue`). They consume **0% CPU** while waiting, drastically reducing power consumption.
*   **Data Logging:** UART is strictly used for real-time system state and CAN transmission debugging.