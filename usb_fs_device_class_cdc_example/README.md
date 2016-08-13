#  Parrot - example of USB FS Device Class CDC

Project overview:
 * USB is configured as Full-Speed Device Class CDC (/dev/ttyACMx)
 * Debug logging via UART is ON
 * LEDs status
  * BLUE led on - example is ready
  * Blinking GREEN - when sending / receiving data

## Board
STM32f401C-DISCO

## MCU
STM32F401VCT6

## Library
STM32Cube_FW_F4_V1.9.0

## Configuration

### LEDs:
 * GPIOs of port D:
  * GREEN_LED -> PD12
  * ORANGE_LED -> PD13
  * RED_LED -> PD14
  * BLUE_LED -> PD15

### SERIAL (DEBUG)
 * USART6 with GPIOs:
  * USART6_TX -> PC6
  * USART6_RX -> PC7 (unused) 

### Tools
 * comport.py - helper python script to easy serial communication via Virtual Com Port (USB Device CDC)

## Compiling and Burning (arm-none-eabi toolchain)
```
$ make && make flash
```
