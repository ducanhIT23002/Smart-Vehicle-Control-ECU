#ifndef CAN_IF_H
#define CAN_IF_H

#include <stdint.h>

typedef enum {
    CAN_SIGNAL_DOOR_OPEN = 0,
    CAN_SIGNAL_DOOR_CLOSED,
    
    CAN_SIGNAL_WIPER_ON,
    CAN_SIGNAL_WIPER_OFF,
    
    CAN_SIGNAL_HEADLIGHT_ON,
    CAN_SIGNAL_HEADLIGHT_OFF,
    
    CAN_SIGNAL_DIMMER_ON,
    CAN_SIGNAL_DIMMER_OFF
} CanIf_SignalType;

void CanIf_Init(void);
void CanIf_Transmit(CanIf_SignalType signal);

#endif