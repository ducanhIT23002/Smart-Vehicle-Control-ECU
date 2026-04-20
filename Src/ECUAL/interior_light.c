#include "interior_light.h"
#include "pwm.h"
#include "cmsis_os2.h"

void ECUAL_Light_Init(void) {
    PWM_Init();
}

void ECUAL_Light_FadeIn(void) {
    for (int i = 0; i <= 100; i += 5) {
        PWM_SetDutyCycle(i);
        osDelay(20);
    }
}

void ECUAL_Light_FadeOut(void) {
    for (int i = 100; i >= 0; i -= 5) {
        PWM_SetDutyCycle(i);
        osDelay(20);
    }
}