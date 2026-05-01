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
        // --- 1. DOOR ---
        case CAN_SIGNAL_DOOR_OPEN:
            tx_msg.id = 0x100;
            tx_msg.dataA = 0x0001; 
            break;
        case CAN_SIGNAL_DOOR_CLOSED:
            tx_msg.id = 0x100;
            tx_msg.dataA = 0x0000; 
            break;
            
        // --- 2. WIPER ---
        case CAN_SIGNAL_WIPER_ON:
            tx_msg.id = 0x200;
            tx_msg.dataA = 0x0001;
            break;
        case CAN_SIGNAL_WIPER_OFF:
            tx_msg.id = 0x200;
            tx_msg.dataA = 0x0000;
            break;
            
        // --- 3. AUTO HEADLIGHT ---
        case CAN_SIGNAL_HEADLIGHT_ON:
            tx_msg.id = 0x300;
            tx_msg.dataA = 0x0001; 
            break;
        case CAN_SIGNAL_HEADLIGHT_OFF:
            tx_msg.id = 0x300;
            tx_msg.dataA = 0x0000; 
            break;

        // --- 4. INTERIOR DIMMER ---
        case CAN_SIGNAL_DIMMER_ON:
            tx_msg.id = 0x400;      
            tx_msg.dataA = 0x0001;  
            break;
        case CAN_SIGNAL_DIMMER_OFF:
            tx_msg.id = 0x400;      
            tx_msg.dataA = 0x0000;  
            break;
            
        default:
            return; 
    }

    CAN1_Send(&tx_msg); 
}