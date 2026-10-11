#include "rcc.h"


void set_ahb4_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->AHB4ENR,periphs);
}


void set_ahb2_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->AHB2ENR,periphs);
}

void set_apb1_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->APB1LENR ,periphs);
}

void set_apb2_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->APB2ENR,periphs);
}
