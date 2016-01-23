# Blinky
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

## Compiling and Burning (arm-none-eabi toolchain)
```
$ make && make flash
```

