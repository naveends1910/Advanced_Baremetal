//Where is the LED connected
//-Pin ?  green led  = 0  |  blue led = 7  |red led = 14
//-Port? green led   = B  | blue led = B   | red led = B

#define PERIPH_BASE       0x40000000UL
#define AHB1_OFFSET       0x00020000UL
#define AHB1PERIPH_BASE   PERIPH_BASE + AHB1_OFFSET
#define GPIOB_OFFSET   	  0x400UL
#define GPIOB_BASE 		  AHB1PERIPH_BASE + GPIOB_OFFSET

#define RCC_OFFSET		  0x3800UL //
#define RCC_BASE		  AHB1PERIPH_BASE + RCC_OFFSET
#define AHB1EN_R_OFFSET   0x30UL

#define RCC_AHB1EN_R      (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODER_OFFSET	  0x000UL
#define GPIOB_MODE_R       (*(volatile unsigned int *)(GPIOB_BASE + MODER_OFFSET))


#define ODR_OFFSET	      0x14UL
#define GPIOB_OD_R       (*(volatile unsigned int *)(GPIOB_BASE + ODR_OFFSET))


#define GPIOB_CLK_EN      (1U<<1) //  0000 0000 0000 0000 0000 0000 0000 0010

#define USER_LED1_MODER   (1U<<0)  //  0000 0000 0000 0000 0000 0000 0000 0001
#define USER_LED2_MODER   (1U<<14)
#define USER_LED3_MODER   (1U<<28)

#define USER_LED1  (1U<<0)   //Green Led
#define USER_LED2  (1U<<7)   //Blue Led
#define USER_LED3  (1U<<14)  //Red Led


int main(void)
{

	while(1)
	{


	}


}













