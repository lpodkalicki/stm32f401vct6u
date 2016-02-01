/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lukasz@podkalicki.com>
 */

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "config.h"
#include "led.h"

extern void error_handler(void);
UART_HandleTypeDef UART_DBG_Handle;

void
SystemClock_Config(void)
{

	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
	clocked below the maximum system frequency, to update the voltage scaling value
	regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/* Enable HSE Oscillator and activate PLL with HSI as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		error_handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		error_handler();
	}
}

void
RCC_Config(void)
{
	/* -- Enable GPIO clock for LED pins -- */
	LED_GPIO_CLK_ENABLE();

        /* -- Enable GPIO clocks for USART/DEBUG -- */
        USART_DBG_RX_GPIO_CLK_ENABLE();
        USART_DBG_TX_GPIO_CLK_ENABLE();
        USART_DBG_CLK_ENABLE();
}

void
GPIO_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	/* -- Configure the GPIO of LED pins -- */
	GPIO_InitStruct.Pin = LED_GPIO_PIN1|LED_GPIO_PIN2|LED_GPIO_PIN3|LED_GPIO_PIN4;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

	/* -- Configure the GPIO pins for USART/DEBUG -- */
        GPIO_InitStruct.Pin = USART_DBG_TX_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
        GPIO_InitStruct.Alternate = USART_DBG_TX_AF;
        HAL_GPIO_Init(USART_DBG_TX_GPIO_PORT, &GPIO_InitStruct);
        GPIO_InitStruct.Pin = USART_DBG_RX_PIN;
        GPIO_InitStruct.Alternate = USART_DBG_RX_AF;
        HAL_GPIO_Init(USART_DBG_RX_GPIO_PORT, &GPIO_InitStruct);
}

void
USART_Config(void)
{

        /* -- Configure USART/DEBUG interface -- */
        UART_DBG_Handle.Instance = USART_DBG;
        UART_DBG_Handle.Init.BaudRate = 115200;
        UART_DBG_Handle.Init.WordLength = UART_WORDLENGTH_8B;
        UART_DBG_Handle.Init.StopBits = UART_STOPBITS_1;
        UART_DBG_Handle.Init.Parity = UART_PARITY_NONE;
        UART_DBG_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        UART_DBG_Handle.Init.Mode = UART_MODE_TX;
        UART_DBG_Handle.Init.OverSampling = UART_OVERSAMPLING_16;

        if (HAL_UART_Init(&UART_DBG_Handle) != HAL_OK) {
                error_handler();
        }
}
