#include "wdt.h"
#include "LPC17xx.h"

void WDT_Init(uint32_t timeout_ms) {

    uint32_t wd_counter = (timeout_ms * 1000); 

    LPC_WDT->WDTC = wd_counter;

    LPC_WDT->WDMOD = (1 << 0) | (1 << 1);

    WDT_Feed();
}

void WDT_Feed(void) {
    LPC_WDT->WDFEED = 0xAA;
    LPC_WDT->WDFEED = 0x55;
}