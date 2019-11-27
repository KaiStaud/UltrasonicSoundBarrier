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

void load_timestamps(uint8_t* alarms)
{	
	uint8_t address=0x07;
	uint8_t i;
	/* Read back eeprom */
	for(i=0;i<5;i++)
	{
	alarms[i]= eeprom_read_byte((uint8_t*)address);
	address++;
	}

}

void clear_eeprom(void)
{	uint8_t addr; 
	for(addr = 0x00; addr <= 0x0B; addr++);
	eeprom_update_byte ((uint8_t*)addr, 0xFF); 
}

void return_eeprom(void)
{
	uint8_t saved_alarms[5];
	load_timestamps(&saved_alarms);
	printf("Alarm 1: %i:%i:%i\n",saved_alarms[0],saved_alarms[1],saved_alarms[2]);
	printf("Alarm 2: %i:%i",saved_alarms[3],saved_alarms[4]);
}

void transfer_timestamp(void)
{
	uint8_t alarms2transfer[5];
	/* Call timestamp */
	load_timestamps(&alarms2transfer);
	/* Send it over to RTC */
	rtc_set_alarm_s(alarms2transfer[0],alarms2transfer[1],alarms2transfer[2],1);
	rtc_set_alarm_s(alarms2transfer[3],alarms2transfer[4],alarms2transfer[5],2);

}
