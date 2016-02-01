/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

#include "stm32f4xx_hal.h"
#include "usbh_core.h"
#include "usbh_hid.h"
#include "config.h"
#include "led.h"
#include "log.h"


#define	STATE_READY		(0)
#define	STATE_ERROR		(1)
#define	STATE_IDLE		(2)


extern void error_handler(void);
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);
static void HID_UserProcess(USBH_HandleTypeDef *phost);
static void HID_Mouse_UserProcess(USBH_HandleTypeDef *phost);
static void HID_Keybd_UserProcess(USBH_HandleTypeDef *phost);


volatile uint8_t usb_state = STATE_IDLE;
volatile uint8_t ctx_state = STATE_IDLE;
USBH_HandleTypeDef hUSBHost;
HID_TypeTypeDef HIDType;
uint32_t ctx_counter = 0;

void
USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id)
{

	switch(id) {
	case HOST_USER_CONNECTION:
		log_info("USB connection!\n");
		led_on(LED_ORANGE);
		break;
	case HOST_USER_DISCONNECTION:
		usb_state = STATE_IDLE;
		ctx_state = STATE_IDLE;
		log_info("USB disconnection!");
		led_all_off();
		break;
	case HOST_USER_CLASS_ACTIVE:
		usb_state = STATE_READY;
		log_info("USB is ready!");
		led_all_off();
		led_on(LED_GREEN);
		break;
	case HOST_USER_UNRECOVERED_ERROR:
		usb_state = STATE_ERROR;
		log_error("USB unrecovered error occured");
		led_all_off();
                led_on(LED_RED);
		break;
	default:
		break;
	}
}

void
HID_UserProcess(USBH_HandleTypeDef *phost)
{

	switch (ctx_state) {
	case STATE_IDLE:
		HIDType = USBH_HID_GetDeviceType(phost);
		if (HIDType == HID_KEYBOARD) {
			log_info("KEYBOARD Detected");
			if (USBH_HID_KeybdInit(phost) != USBH_OK) {
				log_error("Keyboard initialization failed! :(");
				ctx_state = STATE_ERROR;
			}
		} else if (HIDType == HID_MOUSE) {
			log_info("MOUSE Detected");
			if (USBH_HID_MouseInit(phost) != USBH_OK) {
				log_error("Mouse initialization failed! :(");
				ctx_state = STATE_ERROR;
			}
		} else {
			log_warning("Unknown HID device");
		}
		ctx_state = STATE_READY;
		break;
	case STATE_READY:
		if (HIDType == HID_KEYBOARD) {
			HID_Keybd_UserProcess(phost);
		} else if (HIDType == HID_MOUSE) {
			HID_Mouse_UserProcess(phost);
		}
		break;
	case STATE_ERROR: break;
	default:
		log_info("Unknown state=0x%x", ctx_state);
		break;
	}
}

void
HID_Mouse_UserProcess(USBH_HandleTypeDef *phost)
{
	HID_MOUSE_Info_TypeDef *mouse_info;

	if (ctx_counter++ < 1000)
		return;

	mouse_info = USBH_HID_GetMouseInfo(phost);
	if (mouse_info != NULL) {
		led_on(LED_BLUE);
		log_info("Mouse: x=%d,y=%d, buttons=%d,%d,%d",
			(int)mouse_info->x,
			(int)mouse_info->y,
			(int)mouse_info->buttons[0],
			(int)mouse_info->buttons[1],
			(int)mouse_info->buttons[2]);
		led_off(LED_BLUE);
	}

	ctx_counter = 0;
}

void
HID_Keybd_UserProcess(USBH_HandleTypeDef *phost)
{
        HID_KEYBD_Info_TypeDef *keybd_info;
	uint8_t keybd_code;

	if (ctx_counter++ < 1000)
		return;

        keybd_info = USBH_HID_GetKeybdInfo(phost);
	if (keybd_info != NULL) {
		/* keybd_info:
		typedef struct {
			uint8_t state;
			uint8_t lctrl;
			uint8_t lshift;
			uint8_t lalt;
			uint8_t lgui;
			uint8_t rctrl;
			uint8_t rshift;
			uint8_t ralt;
			uint8_t rgui;
			uint8_t keys[6];
		} HID_KEYBD_Info_TypeDef
		*/
		led_on(LED_BLUE);
		keybd_code = USBH_HID_GetASCIICode(keybd_info);
		if (keybd_code != KEY_NONE) {
			log_info("Keybd: ASCII=0x%x, CHARACTER=%c", keybd_code, keybd_code);
		}
		led_off(LED_BLUE);
	}

	ctx_counter = 0;
}

void
USBH_HID_EventCallback(USBH_HandleTypeDef *phost)
{
	log_info("Event!");
}

int
main(void)
{

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
	USBH_RegisterClass(&hUSBHost, USBH_HID_CLASS);
	USBH_Start(&hUSBHost);

        while (1) {

		/* USB Host Background task */
		USBH_Process(&hUSBHost);

		if (usb_state == STATE_READY) {
			HID_UserProcess(&hUSBHost);
		}

	}
}
