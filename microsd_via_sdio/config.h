/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

#ifndef _EXAMPLE_CONFIG_H_
#define _EXAMPLE_CONFIG_H_

#include "stm32f4xx_hal_uart.h"

/* -- DEBUG USART -- */
#define USART_DBG                       USART6
#define USART_DBG_CLK_ENABLE()          __HAL_RCC_USART6_CLK_ENABLE()
#define USART_DBG_RX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()
#define USART_DBG_TX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()
#define USART_DBG_FORCE_RESET()         __HAL_RCC_USART6_FORCE_RESET()
#define USART_DBG_RELEASE_RESET()       __HAL_RCC_USART6_RELEASE_RESET()
#define USART_DBG_TX_PIN                GPIO_PIN_6
#define USART_DBG_TX_GPIO_PORT          GPIOC
#define USART_DBG_TX_AF                 GPIO_AF8_USART6
#define USART_DBG_RX_PIN                GPIO_PIN_7
#define USART_DBG_RX_GPIO_PORT          GPIOC
#define USART_DBG_RX_AF                 GPIO_AF8_USART6

void SystemClock_Config(void);
void RCC_Config(void);
void GPIO_Config(void);
void USART_Config(void);

#endif	/* !_PROJECT_CONFIG_H_ */
