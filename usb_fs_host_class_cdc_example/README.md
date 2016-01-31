# Example of USB FS Host Class CDC

Little overview of what I did:
 * USB OTG interface is used
 * Debug logging via UART is ON
 * LEDs status
  * RED led on - USB unrecovered error occured (strange thing)
  * ORANGE led on - waiting for USB stack checking, enumrating, etc.
  * GREEN led on - USB is ready!
  * Blinking BLUE - sending and receving byte of data from connected USB Device class CDC (virtual COM-port)

## Board
STM32f401C-DISCO

## MCU
STM32F401VCT6

## Library
STM32Cube_FW_F4_V1.9.0

## Configuration

### LEDs:
 * GPIOs:
  * GREEN_LED -> PD12
  * ORANGE_LED -> PD13
  * RED_LED -> PD14
  * BLUE_LED -> PD15

### DEBUG
 * USART6 with GPIOs:
  * USART6_TX -> PC6
  * USART6_RX -> PC7 (unused) 

## Compiling and Burning (arm-none-eabi toolchain)
```
$ make && make flash
```
