// Nucleo Board has USART3 by default. It is connected to APB1 Bus.
// Table 10 of Nucleo User manual: Alternate Function AF7: Pin D8: USART3_TX and Pin D9: USART3_RX

#include "stm32h7xx.h"
#include <stdio.h>
#include "uart.h"



int main(void)
{
    int x;
	uart3_tx_init();

	while(1)
	{
		 printf("Hello from Nucleo STM32H7.....\n\r");
		 for(int i=0;i<9000;i++)
		 {
			 x++;
		 }
	}
}

