#include "wiper_switch.h"
#include "gpio.h"

#define SWITCH_PORT 1
#define SWITCH_PIN  24

void ECUAL_WiperSwitch_Init(void) {
    GPIO_SetDir(SWITCH_PORT, SWITCH_PIN, 0);
}

uint8_t ECUAL_ReadWiperSwitch(void) {
    return GPIO_ReadPin(SWITCH_PORT, SWITCH_PIN);
}