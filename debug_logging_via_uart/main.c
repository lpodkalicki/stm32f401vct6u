/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

#include "stm32f4xx_hal.h"
#include "config.h"
#include "led.h"
#include "log.h"

extern void error_handler(void);

int
main(void)
{
	uint32_t cnt = 0;
	HAL_Init();
        SystemClock_Config();
        RCC_Config();
        GPIO_Config();
	USART_Config();

        if (SysTick_Config(SystemCoreClock / 1000)) {
                error_handler();
        }

        log_init(LOGLEVEL_INFO);
        log_info("PROJECT STERTED");

        while (1) {
                led_toggle(LED_GREEN);
                HAL_Delay(1000);
		log_info("cnt=%u", cnt++);
	}
}

