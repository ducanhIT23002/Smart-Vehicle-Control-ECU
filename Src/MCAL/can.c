#include "can.h"
#include "LPC17xx.h"

void CAN1_Init(void) {
    LPC_SC->PCONP |= (1 << 13) | (1 << 15);
    LPC_SC->PCLKSEL0 &= ~(3 << 26); 

    LPC_PINCON->PINSEL0 &= ~0x0000000F; 
    LPC_PINCON->PINSEL0 |=  0x00000005; 
    

    LPC_PINCON->PINMODE0 &= ~0x0000000F; 

    LPC_CAN1->MOD = 1;
    LPC_CAN1->BTR = 0x00250004;

    LPC_CANAF->AFMR = 0x02;

    LPC_CAN1->MOD = (1 << 2); 
}

void CAN1_Send(CAN_Message *msg) {
    while (!(LPC_CAN1->SR & (1 << 2))); 
    
    LPC_CAN1->TFI1 = (msg->dlc << 16); 
    LPC_CAN1->TID1 = msg->id;
    LPC_CAN1->TDA1 = msg->dataA;
    LPC_CAN1->TDB1 = msg->dataB;
    

    LPC_CAN1->CMR = (1 << 5) | (1 << 4) | (1 << 0);
}

uint8_t CAN1_Receive(CAN_Message *msg) {
    if (LPC_CAN1->GSR & (1 << 0)) {
        msg->id    = LPC_CAN1->RID;
        msg->dataA = LPC_CAN1->RDA;
        msg->dataB = LPC_CAN1->RDB;
        msg->dlc   = (LPC_CAN1->RFS >> 16) & 0x0F;
        LPC_CAN1->CMR = (1 << 2); 
        return 1;
    }
    return 0;
}