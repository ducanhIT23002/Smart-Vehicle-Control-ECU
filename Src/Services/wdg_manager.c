#include "wdg_manager.h"
#include "wdt.h" 
#include "uart.h" 
#include "cmsis_os2.h" 

static uint8_t task_alive_flags[WDG_MAX_TASKS] = {0};

void WdgM_Init(void) {
    WDT_Init(3000); 
    
    for(int i = 0; i < WDG_MAX_TASKS; i++) {
        task_alive_flags[i] = 1; 
    }
}

void WdgM_CheckpointReached(WdgM_TaskType taskId) {
    if (taskId < WDG_MAX_TASKS) {
        task_alive_flags[taskId] = 1;
    }
}

void WdgM_MainFunction(void) {
    uint8_t is_system_healthy = 1;
    
    for(int i = 0; i < WDG_MAX_TASKS; i++) {
        if (task_alive_flags[i] == 0) {
            is_system_healthy = 0;
            break;
        }
    }

    if (is_system_healthy == 1) {
        WDT_Feed(); 
        
        for(int i = 0; i < WDG_MAX_TASKS; i++) {
            task_alive_flags[i] = 0;
        }
    } else {
        UART0_SendString("[WdgM] CRITICAL ERROR: A Task is DEADLOCK! Hardware Reset impending...\r\n");
    }
}

__NO_RETURN void WdgM_Task(void *argument) {
    (void)argument;
    UART0_SendString("[System] Watchdog Task Started. Alive Supervision Active.\r\n");
    
    while(1) {
        WdgM_MainFunction(); 
        osDelay(1000); 
    }
}