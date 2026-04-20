#include "led_door.h"
#include "gpio.h"
#include "uart.h"

#define LED_PORT 0
#define LED_PIN  5
#define BTN_PORT 0
#define BTN_PIN  6

void ECUAL_InitHardware(void) {
    GPIO_SetDir(LED_PORT, LED_PIN, 1);
    GPIO_SetDir(BTN_PORT, BTN_PIN, 0);
}

void ECUAL_SetRoomLight(uint8_t state) {
    GPIO_WritePin(LED_PORT, LED_PIN, state);
    
    if(state == 1) UART0_SendString("[ECUAL] Room Light is ON! (*)\r\n");
    else UART0_SendString("[ECUAL] Room Light is OFF. ( )\r\n");
}

uint8_t ECUAL_ReadDoorSwitch(void) {
    return GPIO_ReadPin(BTN_PORT, BTN_PIN);
}