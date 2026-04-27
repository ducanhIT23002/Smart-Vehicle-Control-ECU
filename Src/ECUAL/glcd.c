#include "glcd.h"
#include "spi.h"   
#include "gpio.h"  

#define GLCD_DC_PORT 0
#define GLCD_DC_PIN  19

void ECUAL_GLCD_Init(void) {
    GPIO_SetDir(GLCD_DC_PORT, GLCD_DC_PIN, 1);
    
    ECUAL_GLCD_WriteCommand(0x11); 
    for(volatile int i=0; i<500000; i++);
    
    ECUAL_GLCD_WriteCommand(0x29);
}

void ECUAL_GLCD_WriteCommand(uint8_t cmd) {
    GPIO_WritePin(GLCD_DC_PORT, GLCD_DC_PIN, 0);
    
    MCAL_SPI_Transfer(cmd);
}

void ECUAL_GLCD_WriteData(uint8_t data) {
    GPIO_WritePin(GLCD_DC_PORT, GLCD_DC_PIN, 1);
    
    MCAL_SPI_Transfer(data);
}

void ECUAL_GLCD_FillColor(uint16_t color) {
    ECUAL_GLCD_WriteCommand(0x2C); 

    for(int i = 0; i < (128 * 160); i++) {
        ECUAL_GLCD_WriteData(color >> 8);   
        ECUAL_GLCD_WriteData(color & 0xFF);
    }
}