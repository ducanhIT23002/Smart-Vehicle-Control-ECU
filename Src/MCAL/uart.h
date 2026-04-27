#ifndef UART_H
#define UART_H

#include <stdint.h>

void UART0_Init(uint32_t baudrate);
void UART0_SendChar(char c);
void UART0_SendString(char *str);

#endif /* UART_H */