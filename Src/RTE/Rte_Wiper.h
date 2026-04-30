#ifndef RTE_WIPER_H
#define RTE_WIPER_H

#include "Rte_Types.h"
#include "wiper.h"
#include "wiper_switch.h"

#define Rte_Read_WiperSwitch()       (WiperSwitchState_t)ECUAL_ReadWiperSwitch()

#define Rte_Write_WiperMode(mode)    ECUAL_Wiper_SetMode((WiperMode_t)mode)

#endif /* RTE_WIPER_H */