// OTHER
#include "can.h"
#include "LPC17xx.h"

// void CAN1_Init(void) {
//     // 1. Cấp nguồn
//     LPC_SC->PCONP |= (1 << 13) | (1 << 14) | (1 << 15);
//     LPC_SC->PCLKSEL0 &= ~((3 << 24) | (3 << 26)); 

//     // 2. Mở chân vật lý cho cổng CAN1 (P0.0 và P0.1)
//     LPC_PINCON->PINSEL0 &= ~0x0000000F; 
//     LPC_PINCON->PINSEL0 |=  0x00000005; 

//     // 3. Đưa vào Reset Mode 
//     LPC_CAN1->MOD = 1;
//     LPC_CAN2->MOD = 1; // Giữ để tránh lỗi bộ lọc của NXP

//     // 4. Baudrate 500kbps 
//     LPC_CAN1->BTR = 0x00250004;

//     // 5. Bypass bộ lọc nhận tất cả
//     LPC_CANAF->AFMR = 0x02; 

//     // 6. Chạy chế độ dây thật (Normal Mode)
//     LPC_CAN1->MOD = 0; 
//     LPC_CAN2->MOD = 0;        
// }

// void CAN1_Send(CAN_Message *msg) {
//     while (!(LPC_CAN1->SR & (1 << 2))); // Chờ trống
    
//     LPC_CAN1->TFI1 = (msg->dlc << 16); 
//     LPC_CAN1->TID1 = msg->id;
//     LPC_CAN1->TDA1 = msg->dataA;
//     LPC_CAN1->TDB1 = msg->dataB;
    
//     // Phát ra cổng CAN1
//     LPC_CAN1->CMR = (1 << 5) | (1 << 0);
// }

// uint8_t CAN1_Receive(CAN_Message *msg) {
//     if (LPC_CAN1->GSR & (1 << 0)) { // Cờ nhận của cổng CAN1
//         msg->id    = LPC_CAN1->RID;
//         msg->dataA = LPC_CAN1->RDA;
//         msg->dataB = LPC_CAN1->RDB;
//         msg->dlc   = (LPC_CAN1->RFS >> 16) & 0x0F;
        
//         LPC_CAN1->CMR = (1 << 2); 
//         return 1;
//     }
//     return 0;
// }

// LOOPBACK TEST ----
void CAN1_Init(void) {
    LPC_SC->PCONP |= (1 << 13) | (1 << 14) | (1 << 15);
    LPC_SC->PCLKSEL0 &= ~((3 << 24) | (3 << 26)); 


    LPC_PINCON->PINSEL0 &= ~0x0000000F; 
    LPC_PINCON->PINSEL0 |=  0x00000005; 

    LPC_PINCON->PINSEL4 &= ~0x0003C000;
    LPC_PINCON->PINSEL4 |=  0x00014000; 

    LPC_CAN1->MOD = 1;
    LPC_CAN2->MOD = 1; 

    
    LPC_CAN1->BTR = 0x00250004;
    LPC_CAN2->BTR = 0x00250004;

    LPC_CANAF->AFMR = 0x02; 


    LPC_CAN1->MOD = 0; 
    LPC_CAN2->MOD = 0;        
}



void CAN1_Send(CAN_Message *msg) {
    uint32_t timeout = 100000; 

    while (!(LPC_CAN1->SR & (1 << 2))) {
        timeout--;
        if (timeout == 0) {
            return; 
        }
    }    
    LPC_CAN1->TFI1 = (msg->dlc << 16); 
    LPC_CAN1->TID1 = msg->id;
    LPC_CAN1->TDA1 = msg->dataA;
    LPC_CAN1->TDB1 = msg->dataB;
    
    LPC_CAN1->CMR = (1 << 5) | (1 << 0);
}

uint8_t CAN2_Receive(CAN_Message *msg) {
    if (LPC_CAN2->GSR & (1 << 0)) { 
        msg->id    = LPC_CAN2->RID;
        msg->dataA = LPC_CAN2->RDA;
        msg->dataB = LPC_CAN2->RDB;
        msg->dlc   = (LPC_CAN2->RFS >> 16) & 0x0F;
        
        LPC_CAN2->CMR = (1 << 2); 
        return 1;
    }
    return 0;
}

// LOOPBACK TEST ----