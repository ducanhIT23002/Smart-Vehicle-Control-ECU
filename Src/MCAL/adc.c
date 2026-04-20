#include "LPC17xx.h"
#include "adc.h"
#include "dma.h"

volatile uint32_t adc_ram_buffer = 0;

void MCAL_ADC_Init(void) {
    LPC_SC->PCONP |= (1 << 12);
    LPC_PINCON->PINSEL1 |= (1 << 14);
    LPC_ADC->ADCR = (1 << 2) | (4 << 8) | (1 << 16) | (1 << 21);
    MCAL_DMA_Connect_ADC((uint32_t)&(LPC_ADC->ADGDR), (uint32_t)&adc_ram_buffer);
}

uint16_t MCAL_ADC_GetRawValue(void) {
    return (adc_ram_buffer >> 4) & 0xFFF;
}