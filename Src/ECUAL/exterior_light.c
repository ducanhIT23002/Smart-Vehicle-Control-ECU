#include "exterior_light.h"
#include "gpio.h"

#define HEADLIGHT_PORT 1
#define HEADLIGHT_PIN  28

void ECUAL_Headlight_Init(void) {
    GPIO_SetDir(HEADLIGHT_PORT, HEADLIGHT_PIN, 1);
}

void ECUAL_Headlight_TurnOn(void) {
    GPIO_WritePin(HEADLIGHT_PORT, HEADLIGHT_PIN, 1);
}

void ECUAL_Headlight_TurnOff(void) {
    GPIO_WritePin(HEADLIGHT_PORT, HEADLIGHT_PIN, 0);
}