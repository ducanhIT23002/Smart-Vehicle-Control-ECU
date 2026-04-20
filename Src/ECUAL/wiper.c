#include "wiper.h"
#include "gpio.h"
#include "timer.h"

#define WIPER_MOTOR_PIN 10

void Wiper_Action_Callback(void) {
    GPIO_WritePin(0, WIPER_MOTOR_PIN, 1);   
    for(volatile int i = 0; i < 50000; i++); 
    GPIO_WritePin(0, WIPER_MOTOR_PIN, 0);
}

void ECUAL_Wiper_Init(void) {
    GPIO_SetDir(0, WIPER_MOTOR_PIN, 1);
    MCAL_Timer0_SetCallback(Wiper_Action_Callback);
}

void ECUAL_Wiper_SetMode(WiperMode_t mode) {
    if (mode == WIPER_INT) {
        MCAL_Timer0_Init(3000);
    } else {
    }
}