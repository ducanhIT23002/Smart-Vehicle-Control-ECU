#include "interior_light.h"
#include "pwm.h"
#include "timer.h"

void ECUAL_Light_Init(void) {
    PWM_Init(); 
    PWM_SetDutyCycle(0); 
}

void ECUAL_Light_FadeIn(void) {
    for (int i = 0; i <= 100; i += 10) {
        PWM_SetDutyCycle(i);
        for(volatile int d=0; d<50000; d++);
    }
}

void ECUAL_Light_FadeOut(void) {
    for (int i = 100; i >= 0; i -= 10) {
        PWM_SetDutyCycle(i);
        for(volatile int d=0; d<50000; d++); 
    }
}