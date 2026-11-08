/*
 * rcc.h
 *
 *  Created on: May 12, 2021
 *      Author: Israel
 */

#ifndef RCC_H_
#define RCC_H_

#include "stm32h7xx.h"
#include <stdint.h>


void set_ahb4_periph_clock(uint32_t periphs);
void set_ahb2_periph_clock(uint32_t perihs);
void set_apb1_periph_clock(uint32_t periphs);
void set_apb2_periph_clock(uint32_t perihs);


#endif /* RCC_H_ */
