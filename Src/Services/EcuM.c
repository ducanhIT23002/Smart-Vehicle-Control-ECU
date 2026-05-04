#include "EcuM.h"

extern void ECUAL_InitHardware(void);
extern void ECUAL_Headlight_Init(void);
extern void ECUAL_Light_Init(void);
extern void ECUAL_LightSensor_Init(void);
extern void ECUAL_Wiper_Init(void);
extern void ECUAL_WiperSwitch_Init(void);

void EcuM_Init(void) {
    ECUAL_InitHardware();      
    ECUAL_Headlight_Init();  
    ECUAL_Light_Init();        
    ECUAL_LightSensor_Init();  
    ECUAL_Wiper_Init();        
    ECUAL_WiperSwitch_Init(); 
}