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
#include "DS3231.h"
#include "UART.h"
#include "EEPROM.h"

/* private macros */
uint8_t next_addr = 0x02;
uint8_t alarm_number = 0;
uint8_t date_time[7];

/* private functions */

void save_timestamp(char* timestamp)
{
	uint8_t section = 0;
	char *ptr;
	char delimiter[] = ",";
	/* Restore last called address and increment by one */
	alarm_number = eeprom_read_byte((uint8_t*)0x01)+1; 
	next_addr = 0x02 + alarm_number* 7;

	printf("Number of saved timestamps %i",(int)alarm_number);

	/* Split string into time and date */
	ptr = strtok(timestamp, delimiter);

	while(ptr != NULL)
		{
			date_time[section]= atoi(ptr);
			section++;
			/* Start over again */
		 	ptr = strtok(NULL, delimiter);
		} 
		/* Save it to EEPROM */
	for(section = 0;section<7; section++)
		{
			eeprom_update_byte ((uint8_t*)next_addr, date_time[section]);
			/* Advance to next free address */
			next_addr++;
		}
	eeprom_update_byte((uint8_t*)0x01,alarm_number);
}

uint8_t* load_timestamp(uint8_t i)
{	static uint8_t timestamp[7];
	uint8_t section;
	uint8_t addr = 0x02+i*7;
	/* Load timestamp from EEPROM */
	for(section=0; section<7; section++)
		{
		timestamp[section] = eeprom_read_byte( (uint8_t *) addr);
		//printf("%i,",(int)timestamp[section]);
		addr++;
		}	
	return timestamp;
}

void clear_eeprom(void)
{ 
	uint8_t addr = 0x01;
	/* Call 0x01 for saved number of timestamps */
	uint8_t n = eeprom_read_byte((uint8_t *)0x01)+1;

for(addr = 0x01; addr <= (0x01+n*7); addr++)
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
