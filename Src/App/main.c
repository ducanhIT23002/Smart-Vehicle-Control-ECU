#include "LPC17xx.h"
#include "gpio.h"
#include "can_if.h"
#include "uart.h"       
#include "cmsis_os2.h" 
#include "Rte_Types.h"
#include "DoorControl_SWC.h"
#include "WiperControl_SWC.h"
#include "LightControl_SWC.h"
#include "InputMonitor_SWC.h"
extern void ECUAL_InitHardware(void);
extern void ECUAL_Headlight_Init(void);
extern void ECUAL_Light_Init(void);
extern void ECUAL_LightSensor_Init(void);
extern void ECUAL_Wiper_Init(void);
extern void ECUAL_WiperSwitch_Init(void);

extern void DoorControl_Task(void *argument);
extern void WiperControl_Task(void *argument);
extern void LightControl_Task(void *argument);

osThreadId_t doorTask_id, wiperTask_id, lightTask_id;
osThreadId_t inputTask_id;
osMessageQueueId_t doorQueue;
osMessageQueueId_t wiperQueue;
osMessageQueueId_t lightQueue;

int main(void) {
    SystemInit();
    UART0_Init(9600);
    UART0_SendString("\r\n=== System Booting ===\r\n");
    
    ECUAL_InitHardware();      
    ECUAL_Headlight_Init();  
    ECUAL_Light_Init();        
    ECUAL_LightSensor_Init();  
    ECUAL_Wiper_Init();        
    ECUAL_WiperSwitch_Init(); 
    CanIf_Init(); 

    DoorControl_Init();
    WiperControl_Init();
    LightControl_Init();
	InputMonitor_Init();
    osKernelInitialize(); 

    doorQueue  = osMessageQueueNew(5, sizeof(SystemEvent_t), NULL);
    wiperQueue = osMessageQueueNew(5, sizeof(SystemEvent_t), NULL);
    lightQueue = osMessageQueueNew(5, sizeof(SystemEvent_t), NULL);

    doorTask_id  = osThreadNew(DoorControl_Task, NULL, NULL);
    wiperTask_id = osThreadNew(WiperControl_Task, NULL, NULL);
    lightTask_id = osThreadNew(LightControl_Task, NULL, NULL);
		inputTask_id = osThreadNew(InputMonitor_Task, NULL, NULL);
    UART0_SendString("Starting OS Kernel...\r\n");
    osKernelStart();

    while(1) {} // System is now managed by RTOS
}

