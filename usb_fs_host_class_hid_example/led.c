/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

#include "stm32f4xx_hal_conf.h"
#include "led.h"

const uint16_t led_gpio_pins[LED_NUM] = {
	LED_GPIO_PIN1,
	LED_GPIO_PIN2,
	LED_GPIO_PIN3,
	LED_GPIO_PIN4
};

void
led_on(led_t led)
{

	HAL_GPIO_WritePin(LED_GPIO_PORT, led_gpio_pins[led], GPIO_PIN_SET);
}

void
led_off(led_t led)
{

	HAL_GPIO_WritePin(LED_GPIO_PORT, led_gpio_pins[led], GPIO_PIN_RESET);
}

void
led_toggle(led_t led)
{

	HAL_GPIO_TogglePin(LED_GPIO_PORT, led_gpio_pins[led]);
}

void
led_all_on()
{

	led_on(LED1);
	led_on(LED2);
	led_on(LED3);
	led_on(LED4);
}

void
led_all_off()
{

	led_off(LED1);
	led_off(LED2);
	led_off(LED3);
	led_off(LED4);
}
