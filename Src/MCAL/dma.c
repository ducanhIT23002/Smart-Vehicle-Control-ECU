#include "LPC17xx.h"
#include "dma.h"

void MCAL_DMA_Init(void) {
    LPC_SC->PCONP |= (1 << 29);
    LPC_GPDMA->DMACConfig = 1;
}

void MCAL_DMA_Connect_ADC(uint32_t src_addr, uint32_t dest_addr) {
    LPC_GPDMA->DMACIntTCClear = 1;
    LPC_GPDMACH0->DMACCSrcAddr = src_addr;
    LPC_GPDMACH0->DMACCDestAddr = dest_addr;
    LPC_GPDMACH0->DMACCControl = (1 << 18) | (2 << 21);
    LPC_GPDMACH0->DMACCConfig = (1 << 0) | (4 << 1) | (1 << 11);
}