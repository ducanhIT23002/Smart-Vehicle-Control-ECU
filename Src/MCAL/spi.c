#include "spi.h"
#include "LPC17xx.h"

void MCAL_SPI_Init(void) {
    // 1. C?p ngu?n và chia xung nh?p cho kh?i SSP0
    LPC_SC->PCONP |= (1 << 21);
    LPC_SC->PCLKSEL1 &= ~(3 << 10); 

    // 2. D?n s?ch rác và Set ch?c nang chân chu?n ch? (Alternative Function 2)
    LPC_PINCON->PINSEL0 &= ~(3 << 30);
    LPC_PINCON->PINSEL0 |=  (2 << 30); // SCK0 (P0.15)

    LPC_PINCON->PINSEL1 &= ~((3 << 2) | (3 << 4));
    LPC_PINCON->PINSEL1 |=  ((2 << 2) | (2 << 4)); // MISO0 (P0.17), MOSI0 (P0.18)

    // SSEL0 (P0.16) làm GPIO Output d? ch?n chip
    LPC_PINCON->PINSEL1 &= ~(3 << 0);
    LPC_GPIO0->FIODIR |= (1 << 16);
    LPC_GPIO0->FIOSET = (1 << 16); 

    // 3. C?u hình Frame 8-bit (DSS = 0111)
    LPC_SSP0->CR0 = 0x07; 
    
    // 4. B?T INTERNAL LOOPBACK VÀ KÍCH HO?T SPI
    // Bit 0 là LBM (Loop Back Mode) - T? ch?p MOSI vào MISO bên trong lõi chip!
    // Bit 1 là SSE (Kích ho?t b? SSP)
    LPC_SSP0->CR1 = (1 << 1) | (1 << 0); 
    
    // 5. T?c d? truy?n
    LPC_SSP0->CPSR = 8; 

    // 6. Xóa s?ch b? d?m nh?n (Flush RX FIFO) l? có rác
    while (LPC_SSP0->SR & (1 << 2)) {
        volatile uint32_t dummy = LPC_SSP0->DR;
    }
}

uint8_t MCAL_SPI_Transfer(uint8_t data) {
    // Kéo chân CS xu?ng Low
    LPC_GPIO0->FIOCLR = (1 << 16);

    // G?i data
    LPC_SSP0->DR = data;

    // Ch? d?n khi Bus h?t b?n (BSY = 0)
    while (LPC_SSP0->SR & (1 << 4));

    // Kéo chân CS lên High
    LPC_GPIO0->FIOSET = (1 << 16);

    // Ð?c data tr? v?
    return (LPC_SSP0->DR & 0xFF);
}