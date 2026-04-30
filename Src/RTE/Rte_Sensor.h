#ifndef RTE_SENSOR_H
#define RTE_SENSOR_H

#include "Rte_Types.h"
#include "light_sensor.h"

#define Rte_Read_EnvLight() (EnvLightState_t)ECUAL_CheckIsDark()

#endif