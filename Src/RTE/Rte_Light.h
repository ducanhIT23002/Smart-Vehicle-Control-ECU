#ifndef RTE_LIGHT_H
#define RTE_LIGHT_H

#include "interior_light.h" 
#include "exterior_light.h"

#define Rte_Call_LightFadeIn()  ECUAL_Light_FadeIn()
#define Rte_Call_LightFadeOut() ECUAL_Light_FadeOut()

#define Rte_Call_Headlight_TurnOn()  ECUAL_Headlight_TurnOn()
#define Rte_Call_Headlight_TurnOff() ECUAL_Headlight_TurnOff()

#endif