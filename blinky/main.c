/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

#include "stm32f4xx_hal.h"
#include "config.h"
#include "led.h"

extern void error_handler(void);
#define DELAY   (100)

int
main(void)
{

	HAL_Init();	
        SystemClock_Config();
        RCC_Config();        
        GPIO_Config();      

        if (SysTick_Config(SystemCoreClock / 1000)) {
                error_handler();
        }

        while (1) {
                led_toggle(LED_GREEN);
                HAL_Delay(DELAY);
                led_toggle(LED_GREEN);
                led_toggle(LED_ORANGE);
                HAL_Delay(DELAY);
                led_toggle(LED_ORANGE);
                led_toggle(LED_RED);
                HAL_Delay(DELAY);
                led_toggle(LED_RED);
                led_toggle(LED_BLUE);
                HAL_Delay(DELAY);
                led_toggle(LED_BLUE);
	}	
}

