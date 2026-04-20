#include "LPC17xx.h"
#include "gpio.h"

void GPIO_SetDir(uint8_t port, uint8_t pin, uint8_t dir) {
    if (port == 0) {
        if (dir == 1) LPC_GPIO0->FIODIR |= (1 << pin);
        else LPC_GPIO0->FIODIR &= ~(1 << pin);
    }
}

void GPIO_WritePin(uint8_t port, uint8_t pin, uint8_t value) {
    if (port == 0) {
        if (value == 1) LPC_GPIO0->FIOSET = (1 << pin);
        else LPC_GPIO0->FIOCLR = (1 << pin);
    }
}

uint8_t GPIO_ReadPin(uint8_t port, uint8_t pin) {
    if (port == 0) {
        return (LPC_GPIO0->FIOPIN & (1 << pin)) ? 1 : 0;
    }
    return 0;
}