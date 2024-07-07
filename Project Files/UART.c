#include <lpc17xx.h>
#include "uart.h"

void UART0_Init(void)
{
            LPC_PINCON->PINSEL0 |= 0x50;
            LPC_UART0->LCR = 0x83 ;
            LPC_UART0->DLL = 12;
            LPC_UART0->DLM = 0;
            LPC_UART0->FCR |= 0x07;
            LPC_UART0->FDR = 0xF2;
            LPC_UART0->LCR &= ~0x80;
}