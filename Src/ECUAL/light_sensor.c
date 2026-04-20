#include "light_sensor.h"
#include "adc.h"
#include "dma.h"

#define DARK_THRESHOLD 3000

void ECUAL_LightSensor_Init(void) {
    MCAL_DMA_Init();
    MCAL_ADC_Init();
}

uint8_t ECUAL_CheckIsDark(void) {
    uint16_t raw_value = MCAL_ADC_GetRawValue();
    if (raw_value >= DARK_THRESHOLD) {
        return 1;
    }
    return 0;
}