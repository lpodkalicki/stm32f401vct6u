/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

#include "stm32f4xx_hal.h"
#include "usbh_core.h"
#include "usbh_cdc.h"
#include "config.h"
#include "led.h"
#include "log.h"

#define	RXTX_BUFF_SIZE	0x200
extern void error_handler(void);

USBH_HandleTypeDef hUSBHost;
volatile uint8_t usb_host_isconnection = 0;
volatile uint8_t usb_host_isready = 0;
uint8_t CDC_TX_Buffer[RXTX_BUFF_SIZE];
uint8_t CDC_RX_Buffer[RXTX_BUFF_SIZE];


static void
USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id)
{

	switch(id) {
	case HOST_USER_SELECT_CONFIGURATION:
		log_info("USB unrecovered error occured");
		break;
	case HOST_USER_CONNECTION:
		usb_host_isconnection = 1;
		log_info("USB connection!\n");
		led_on(LED_ORANGE);
		break;
	case HOST_USER_DISCONNECTION:
		usb_host_isready = usb_host_isconnection = 0;
		log_info("USB disconnection!");
		led_all_off();
		break;
	case HOST_USER_CLASS_ACTIVE:
		usb_host_isready = 1;
		log_info("USB is ready!");
		led_all_off();
		led_on(LED_GREEN);
		break;
	case HOST_USER_UNRECOVERED_ERROR:
		usb_host_isready = 0;
		log_error("USB unrecovered error occured");
		led_all_off();
                led_on(LED_RED);
		break;
	default:
		break;
	}
}

int
main(void)
{
	CDC_LineCodingTypeDef FrameFormat;
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

	/* Configure and start USB HOST CDC */
	USBH_Init(&hUSBHost, USBH_UserProcess, 0);
	USBH_RegisterClass(&hUSBHost, USBH_CDC_CLASS);
	FrameFormat.b.dwDTERate = 9600;
	FrameFormat.b.bCharFormat = 0;
	FrameFormat.b.bDataBits = 8;
	FrameFormat.b.bParityType = 0;
	USBH_CDC_SetLineCoding(&hUSBHost, &FrameFormat);
	USBH_Start(&hUSBHost);

        while (1) {

		/* USB Host Background task */
		USBH_Process(&hUSBHost);

		if (usb_host_isready) {
			led_on(LED_BLUE);
			CDC_TX_Buffer[0] = 0x05;
			CDC_TX_Buffer[1] = 0;
			USBH_CDC_Transmit(&hUSBHost, CDC_TX_Buffer, 1);
			USBH_CDC_Receive(&hUSBHost, CDC_RX_Buffer, 1);
			log_info("out=%x", CDC_RX_Buffer[0]);
			led_off(LED_BLUE);
			HAL_Delay(2000);
		} else if (usb_host_isconnection) {
			if (cnt++ >= 5000) {
				log_warning("Device attached but not responding, reseting...");
				HAL_NVIC_SystemReset();
			}
			HAL_Delay(1);
			led_toggle(LED_ORANGE);
		}

	}
}
