#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void MCAL_Timer0_Init(uint32_t ms);
void MCAL_Timer0_SetCallback(void (*callback)(void));

#endif