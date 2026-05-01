#ifndef WDG_MANAGER_H
#define WDG_MANAGER_H

typedef enum {
    WDG_INPUT_TASK_ID = 0,
    WDG_DOOR_TASK_ID,
    WDG_WIPER_TASK_ID,
    WDG_LIGHT_TASK_ID,
    WDG_MAX_TASKS 
} WdgM_TaskType;

void WdgM_Init(void);
void WdgM_MainFunction(void);

void WdgM_CheckpointReached(WdgM_TaskType taskId);
void WdgM_Task(void *argument);
#endif