#include "LPC17xx.h"

void PWM_Init(void) {
    LPC_SC->PCONP |= (1 << 6); 
    
    LPC_PINCON->PINSEL4 &= ~(3 << 4); 
    LPC_PINCON->PINSEL4 |= (1 << 4);  

    LPC_PWM1->PR = 0;   
    LPC_PWM1->MR0 = 25000; 

    LPC_PWM1->MCR = (1 << 1); 
    LPC_PWM1->LER = (1 << 0);

    
    LPC_PWM1->PCR |= (1 << 11); 
    LPC_PWM1->TCR = (1 << 0) | (1 << 3); 
}

void PWM_SetDutyCycle(uint8_t duty_percent) {
    if (duty_percent > 100) duty_percent = 100;
    
    uint32_t active_time = (25000 * duty_percent) / 100;
    
    LPC_PWM1->MR3 = active_time;
    LPC_PWM1->LER |= (1 << 3); 
}