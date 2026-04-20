#include "LPC17xx.h"

void PWM_Init(void) {
    LPC_SC->PCONP |= (1 << 6); 
    
    LPC_PINCON->PINSEL4 &= ~(0x03 << 0);
    LPC_PINCON->PINSEL4 |=  (0x01 << 0);
    
    LPC_PWM1->MR0 = 25000;
    
    LPC_PWM1->MR1 = 0;
    
    LPC_PWM1->MCR = (1 << 1);
    LPC_PWM1->LER = (1 << 0) | (1 << 1);
    LPC_PWM1->PCR = (1 << 9);
    LPC_PWM1->TCR = (1 << 0) | (1 << 3);
}

void PWM_SetDutyCycle(uint8_t duty_percent) {
    if (duty_percent > 100) duty_percent = 100;
    
    uint32_t mr1_value = (duty_percent * 25000) / 100;
    
    LPC_PWM1->MR1 = mr1_value; 
    LPC_PWM1->LER = (1 << 1);
}