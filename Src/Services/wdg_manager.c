#include "wdg_manager.h"
#include "wdt.h" 

void WdgM_Init(void) {
    WDT_Init(3000); 
}

void WdgM_MainFunction(void) {
    WDT_Feed(); 
}