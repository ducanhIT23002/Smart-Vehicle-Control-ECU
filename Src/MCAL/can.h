#ifndef CAN_H
#define CAN_H

#include <stdint.h>

typedef struct {
    uint32_t id;
    uint32_t dataA;
    uint32_t dataB;
    uint8_t  dlc;
} CAN_Message;

void CAN1_Init(void);
void CAN1_Send(CAN_Message *msg);
uint8_t CAN2_Receive(CAN_Message *msg);

#endif