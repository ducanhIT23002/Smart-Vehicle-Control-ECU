#include "LPC17xx.h"
#include "uart.h"

void UART0_Init(uint32_t baudrate) {
    uint32_t Fdiv;
    
    LPC_SC->PCONP |= (1 << 3); 
    
    LPC_PINCON->PINSEL0 &= ~0x000000F0;
    LPC_PINCON->PINSEL0 |= 0x00000050;
    
    LPC_UART0->LCR = 0x83; 
    
    Fdiv = (25000000 / 16) / baudrate; 
    LPC_UART0->DLM = Fdiv / 256;
    LPC_UART0->DLL = Fdiv % 256;
    
    LPC_UART0->LCR = 0x03;
    LPC_UART0->FCR = 0x07;
}

void UART0_SendChar(char c) {
    while (!(LPC_UART0->LSR & 0x20));
    LPC_UART0->THR = c;
}

void UART0_SendString(char *str) {
    while (*str != '\0') {
        UART0_SendChar(*str++);
    }
}