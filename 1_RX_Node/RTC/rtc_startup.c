#include "rtc_startup.h"
#include <avr/io.h>
#include <stdio.h>
#include <string.h>

uint8_t section = 0;
char *ptr;
char input[20];
uint8_t index= 0;
char delimiter = 'a';
char time[];
char i;

uint8_t* init_time(void)
{
printf("Enter current time,end menue by typing 'z'\r\n");

/* If end character is send close configuration */
while(i != 'z')
	{
		/* Wait for new chars */
		if(!(UCSR0A & (1<<RXC0)));
		
		else
		{
			i =UDR0;
			input[index] = i;
			index++;			
		}		
	}
	input[index-1]= 0;

/* Spliit string at delimiter */
	ptr = strtok(time, delimiter);

	while(ptr != NULL)
		{
			time[section]= atoi(ptr);
			section++;
			/* Start over again */
		 	ptr = strtok(NULL, delimiter);
		} 
/* Return struct to init function */

}

uint8_t* init_alarms(void)
{
/* Get the initial input */

/* Call save timestamp */

/* Call transfer timestamp */

}
