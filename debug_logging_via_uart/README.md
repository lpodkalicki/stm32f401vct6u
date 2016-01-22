## Board
STM32f401C-DISCO

## MCU
STM32F401VCT6

## Project
Debug loggin via UART

## Configuration
### DEBUG
 * USART6 with GPIOs:
  * USART6_TX -> PC6
  * USART6_RX -> PC7 (unused) 

## Compiling and Burning (arm-none-eabi toolchain)

```
$ make && make flash
```
