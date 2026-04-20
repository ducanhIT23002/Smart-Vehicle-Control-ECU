#include "LPC17xx.h"
#include "timer.h"

static void (*timer0_callback)(void) = 0;

void MCAL_Timer0_Init(uint32_t ms) {
    LPC_SC->PCONP |= (1 << 1);
    LPC_TIM0->PR = 25000 - 1;
    LPC_TIM0->MR0 = ms;
    LPC_TIM0->MCR = (1 << 0) | (1 << 1);
    NVIC_EnableIRQ(TIMER0_IRQn);
    LPC_TIM0->TCR = 1;
}

void MCAL_Timer0_SetCallback(void (*callback)(void)) {
    timer0_callback = callback;
}

void TIMER0_IRQHandler(void) {
    if (LPC_TIM0->IR & (1 << 0)) {
        if (timer0_callback) timer0_callback();
        LPC_TIM0->IR = (1 << 0);
    }
}