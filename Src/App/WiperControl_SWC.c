#include "WiperControl_SWC.h"
#include "Rte_Wiper.h"
#include "Rte_Types.h"
#include "cmsis_os2.h" 
#include "uart.h"
#include "can_if.h"
#include "wdg_manager.h"
extern osMessageQueueId_t wiperQueue;

static WiperMode_t current_wiper_mode;

void WiperControl_Init(void) {
    current_wiper_mode = WIPER_OFF;
    Rte_Write_WiperMode(current_wiper_mode);
}

__NO_RETURN void WiperControl_Task(void *argument) {
    (void)argument;
    UART0_SendString("[Task Wiper] Ready & Waiting...\r\n");

    while(1) {
        WdgM_CheckpointReached(WDG_WIPER_TASK_ID);
        SystemEvent_t received_msg;
        if (osMessageQueueGet(wiperQueue, &received_msg, NULL, 500) == osOK) {
            if (received_msg == SYS_EVT_WIPER_BTN_PRESSED) {
                current_wiper_mode = (current_wiper_mode == WIPER_OFF) ? WIPER_INT : WIPER_OFF;
                
                Rte_Write_WiperMode(current_wiper_mode);

                if(current_wiper_mode == WIPER_INT) {
                    CanIf_Transmit(CAN_SIGNAL_WIPER_ON); 
                    UART0_SendString("[Task Wiper] Mode INT (CAN Sent)\r\n");
                } else {
                    CanIf_Transmit(CAN_SIGNAL_WIPER_OFF); 
                    UART0_SendString("[Task Wiper] Mode OFF (CAN Sent)\r\n");
                }
            }
        }
    }
}

// #include "WiperControl_SWC.h"
// #include "Rte_Wiper.h"
// #include "cmsis_os2.h" 
// #include "uart.h"

// static WiperMode_t current_wiper_mode;
// static WiperSwitchState_t last_sw_state;

// void WiperControl_Init(void) {
//     current_wiper_mode = WIPER_OFF;
//     last_sw_state = WIPER_SW_OFF; 
//     Rte_Write_WiperMode(current_wiper_mode);
// }

// __NO_RETURN void WiperControl_Task(void *argument) {
//     (void)argument;
//     osDelay(10);
//     UART0_SendString("[Task Wiper] Running...\r\n");

//     while(1) {
//         WiperSwitchState_t current_sw_state = Rte_Read_WiperSwitch();

//         if (current_sw_state == WIPER_SW_ON && last_sw_state == WIPER_SW_OFF) {
            
//             switch (current_wiper_mode) {
//                 case WIPER_OFF: 
//                     current_wiper_mode = WIPER_INT; 
//                     UART0_SendString("[Task Wiper] Button Pressed -> Mode INT\r\n");
//                     break;
//                 case WIPER_INT: 
//                     current_wiper_mode = WIPER_OFF; 
//                     UART0_SendString("[Task Wiper] Button Pressed -> Mode OFF\r\n");
//                     break;
//                 default: 
//                     current_wiper_mode = WIPER_OFF; 
//                     break;
//             }
//             Rte_Write_WiperMode(current_wiper_mode);
//         }
        
//         last_sw_state = current_sw_state;

//         osDelay(50); // Sleep 50ms
//     }
// }