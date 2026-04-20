#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void MCAL_ADC_Init(void);
uint16_t MCAL_ADC_GetRawValue(void);

#endif