#include "can_if.h"
#include "can.h" 

void CanIf_Init(void) {
    CAN1_Init(); 
}

void CanIf_Transmit(CanIf_SignalType signal) {
    CAN_Message tx_msg;
    tx_msg.dlc = 4;
    tx_msg.dataB = 0;

    switch (signal) {
        case CAN_SIGNAL_DOOR_OPEN:
            tx_msg.id = 0x100;
            tx_msg.dataA = 0x0001; 
            break;
            
        case CAN_SIGNAL_WIPER_ON:
            tx_msg.id = 0x200;
            tx_msg.dataA = 0x00FF;
            break;
            
        case CAN_SIGNAL_LIGHT_AUTO:
            tx_msg.id = 0x300;
            tx_msg.dataA = 0xAAAA; 
            break;
            
        default:
            return; 
    }

    CAN1_Send(&tx_msg); 
}