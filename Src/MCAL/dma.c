#include "LPC17xx.h"
#include "dma.h"


typedef struct {
    uint32_t SrcAddr;
    uint32_t DstAddr;
    uint32_t NextLLI;
    uint32_t Control;
} DMA_LLI_t;

static DMA_LLI_t adc_lli;

void MCAL_DMA_Init(void) {
    LPC_SC->PCONP |= (1 << 29); 
    LPC_GPDMA->DMACConfig = 1;  
}

void MCAL_DMA_Connect_ADC(uint32_t src_addr, uint32_t dest_addr) {
    LPC_GPDMA->DMACIntTCClear = 1;

    uint32_t control_config = 1 | (2 << 18) | (2 << 21);

    adc_lli.SrcAddr = src_addr;
    adc_lli.DstAddr = dest_addr;
    adc_lli.NextLLI = (uint32_t)&adc_lli;  
    adc_lli.Control = control_config;

    LPC_GPDMACH0->DMACCSrcAddr = src_addr;
    LPC_GPDMACH0->DMACCDestAddr = dest_addr;
    LPC_GPDMACH0->DMACCLLI = (uint32_t)&adc_lli; 
    LPC_GPDMACH0->DMACCControl = control_config;


    LPC_GPDMACH0->DMACCConfig = (1 << 0) | (4 << 1) | (2 << 11);
}