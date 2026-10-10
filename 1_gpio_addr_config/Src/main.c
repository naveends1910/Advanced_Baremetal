//Where are the LEDs connected
//-Pin ?  green led  = 0  | blue led = 1   | red led = 14
//-Port?  green led  = B  | blue led = E   | red led = B

// All GPIO ports are connected to AHB4

#define PERIPH_BASE       0x40000000UL
#define AHB4_OFFSET       0x18000000UL		// AHB4 Starts at 0x58000000UL
#define AHB4PERIPH_BASE   PERIPH_BASE + AHB4_OFFSET
#define GPIOB_OFFSET   	  0x20400UL
#define GPIOE_OFFSET   	  0x21000UL
#define GPIOB_BASE 		  AHB4PERIPH_BASE + GPIOB_OFFSET
#define GPIOE_BASE 		  AHB4PERIPH_BASE + GPIOE_OFFSET

#define RCC_OFFSET		  0x24400UL //
#define RCC_BASE		  AHB4PERIPH_BASE + RCC_OFFSET
#define AHB4EN_R_OFFSET   0xE0

#define RCC_AHB4EN_R      (*(volatile unsigned int *)(RCC_BASE + AHB4EN_R_OFFSET))  //Typecast and dereference the pojnter to be used as a register

#define MODER_OFFSET	  0x000UL
#define GPIOB_MODE_R       (*(volatile unsigned int *)(GPIOB_BASE + MODER_OFFSET))
#define GPIOE_MODE_R       (*(volatile unsigned int *)(GPIOE_BASE + MODER_OFFSET))


#define ODR_OFFSET	      0x14UL		//Output data register to which GPIO Output value to be written
#define GPIOB_OD_R       (*(volatile unsigned int *)(GPIOB_BASE + ODR_OFFSET))
#define GPIOE_OD_R       (*(volatile unsigned int *)(GPIOE_BASE + ODR_OFFSET))


#define GPIOB_CLK_EN      (1U<<1) //  0000 0000 0000 0000 0000 0000 0000 0010
#define GPIOE_CLK_EN      (1U<<4) //  0000 0000 0000 0000 0000 0000 0001 0000

#define USER_LED1_MODER   (1U<<0)  // Setting the bits to 1 will make these Output Pins
#define USER_LED2_MODER   (1U<<2)
#define USER_LED3_MODER   (1U<<28)

#define USER_LED1  (1U<<0)   //Green Led
#define USER_LED2  (1U<<1)   //Blue Led
#define USER_LED3  (1U<<14)  //Red Led


int main(void)
{
	/* Enable GPIOB and GPIOE clocks */
	RCC_AHB4EN_R |= GPIOB_CLK_EN | GPIOE_CLK_EN;

	/* Configure PB0 and PB14 as outputs */
	GPIOB_MODE_R &= ~((3U << 0) | (3U << 28));
	GPIOB_MODE_R |= USER_LED1_MODER | USER_LED3_MODER;

	/* Configure PE1 as an output */
	GPIOE_MODE_R &= ~(3U << 2);
	GPIOE_MODE_R |= USER_LED2_MODER;

	while(1)
	{
		/*Turn on all leds*/
		//GPIOB_OD_R |= USER_LED1 | USER_LED3;
		//GPIOE_OD_R |= USER_LED2;

		/* toggle*/
		GPIOB_OD_R ^= USER_LED1 | USER_LED3;
		GPIOE_OD_R ^= USER_LED2;
		for(int i=0;i<10000000;i++){}


	}

}













