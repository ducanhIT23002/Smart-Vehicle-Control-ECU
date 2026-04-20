#ifndef PWM_H
#define PWM_H

#include <stdint.h> 


void PWM_Init(void);

void PWM_SetDutyCycle(uint8_t duty_percent);

#endif