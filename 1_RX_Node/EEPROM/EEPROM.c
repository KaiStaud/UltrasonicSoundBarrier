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
//uint8_t section = 0;


/* private functions */

void save_timestamp(char* timestamp)
{
uint8_t section = 0;
char *ptr;
char delimiter[] = ",";

	/* Split string into time and date */
	ptr = strtok(timestamp, delimiter);

	while(ptr != NULL)
		{
			date_time[section]= atoi(ptr);
			//uart_tx_int(date_time[section]);
			//uart_tx("\r\n");
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
	alarm_number++;

}

void load_timestamp(uint8_t i)
{
	uint8_t section;
	uint8_t addr = 0x02+i*7;
	/* Load timestamp from EEPROM */
	for(section=0; section<7; section++)
		{
		uart_tx_int(eeprom_read_byte( (uint8_t *) addr));
		addr++;
		}
	/* Update Alarm on RTC */

}

void clear_eeprom(void)
{
uint8_t addr = 0x01;
/* Call 0x01 for saved number of timestamps */
uint8_t n = eeprom_read_byte((uint8_t *)0x01)+1;

for(addr = 0x01; addr <= (0x01+n*7); addr++)
	eeprom_update_byte ((uint8_t*)addr, 0xFF);
 
}
