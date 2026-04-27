#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

void GPIO_SetDir(uint8_t port, uint8_t pin, uint8_t dir);

void GPIO_WritePin(uint8_t port, uint8_t pin, uint8_t value);

uint8_t GPIO_ReadPin(uint8_t port, uint8_t pin);

void GPIO_TogglePin(uint8_t port, uint8_t pin);
#endif