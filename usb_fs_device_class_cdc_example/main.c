/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

#include "stm32f4xx_hal.h"
#include "config.h"
#include "led.h"
#include "log.h"
#include "usbd_cdc.h"
#include "usbd_desc.h"
#include "usbd_cdc_if.h"


extern void error_handler(void);

/* Variables used for USB */
extern USBD_HandleTypeDef  hUSBDDevice;

int
main(void)
{
	uint32_t retval;
	uint8_t data[32];
	
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

        
        /* Init Device Library */
	USBD_Init(&hUSBDDevice, &CDC_Desc, 0);
	
	/* Add Supported Class */
	USBD_RegisterClass(&hUSBDDevice, USBD_CDC_CLASS);
	USBD_CDC_RegisterInterface(&hUSBDDevice, &USBD_CDC_fops);
	
	/* Start Device Process */
	USBD_Start(&hUSBDDevice);
	
	led_on(LED_BLUE);

        while (1) {
        
		while((retval = CDC_IntfReceive(data, 16)) > 0) {
			led_on(LED_GREEN);			
			if (retval > 0) {
				data[retval] = 0;
				log_info("data(%u)=%s", retval, data);
				CDC_IntfTransmit(data, retval);
			}
			led_off(LED_GREEN);
		}
		
		HAL_Delay(10);
	}
}

