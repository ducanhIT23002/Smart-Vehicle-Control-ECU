#ifndef WDT_H
#define WDT_H

#include <stdint.h>

void WDT_Init(uint32_t timeout_ms);
void WDT_Feed(void);

#endif