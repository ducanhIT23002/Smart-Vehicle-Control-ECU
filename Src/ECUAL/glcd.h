#ifndef GLCD_H
#define GLCD_H

#include <stdint.h>

void ECUAL_GLCD_Init(void);
void ECUAL_GLCD_WriteCommand(uint8_t cmd);
void ECUAL_GLCD_WriteData(uint8_t data);
void ECUAL_GLCD_FillColor(uint16_t color); // L?nh test tô full màn hình

#endif