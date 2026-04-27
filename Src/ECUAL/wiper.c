#include "wiper.h"
#include "gpio.h"

#define WIPER_MOTOR_PORT 1
#define WIPER_MOTOR_PIN  29 

void ECUAL_Wiper_Init(void) {
    GPIO_SetDir(WIPER_MOTOR_PORT, WIPER_MOTOR_PIN, 1);
    GPIO_WritePin(WIPER_MOTOR_PORT, WIPER_MOTOR_PIN, 0); 
}

void ECUAL_Wiper_SetMode(WiperMode_t mode) {
    if (mode == WIPER_INT) {
        GPIO_WritePin(WIPER_MOTOR_PORT, WIPER_MOTOR_PIN, 1);
    } else {
        GPIO_WritePin(WIPER_MOTOR_PORT, WIPER_MOTOR_PIN, 0);
    }
}