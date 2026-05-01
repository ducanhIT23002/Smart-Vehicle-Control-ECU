#include "DoorControl_SWC.h"
#include "Rte_Door.h" 
#include "Rte_Types.h"
#include "cmsis_os2.h"
#include "uart.h"
#include "can_if.h"
#include "wdg_manager.h"
extern osMessageQueueId_t doorQueue;

void DoorControl_Init(void) { }

__NO_RETURN void DoorControl_Task(void *argument) {
    (void)argument; 
    UART0_SendString("[Task Door] Ready & Waiting...\r\n");

    while(1) {
        WdgM_CheckpointReached(WDG_DOOR_TASK_ID);
        SystemEvent_t received_msg;
        if (osMessageQueueGet(doorQueue, &received_msg, NULL, 500) == osOK) {
            if (received_msg == SYS_EVT_DOOR_OPENED) {
                Rte_Write_P_DoorLed_Status(LED_ON);
                CanIf_Transmit(CAN_SIGNAL_DOOR_OPEN);
                UART0_SendString("[Task Door] DOOR OPEN -> LED ON\r\n");
            } 
            else if (received_msg == SYS_EVT_DOOR_CLOSED) {
                Rte_Write_P_DoorLed_Status(LED_OFF);
                CanIf_Transmit(CAN_SIGNAL_DOOR_CLOSED);
                UART0_SendString("[Task Door] DOOR CLOSED -> LED OFF\r\n");
            }
        }
    }
}


// #include "DoorControl_SWC.h"
// #include "Rte_Door.h" 
// #include "cmsis_os2.h"
// #include "uart.h"

// void DoorControl_Init(void) {
//     // Initialization if needed
// }

// __NO_RETURN void DoorControl_Task(void *argument) {
//     (void)argument; 
//     static uint8_t last_door_state = 0; // Assume 0 is closed
    
//     UART0_SendString("[Task Door] Running...\r\n");

//     while(1) {
//         // 1. Read hardware state
//         uint8_t current_door_state = Rte_Read_DoorStatus(); // Assume this returns 1 (Open) or 0 (Closed)

//         // 2. Process only if state changed (Edge detection)
//         if (current_door_state != last_door_state) {
            
//             if (current_door_state == 1) { 
//                 Rte_Write_P_DoorLed_Status(LED_ON);
//                 UART0_SendString("[Task Door] DOOR OPEN -> LED ON\r\n");
//             } else {
//                 Rte_Write_P_DoorLed_Status(LED_OFF);
//                 UART0_SendString("[Task Door] DOOR CLOSED -> LED OFF\r\n");
//             }
//             last_door_state = current_door_state; // Save history
//         }

//         // 3. Go to sleep for 50ms
//         osDelay(50); 
//     }
// }