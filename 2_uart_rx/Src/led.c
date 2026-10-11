#include  "led.h"
#include "stm32h7xx.h"

void user_leds_init(void)
{
	/* Enable GPIOB and GPIOE clocks */
	RCC->AHB4ENR |= GPIOB_CLK_EN | GPIOE_CLK_EN;

	/* Configure PB0 and PB14 as outputs */
	GPIOB->MODER &= ~((3U << 0) | (3U << 28));
	GPIOB->MODER |= USER_LED1_MODER | USER_LED3_MODER;

	/* Configure PE1 as an output */
	GPIOE->MODER &= ~(3U << 2);
	GPIOE->MODER |= USER_LED2_MODER;

}


void all_leds_on(void)
{
	GPIOB->ODR |= USER_LED1 | USER_LED3;
	GPIOE->ODR |= USER_LED2;
}


void all_leds_off(void)
{
    GPIOB->BSRR = (USER_LED1 | USER_LED3) << 16;
    GPIOE->BSRR = USER_LED2 << 16;

	//GPIOB->ODR &= ~(USER_LED1 | USER_LED3);		//SOmething is not letting this Read Modify Write to work. But BSRR works.
	//GPIOE->ODR &= ~USER_LED2;
}


void all_leds_toggle(void)
{
	GPIOB->ODR ^= USER_LED1 | USER_LED3;
	GPIOE->ODR ^= USER_LED2;
	//for(int i=0;i<100000;i++){}
}

