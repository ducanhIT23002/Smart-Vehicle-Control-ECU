# 🚘 Smart Automotive Body Control Module (BCM)

## 📌 Project Overview
This project simulates an automotive **Body Control Module (BCM)** using the NXP LPC1768 microcontroller. It is designed based on the **AUTOSAR Layered Architecture** and utilizes a strictly **Event-Driven** model powered by CMSIS-RTOS2 Message Queues. 

To closely reflect real-world automotive software standards, the system includes an **Alive Supervision Watchdog** mechanism (ISO 26262 Functional Safety concept) and broadcasts state changes over a simulated **CAN Bus network** to notify other ECUs.

## 🛠️ Technologies & Hardware
*   **Microcontroller:** NXP LPC1768 (ARM Cortex-M3)
*   **RTOS:** CMSIS-RTOS2 (Keil RTX5)
*   **Language:** Embedded C
*   **Architecture:** AUTOSAR-inspired (App SWC, RTE, ECUAL, MCAL, Services)
*   **Peripherals Used:** CAN, WDT, UART, ADC, DMA, PWM, GPIO

## 🧩 Software Architecture
The codebase is strictly modularized into distinct layers:
1.  **APP (Software Components - SWCs):** Contains core logic for Door, Wiper, and Light control. 
2.  **RTE (Runtime Environment):** Acts as the communication bridge. SWCs interact with hardware solely through RTE macros.
3.  **ECUAL & MCAL:** Abstracts hardware components and handles direct microcontroller register manipulation.
4.  **Services:** 
    *   **CanIf (CAN Interface):** Abstracts the CAN stack, translating semantic signals into specific CAN IDs and Data Payloads.
    *   **WdgM (Watchdog Manager):** Manages system health and prevents software deadlocks.

## 📡 CAN Network Matrix
Every state change triggers a CAN broadcast to synchronize the vehicle's network.

| Feature | Trigger Event | Physical Action | CAN ID | Payload (DataA) | Meaning |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Smart Door** | Physical switch pressed | Toggle Warning LED | `0x100` | `0x0001` / `0x0000` | Door Open / Closed |
| **Auto Wiper** | Wiper Joystick interacted | GPIO Motor Control | `0x200` | `0x0001` / `0x0000` | Wiper INT / OFF |
| **Auto Headlight** | ADC light sensor drops | Activate Headlight | `0x300` | `0x0001` / `0x0000` | Headlight ON / OFF |
| **Interior Dimmer**| Dimmer Joystick interacted| PWM Smooth Fade In/Out | `0x400` | `0x0001` / `0x0000` | Dimmer ON / OFF |

## ⚙️ RTOS & Safety Implementation Details
*   **Event-Driven Architecture:** Replaced all `osDelay()` polling mechanisms. Control tasks pend on dedicated Queues (`osWaitForever` / timeout) and consume **0% CPU** while waiting.
*   **Input Monitor Task (Producer):** A dedicated background task that polls sensors, performs edge detection, and pushes standard `SystemEvent_t` messages into specific Message Queues.
*   **System Safety (Alive Supervision):** Implemented an AUTOSAR-like Watchdog Manager (`WdgM`). It avoids "blind feeding" by requiring all control SWCs to periodically report their health status (`WdgM_CheckpointReached`). If any task is trapped in a deadlock, the Hardware WDT forces a system reset to ensure fail-safe operation.