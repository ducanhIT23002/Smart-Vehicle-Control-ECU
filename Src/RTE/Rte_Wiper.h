#ifndef RTE_WIPER_H
#define RTE_WIPER_H

#include "wiper.h"
#include "wiper_switch.h"

#define Rte_Call_Wiper_StartIntMode()  ECUAL_Wiper_SetMode(WIPER_INT)
#define Rte_Call_Wiper_Stop()          ECUAL_Wiper_SetMode(WIPER_OFF)

#define Rte_Write_WiperMode(mode)      ECUAL_Wiper_SetMode(mode)

#define Rte_Read_WiperSwitch()         ECUAL_ReadWiperSwitch()

#endif