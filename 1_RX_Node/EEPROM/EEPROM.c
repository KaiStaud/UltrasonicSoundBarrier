/* official c headers */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* avr libc includes */
#include <avr/io.h>
#include <avr/eeprom.h>

/* private includes */
#include "Globals.h"
#include "UART.h"
#include "EEPROM.h"

/* private macros */

/* private functions */

void save_timestamp(uint8_t h, uint8_t m, uint8_t s, uint8_t alarm_num)
{
	/* Save it to EEPROM */
	if(alarm_num == 1)
	{
	eeprom_update_byte((uint8_t*)0x07,h);
	eeprom_update_byte((uint8_t*)0x08,m);
	eeprom_update_byte((uint8_t*)0x09,s);
	}
	else
	{
	eeprom_update_byte((uint8_t*)0x0A,h);
	eeprom_update_byte((uint8_t*)0x0B,m);
	}
}

uint8_t* load_timestamp(uint8_t alarm_num)
{	static uint8_t timestamp[3];
	uint8_t section;
	uint8_t addr = 0x07+alarm_num*3;
	/* Load timestamp from EEPROM */
	while(section<2)
	{
	timestamp[section] = eeprom_read_byte((uint8_t*)addr);
	section++;
	addr++;
	}

	return timestamp;
}

void clear_eeprom(void)
{uint8_t addr; 
	for(addr = 0x00; addr <= 0x0B; addr++);
	eeprom_update_byte ((uint8_t*)addr, 0xFF); 
}

void return_eeprom(void)
{
	uint8_t* timestamp;
	/* Get the number of stored alarms */
	uint8_t count = eeprom_read_byte((uint8_t *)0x01)+1;
	uint8_t i=0;
	uint8_t section =0;
	printf("Rückgabe von %i Timestamps\r\n",count);
/* Count up on on alarms */
	while(i<count)
	{
		timestamp = load_timestamp(i);

		for(section=0;section<6;section++)
				printf("%i,",timestamp[section]);
		printf("%iz",timestamp[section++]);
		i++;
	}
}

void transfer_timestamp(void)
{
	/* Call timestamp */

	/*Convert element into bcd format */

	/* Send it over to RTC */
}
