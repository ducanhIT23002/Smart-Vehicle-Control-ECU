#include "InputMonitor_SWC.h"
#include "Rte_Types.h"
#include "Rte_Door.h"
#include "Rte_Wiper.h"
#include "Rte_Light.h"
#include "Rte_Sensor.h"
#include "cmsis_os2.h"
#include "wdg_manager.h" 

extern osMessageQueueId_t doorQueue;
extern osMessageQueueId_t wiperQueue;
extern osMessageQueueId_t lightQueue;

void InputMonitor_Init(void) {}

__NO_RETURN void InputMonitor_Task(void *argument) {
    (void)argument;
    static uint8_t last_door = 1;      
    static uint8_t last_wiper_sw = 1;  
    static uint8_t last_dimmer_sw = 1; 
    static EnvLightState_t last_env = ENV_BRIGHT; 

    while(1) {
        WdgM_CheckpointReached(WDG_INPUT_TASK_ID);

        SystemEvent_t event_msg;

        uint8_t current_door = Rte_Read_DoorStatus();
        if (current_door != last_door) {
            event_msg = (current_door == 1) ? SYS_EVT_DOOR_OPENED : SYS_EVT_DOOR_CLOSED;
            osMessageQueuePut(doorQueue, &event_msg, 0, 0); 
            last_door = current_door;
        }

        uint8_t current_wiper_sw = Rte_Read_WiperSwitch();
        if (current_wiper_sw == 0 && last_wiper_sw == 1) { 
            event_msg = SYS_EVT_WIPER_BTN_PRESSED;
            osMessageQueuePut(wiperQueue, &event_msg, 0, 0);
        }
        last_wiper_sw = current_wiper_sw;

        uint8_t current_dimmer_sw = Rte_Read_DimmerSwitch();
        if (current_dimmer_sw == 0 && last_dimmer_sw == 1) { 
            event_msg = SYS_EVT_DIMMER_BTN_PRESSED;
            osMessageQueuePut(lightQueue, &event_msg, 0, 0);
        }
        last_dimmer_sw = current_dimmer_sw;

        EnvLightState_t current_env = Rte_Read_EnvLight();
        if (current_env != last_env) {
            event_msg = (current_env == ENV_DARK) ? SYS_EVT_ENV_DARK : SYS_EVT_ENV_BRIGHT;
            osMessageQueuePut(lightQueue, &event_msg, 0, 0);
            last_env = current_env;
        }

        osDelay(50);
    }
}