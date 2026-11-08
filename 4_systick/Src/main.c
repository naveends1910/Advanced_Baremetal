// Nucleo Board has USART3 by default. It is connected to APB1 Bus.
// Table 10 of Nucleo User manual: Alternate Function AF7: Pin D8: USART3_TX and Pin D9: USART3_RX

#include "stm32h7xx.h"
#include <stdio.h>
#include "uart.h"
#include "led.h"
#include "adc.h"
#include "systick.h"

int sensor_val;

int main(void)
{
	uart3_tx_init();

	while(1)
	{
	      printf("A second just passed!! \n\r");
	      systickDelayMs(4000);

	}
}
