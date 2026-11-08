// Nucleo Board has USART3 by default. It is connected to APB1 Bus.
// Table 10 of Nucleo User manual: Alternate Function AF7: Pin D8: USART3_TX and Pin D9: USART3_RX

#include "stm32h7xx.h"
#include <stdio.h>
#include "uart.h"
#include "led.h"
#include "adc.h"

int sensor_val;

int main(void)
{
	int x, i;
	pa3_adc1_init();
	uart3_tx_init();

	while(1)
	{
		sensor_val = adc_get_data();
		printf(" Sensor Value: %d \n\r", sensor_val);

		for(i=0;i<10000;i++){		// just add x++ to not optimize away the loop
			x++;
		}
	}
}
