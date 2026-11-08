
#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>
#include "stm32h7xx.h"



void pa3_adc1_init(void);
uint32_t adc_get_data(void);


#endif /* ADC_H_ */
