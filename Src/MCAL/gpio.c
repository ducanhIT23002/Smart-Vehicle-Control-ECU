#include "LPC17xx.h"
#include "gpio.h"
#include <stddef.h>

static LPC_GPIO_TypeDef* GPIO_GetBase(uint8_t port) {
    switch (port) {
        case 0: return LPC_GPIO0;
        case 1: return LPC_GPIO1;
        case 2: return LPC_GPIO2;
        default: return NULL;
    }
}

void GPIO_SetDir(uint8_t port, uint8_t pin, uint8_t dir) {
    LPC_GPIO_TypeDef* gpio = GPIO_GetBase(port);
    if (gpio != NULL) {
        if (dir == 1) gpio->FIODIR |= (1 << pin);
        else gpio->FIODIR &= ~(1 << pin);
    }
}

void GPIO_WritePin(uint8_t port, uint8_t pin, uint8_t value) {
    LPC_GPIO_TypeDef* gpio = GPIO_GetBase(port);
    if (gpio != NULL) {
        if (value == 1) gpio->FIOSET = (1 << pin);
        else gpio->FIOCLR = (1 << pin);
    }
}

uint8_t GPIO_ReadPin(uint8_t port, uint8_t pin) {
    LPC_GPIO_TypeDef* gpio = GPIO_GetBase(port);
    if (gpio != NULL) {
        return (gpio->FIOPIN & (1 << pin)) ? 1 : 0;
    }
    return 0;
}

void GPIO_TogglePin(uint8_t port, uint8_t pin) {
    LPC_GPIO_TypeDef* gpio = GPIO_GetBase(port);
    if (gpio != NULL) {
        gpio->FIOPIN ^= (1 << pin);
    }
}
