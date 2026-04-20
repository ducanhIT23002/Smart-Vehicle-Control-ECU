#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <stdint.h>

void ECUAL_LightSensor_Init(void);
uint8_t ECUAL_CheckIsDark(void);

#endif