/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

#ifndef _PROJECT_LED_H_
#define _PROJECT_LED_H_

#include "stm32f4xx_hal_gpio.h"

#define	LED_NUM			(4)
#define	LED_GPIO_PORT		GPIOD
#define	LED1_PIN		GPIO_PIN_12
#define	LED2_PIN		GPIO_PIN_13
#define	LED3_PIN		GPIO_PIN_14
#define	LED4_PIN		GPIO_PIN_15

typedef enum {
	LED1, // Green
	LED2, // Orange
	LED3, // Red
	LED4  // Blue
} led_t;

#define	LED_GREEN		LED1
#define	LED_ORANGE		LED2
#define	LED_RED			LED3
#define	LED_BLUE		LED4

void led_init(led_t led);
void led_on(led_t led);
void led_off(led_t led);
void led_toggle(led_t led);
void led_all_on();
void led_all_off();

#endif	/* !_PROJECT_LED_H_ */
