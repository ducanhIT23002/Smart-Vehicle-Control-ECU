#ifndef DMA_H
#define DMA_H

#include <stdint.h>

void MCAL_DMA_Init(void);
void MCAL_DMA_Connect_ADC(uint32_t src_addr, uint32_t dest_addr);

#endif