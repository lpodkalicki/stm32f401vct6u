# -
# Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
# -

TARGET=main
STMDIR=lib

###################################################

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump
SE=arm-none-eabi-size
SF=st-flash

###################################################

STMSRCDIR = $(STMDIR)/Drivers/STM32F4xx_HAL_Driver/Src
STMSRCDIR += $(STMDIR)/Middlewares/ST/STM32_USB_Host_Library/Core/Src
STMSRCDIR += $(STMDIR)/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Src
vpath %.c $(STMSRCDIR)

INC_DIRS = $(STMDIR)/Drivers/STM32F4xx_HAL_Driver/Inc
INC_DIRS += $(STMDIR)/Drivers/CMSIS/Device/ST/STM32F4xx/Include
INC_DIRS += $(STMDIR)/Drivers/CMSIS/Include
INC_DIRS += $(STMDIR)/Middlewares/ST/STM32_USB_Host_Library/Core/Inc
INC_DIRS += $(STMDIR)/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc
INC_DIRS += .

INCLUDE = $(addprefix -I,$(INC_DIRS))

###################################################

CFLAGS  = -std=gnu99 -g -O2 -Wall -TSTM32F401VCTx_FLASH.ld
CFLAGS += -mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m4
CFLAGS += -fsingle-precision-constant -Wdouble-promotion
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS += -DUSE_STDPERIPH_DRIVER -DSTM32F401xC
CFLAGS += -DDEBUG

###################################################

SRCS =  main.c \
	stm32f4xx_it.c \
	system_stm32f4xx.c \
	startup_stm32f401xc.s \
	syscalls.c \
	config.c \
	led.c \
	log.c \
	usbh_conf.c
	
SRCS += stm32f4xx_hal.c \
	stm32f4xx_hal_rcc.c \
	stm32f4xx_hal_gpio.c \
	stm32f4xx_hal_cortex.c \
	stm32f4xx_hal_cortex.c \
	stm32f4xx_hal_uart.c \
	stm32f4xx_hal_dma.c \
	stm32f4xx_hal_hcd.c \
	stm32f4xx_ll_usb.c

SRCS += usbh_core.c \
	usbh_ctlreq.c \
	usbh_ioreq.c \
	usbh_pipes.c \
	usbh_cdc.c

###################################################

.PHONY: $(TARGET)

$(TARGET): $(TARGET).elf

$(TARGET).elf: $(SRCS)
	$(CC) $(INCLUDE) $(CFLAGS) $^ -o $@ 
	$(CP) -O ihex $(TARGET).elf $(TARGET).hex
	$(CP) -O binary $(TARGET).elf $(TARGET).bin

clean:
	rm -f *.o $(TARGET).elf $(TARGET).hex $(TARGET).bin

flash: 
	$(SF) write $(TARGET).bin 0x8000000
