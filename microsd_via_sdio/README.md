# Debug logging via UART

I have test this example with SDIO interface. I used 8GB cards in FAT32 format. In this example, default settings are in use, so:

 * SDIO interface
 * Card detect is OFF
 * Write protect is OFF
 * Debug logging via UART is ON
 * LEDs status
  * RED led on - could not mount filesystem
  * ORANGE led on - mount ok, but coud't open file (maybe you have enabled Write protect pin. Disable it for this example);
  * BLUE led on - mount ok, could open file and write some data
  * GREEN blinking - just blinking GREEN led.

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

### DEBUG
 * USART6:
  * USART6_TX -> PC6
  * USART6_RX -> PC7 (unused) 

### uSD
 * SDIO (4bits):
  * 
 


## Compiling and Burning (arm-none-eabi toolchain)
```
$ make && make flash
```
