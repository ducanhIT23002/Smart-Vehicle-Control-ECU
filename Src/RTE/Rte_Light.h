#ifndef RTE_LIGHT_H
#define RTE_LIGHT_H

#include "Rte_Types.h"
#include "exterior_light.h"
#include "interior_light.h"

#define Rte_Write_Headlight(state)    ((state == LED_ON) ? ECUAL_Headlight_TurnOn() : ECUAL_Headlight_TurnOff())

#define Rte_Read_DimmerSwitch()       ECUAL_ReadDimmerSwitch() 
#define Rte_Call_LightFadeIn()        ECUAL_Light_FadeIn()
#define Rte_Call_LightFadeOut()       ECUAL_Light_FadeOut()

#endif /* RTE_LIGHT_H */