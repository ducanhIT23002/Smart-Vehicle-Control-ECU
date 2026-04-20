#ifndef LED_DOOR_H
#define LED_DOOR_H

#include <stdint.h>

void ECUAL_InitHardware(void);

void ECUAL_SetRoomLight(uint8_t state);

uint8_t ECUAL_ReadDoorSwitch(void);

#endif