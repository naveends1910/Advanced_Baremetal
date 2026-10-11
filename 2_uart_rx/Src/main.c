// Nucleo Board has USART3 by default. It is connected to APB1 Bus.
// Table 10 of Nucleo User manual: Alternate Function AF7: Pin D8: USART3_TX and Pin D9: USART3_RX

#include "stm32h7xx.h"
#include <stdio.h>
#include "uart.h"
#include "led.h"

char ch;

int main(void)
{
    user_leds_init();
	uart3_rxtx_init();

	while(1)
	{

		ch = uart_read(USART3);

	    switch(ch)
	    {
	    case 'o':
	    	all_leds_off();
	    	break;
	    case 'a':
	    	all_leds_on();
	    	break;
	    case 't':
	    	all_leds_toggle();
	    	break;

	    default:
	    	break;
	    }
	}
}
