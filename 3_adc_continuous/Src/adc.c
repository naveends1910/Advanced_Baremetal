//  ADC12_INP15 is on PA3 pin of H7 MCU of Nucleo Board. It is connected to A0 of CN9 connector
//  We are enabling ADC1, channel 15 connected to Pin PA3 of the MCU.
//  Port A is connected to AHB4 bus and ADC1 is connected to AHB1 Bus.

#include "adc.h"

#define		GPIOAEN			(1U<<0)
#define		ADC1_CLKEN		(1U<<5)
#define		ADC1EN		    (1U<<0)
#define		ADC1RDY		    (1U<<0)
#define		CFG_CONT		(1U<<13)
#define		SEQ_LEN_1		0
#define		CH15_RANK1		(0xF<<6)
#define		ADSTART		    (1U<<2)
#define		ISR_EOC			(1U<<2)
#define		CKMODE   		(3U<<16)
#define		CKMODE_HCLK_DIV4 (3U<<16)	/* adc_sclk / 4 = 64 MHz / 4 = 16 MHz */

#define		BOOST_01		(1U<<8)
#define		PCSEL_CH15		(1U<<15)
#define		ADCALLIN		(1U<<16)
#define		ADVREGEN		(1U<<28)
#define		DEEPPWD			(1U<<29)
#define		ADCAL			(1U<<31)

static void short_delay(void)
{
	/* > 10 us at 64 MHz, for the ADC voltage regulator start-up */
	for (volatile uint32_t i = 0; i < 2000; i++) {}
}


void pa3_adc1_init(void){

	/*Enable clock access to GPIOA*/
	RCC->AHB4ENR |= GPIOAEN;

	/*Set PA3 mode to analog mode*/
	GPIOA->MODER |=(1U<<6);
	GPIOA->MODER |=(1U<<7);

	/*Enable clock access to the ADC module*/
	RCC->AHB1ENR |=ADC1_CLKEN;

	/*Select ADC kernel clock = AHB clock / 4 (synchronous).
	  Default (CKMODE=00) uses RCC adc_ker_ck = pll2_p_ck, and PLL2 is off after reset.
	  An additional divider factor of 2 is applied to the clock delivered to the analog ADC block. So, 64/4/2 = 8 MHz*/
	ADC12_COMMON->CCR &= ~CKMODE;
	ADC12_COMMON->CCR |=  CKMODE_HCLK_DIV4;

	/*Exit deep power-down and enable the internal voltage regulator*/
	ADC1->CR &= ~DEEPPWD;
	ADC1->CR |=  ADVREGEN;
	short_delay();		// Let voltage regulator stabilize

	/*Boost setting for the ADC clock range.  Set BOOST bits to 0b01 for clock range 6.25 MHz to 12.5 MHz. Clock to ADC is 8 MHz*/
	ADC1->CR |= BOOST_01;

	/*Calibrate (ADEN must be 0): single-ended, with linearity calibration*/
	ADC1->CR |= ADCALLIN;
	ADC1->CR |= ADCAL;
	while (ADC1->CR & ADCAL) {}

	/*Set conversion to continuous*/
	ADC1->CFGR |=CFG_CONT;

	/*Set sequencer length to 1   only 1 channel to be sampled*/
	ADC1->SQR1 = SEQ_LEN_1;

	/*Set adc channel 15. Write Bits 10:6 of ADC1->SQR1 with value 15, 0b01111. So, ADC1_CH15 is first in the sequence of sampling.*/
	ADC1->SQR1 |= CH15_RANK1;

	/*H7 only: preselect channel 15, otherwise its input switch stays disconnected from PA3*/
	ADC1->PCSEL_RES0 |= PCSEL_CH15;

	/*Sampling time for channel 15: SMP15[2:0] at bits 17:15 of SMPR2, 011 = 64.5 cycles*/
	ADC1->SMPR2 &= ~(7U << 15);
	ADC1->SMPR2 |=  (3U << 15);


	/*Enable the ADC module*/
	ADC1->CR |=ADC1EN;

	/* Wait until ADC is ready */
	while (!(ADC1->ISR & ADC1RDY)) {}

	/*Start conversion*/
	ADC1->CR |= ADSTART;

}


uint32_t adc_get_data(void)
{
	/*Wait for End-of-Conversion flag*/
	while(!(ADC1->ISR & ISR_EOC)){}

	ADC1->ISR = (1U << 4);   /* clear OVR flag (write-1-to-clear) */

	/*Read results*/
	return (ADC1->DR);
}
