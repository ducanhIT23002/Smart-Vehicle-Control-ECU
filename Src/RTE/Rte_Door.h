#ifndef RTE_DOOR_H
#define RTE_DOOR_H

#include "led_door.h" 
#include "Rte_Types.h"

#define Rte_Read_DoorStatus()             (DoorState_t)ECUAL_ReadDoorSwitch()
#define Rte_Write_P_DoorLed_Status(state) ECUAL_SetRoomLight((uint8_t)state)

#endif