#ifndef RTE_DOOR_H
#define RTE_DOOR_H

#include "led_door.h" 

#define Rte_Read_DoorStatus()            ECUAL_ReadDoorSwitch()

#define Rte_Write_P_DoorLed_Status(state) ECUAL_SetRoomLight(state)

#endif