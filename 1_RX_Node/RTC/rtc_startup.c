#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include "rtc_startup.h"
#include "rtc.h"
#include "EEPROM.h"

char *ptr;
char input[20];
uint8_t element= 0;
char delimiter[] = ",";
char i;

void init_time(void)
{
uint8_t now[6]; 
printf("Enter current time,end menue by typing 'z'\r\n");
string_to_int(now);
/* Set new time */
rtc_set_time_s(now[0],now[1] ,now[2]);
}

void init_alarms(void)
{
uint8_t alarms[6]={0,0,0,0,0,0};
printf("Enter your alarms,terminate by typing'z'\r\n");
/* Get the initial input */
string_to_int(alarms);
/* Call save timestamp */
save_timestamp(alarms[0],alarms[1],alarms[2],1);
save_timestamp(alarms[3],alarms[4],alarms[5],2);
/* Call transfer timestamp */
rtc_set_alarm_s(alarms[0],alarms[1],alarms[2],1);
rtc_set_alarm_s(alarms[3],alarms[4],alarms[5],2);
}

void string_to_int(uint8_t* time)
{
	while(i != 'z')
	{
		/* Wait for new chars */
		if(!(UCSR0A & (1<<RXC0)));
		
		else
		{
			i =UDR0;
			input[element] = i;
			element++;			
		}		
	}
	/* Terminate string with a zero */
	input[element-1]= 0;
	element=0;
	/* Split string at delimiter */
	ptr = strtok(input, delimiter);

	while(ptr != 0)
		{
			time[element]= atoi(ptr);
			element++;
			/* Start over again */
		 	ptr = strtok(0, delimiter);
		}
/* Clear buffers */
i= '0';
element = 0;
}
