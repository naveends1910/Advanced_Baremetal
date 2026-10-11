/*
 * led.h
 *
 *  Created on: May 12, 2021
 *      Author: Israel
 */

#ifndef LED_H_
#define LED_H_

#include <stdint.h>

#define GPIOB_CLK_EN      (1U<<1) //  0000 0000 0000 0000 0000 0000 0000 0010
#define GPIOE_CLK_EN      (1U<<4) //  0000 0000 0000 0000 0000 0000 0001 0000

#define USER_LED1_MODER   (1U<<0)  // Setting the bits to 1 will make these Output Pins
#define USER_LED2_MODER   (1U<<2)
#define USER_LED3_MODER   (1U<<28)

#define USER_LED1  (1U<<0)   //Green Led
#define USER_LED2  (1U<<1)   //Blue Led
#define USER_LED3  (1U<<14)  //Red Led


#define GREEN_LED	USER_LED1
#define BLUE_LED	USER_LED2
#define RED_LED		USER_LED3


typedef uint32_t ledType;

void user_leds_init(void);
void all_leds_on(void);
void all_leds_off(void);
void all_leds_toggle(void);
void led_toggle(ledType led);
void led_on(ledType led);
void led_off(ledType led);


#endif /* LED_H_ */
