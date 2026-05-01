#include "LightControl_SWC.h"
#include "Rte_Light.h"
#include "Rte_Types.h"  
#include "cmsis_os2.h"
#include "uart.h"
#include "can_if.h"
#include "wdg_manager.h"
extern osMessageQueueId_t lightQueue;

static uint8_t is_interior_light_on = 0;

void LightControl_Init(void) {
    is_interior_light_on = 0; 
    Rte_Write_Headlight(LED_OFF); 
}

__NO_RETURN void LightControl_Task(void *argument) {
    (void)argument;
    UART0_SendString("[Task Light] Ready & Waiting for Events...\r\n");

    while(1) {
        SystemEvent_t received_msg;
        osStatus_t status = osMessageQueueGet(lightQueue, &received_msg, NULL, 500);

        if (status == osOK) {
            switch (received_msg) {
                case SYS_EVT_ENV_DARK:
                    Rte_Write_Headlight(LED_ON);
                    CanIf_Transmit(CAN_SIGNAL_HEADLIGHT_ON);
                    UART0_SendString("[Task Light] Dark -> Headlight ON\r\n");
                    break;

                case SYS_EVT_ENV_BRIGHT:
                    Rte_Write_Headlight(LED_OFF);
                    CanIf_Transmit(CAN_SIGNAL_HEADLIGHT_OFF);
                    UART0_SendString("[Task Light] Bright -> Headlight OFF\r\n");
                    break;

                case SYS_EVT_DIMMER_BTN_PRESSED:
                    if (is_interior_light_on == 0) {
                        Rte_Call_LightFadeIn();
                        is_interior_light_on = 1;
                        CanIf_Transmit(CAN_SIGNAL_DIMMER_ON); 
                        UART0_SendString("[Task Light] Dimmer ON (CAN Sent)\r\n");
                    } else {
                        Rte_Call_LightFadeOut();
                        is_interior_light_on = 0;
                        CanIf_Transmit(CAN_SIGNAL_DIMMER_OFF); 
                        UART0_SendString("[Task Light] Dimmer OFF (CAN Sent)\r\n");
                    }
                    break;

                default:
                    break;
            }
        }
    }
}



// #include "LightControl_SWC.h"
// #include "Rte_Light.h"
// #include "Rte_Sensor.h"  
// #include "Rte_Types.h"
// #include "cmsis_os2.h" 
// #include "uart.h"

// static uint8_t last_dimmer_sw_state;
// static uint8_t is_interior_light_on;
// static EnvLightState_t last_env_state;

// void LightControl_Init(void) {
//     last_dimmer_sw_state = 1; 
//     is_interior_light_on = 0; 
//     last_env_state = ENV_BRIGHT; 
//     Rte_Write_Headlight(LED_OFF); 
// }

// __NO_RETURN void LightControl_Task(void *argument) {
//     (void)argument;
//     osDelay(20);
//     UART0_SendString("[Task Light] Running...\r\n");

//     while(1) {
//         // --- FEATURE 1: AUTO HEADLIGHT ---
//         EnvLightState_t current_env_state = Rte_Read_EnvLight();
//         if (current_env_state != last_env_state) {
//             if (current_env_state == ENV_DARK) {
//                 Rte_Write_Headlight(LED_ON);
//                 UART0_SendString("[Task Light] Dark detected -> Headlight ON\r\n");
//             } else {
//                 Rte_Write_Headlight(LED_OFF);
//                 UART0_SendString("[Task Light] Bright detected -> Headlight OFF\r\n");
//             }
//             last_env_state = current_env_state;
//         }

//         // --- FEATURE 2: INTERIOR DIMMER ---
//         uint8_t current_dimmer_sw = Rte_Read_DimmerSwitch();
//         if (current_dimmer_sw == 0 && last_dimmer_sw_state == 1) {
//             if (is_interior_light_on == 0) {
//                 Rte_Call_LightFadeIn();
//                 is_interior_light_on = 1; 
//                 UART0_SendString("[Task Light] Button Pressed -> FADE IN\r\n");
//             } else {
//                 Rte_Call_LightFadeOut();
//                 is_interior_light_on = 0; 
//                 UART0_SendString("[Task Light] Button Pressed -> FADE OUT\r\n");
//             }
//         }
//         last_dimmer_sw_state = current_dimmer_sw;

//         // --- SLEEP ---
//         osDelay(50);
//     }
// }