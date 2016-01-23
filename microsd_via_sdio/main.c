/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

#include <string.h>
#include "stm32f4xx_hal.h"
#include "ff_gen_drv.h"
#include "ff.h"
#include "sd_diskio.h"
#include "config.h"
#include "led.h"
#include "log.h"

extern void error_handler(void);
FATFS fs;
char path[4];

static int
test(const char *filename, const char *content)
{
	FIL fp;	
	UINT retval;
	
	if (f_open(&fp, filename, FA_WRITE|FA_CREATE_ALWAYS) != FR_OK) {
		log_error("Could not open file %s", filename);
		led_on(LED_ORANGE);
		return (1);
	}
	
	
	if (f_write(&fp, content, strlen(content), &retval) != FR_OK) {
		log_error("Could not write to file %s, err=%d", filename, retval);
		f_close(&fp);
		led_on(LED_ORANGE);
		return (2);
	}
	
	f_close(&fp);
	led_on(LED_GREEN);
	log_info("Test ok, file %s has been created with new content", filename);
	
	return (0);
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

	if (FATFS_LinkDriver(&SD_Driver, path) == 0) {
                /* Mount drive */
		if (f_mount(&fs, (TCHAR const*)"", 1) == FR_OK) {                        
			log_info("Filesystem mounted");
			test("example.txt", "The Content, :)\n");
			f_mount(0, "", 1); // Unmount drive, don't forget this!
                } else {
			log_error("Could not mount filesystem");
			led_on(LED_RED);
		}
        } else {
		log_error("Could not initialize driver");
		led_on(LED_RED);
	}

        while (1); // hang on endless loop
}
