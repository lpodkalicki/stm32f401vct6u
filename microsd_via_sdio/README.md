# uSD (microsd) via SDIO interface

I have test this example with SDIO interface. I used 8GB cards in FAT32 format. In this example, default settings are in use, so:

 * SDIO interface
 * Card detect is OFF
 * Write protect is OFF
 * Debug logging via UART is ON
 * LEDs status
  * RED led on - could not init driver or could not mount filesystem
  * ORANGE led on - mount ok, but coud't open file or write to file (maybe you have enabled Write protect pin. Disable it for this example);
  * GREEN led on - mount ok and test ok - could open file and write some data

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
 * SDIO (4-bit):
  * 1. CD/DAT3 -> PC11
  * 2. CMD -> PD2 
  * 3. VSS1 -> GND 	
  * 4. VDD  -> 3.3V
  * 5. CLK -> PC12 	
  * 6. VSS2 -> GND
  * 7. DAT0 -> PC8
  * 8. DAT1 -> PC9
  * 9. DAT2 -> PC10  	
  

## Compiling and Burning (arm-none-eabi toolchain)
```
$ make && make flash
```
