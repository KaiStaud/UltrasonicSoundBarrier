###############################################################################
# Makefile for the project RN_V0
###############################################################################

## General Flags
PROJECT = RN_V0
MCU = atmega328p
TARGET = RN_V0.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wl,-u,vfprintf
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=RN_V0.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Libraries
LIBS = -lso 

## Objects that must be built in order to link
OBJECTS = main.o UART.o Sonar.o ADC.o EEPROM.o Wakeups.o App.o twi.o twi-lowlevel.o rtc.o rtc_startup.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) RN_V0.hex RN_V0.eep RN_V0.lss size

## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

UART.o: ../UART.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Sonar.o: ../Sonar.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ADC.o: ../ADC.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

EEPROM.o: ../EEPROM.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Wakeups.o: ../Wakeups.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

App.o: ../App.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

twi.o: ../twi.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

twi-lowlevel.o: ../twi-lowlevel.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

rtc.o: ../rtc.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

rtc_startup.o: ../rtc_startup.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) RN_V0.elf dep/* RN_V0.hex RN_V0.eep RN_V0.lss RN_V0.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

