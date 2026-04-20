#ifndef WIPER_H
#define WIPER_H

typedef enum { WIPER_OFF, WIPER_INT } WiperMode_t;

void ECUAL_Wiper_Init(void);
void ECUAL_Wiper_SetMode(WiperMode_t mode);

#endif