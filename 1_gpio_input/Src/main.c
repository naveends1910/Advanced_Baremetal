//Where are the LEDs connected
//-Pin ?  green led  = 0  | blue led = 1   | red led = 14
//-Port?  green led  = B  | blue led = E   | red led = B

//Push Button connected to PC13  -  Blue User Button

#include "stm32h7xx.h"

#define GPIOB_CLK_EN      (1U<<1) //  0000 0000 0000 0000 0000 0000 0000 0010
#define GPIOE_CLK_EN      (1U<<4) //  0000 0000 0000 0000 0000 0000 0001 0000

#define GPIOC_CLK_EN      (1U<<2)  //

#define USER_LED1_MODER   (1U<<0)  // Setting the bits to 1 will make these Output Pins
#define USER_LED2_MODER   (1U<<2)
#define USER_LED3_MODER   (1U<<28)

// Setting bits 27:26 of PORT C will make the Pin PC13 as input Pin

#define USER_LED1  (1U<<0)   //Green Led
#define USER_LED2  (1U<<1)   //Blue Led
#define USER_LED3  (1U<<14)  //Red Led

#define USER_BTN   (1U<<13)

int main(void)
{
	/* Enable GPIOB and GPIOE clocks */
	RCC->AHB4ENR |= GPIOB_CLK_EN | GPIOE_CLK_EN | GPIOC_CLK_EN;

	/* Configure PB0 and PB14 as outputs */
	GPIOB->MODER &= ~((3U << 0) | (3U << 28));
	GPIOB->MODER |= USER_LED1_MODER | USER_LED3_MODER;

	/* Configure PE1 as an output */
	GPIOE->MODER &= ~(3U << 2);
	GPIOE->MODER |= USER_LED2_MODER;

	GPIOC->MODER &= 0xF3FFFFFF;


	while(1)
	{
		/*Turn on all leds*/
		//GPIOB_OD_R |= USER_LED1 | USER_LED3;
		//GPIOE_OD_R |= USER_LED2;

		/* toggle*/
		//GPIOB->ODR ^= USER_LED1 | USER_LED3;
		//GPIOE->ODR ^= USER_LED2;
		//for(int i=0;i<10000000;i++){}

		// Turn ON LEDs if Button is Pressed
		if (GPIOC->IDR & USER_BTN){
			GPIOB->ODR |= USER_LED1 | USER_LED3;
			GPIOE->ODR |= USER_LED2;
		}
		else{
			GPIOB->ODR = 0x0;
			GPIOE->ODR = 0x0;
		}

	}

}













