#include <avr/io.h>
#include "app.h"

typedef struct 
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}HistoricData;

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
	uint8_t mode;
}AlarmData;

/*	HistoricData newtime;
	newtime.sec =dec2bcd(50);
	newtime.min =dec2bcd(59);
	newtime.hour= dec2bcd(20);
	newtime.weekDay = dec2bcd(0);
	newtime.date =dec2bcd(0);
	newtime.month =dec2bcd(0);
	newtime.year = dec2bcd(0);

	ds3231_SetDateTime(&newtime);
	ds3231_GetDateTime(&newtime);
*/

char c='a';

int main()
{
	app_init();
	
while(1)
{	

	/* Poll for new data */
	if (!(UCSR0A & (1<<RXC0)))
	{
		switch(c) 
		{
			/* Continue operation */
			case 'a': op_normal(); break;

			/* stop operation */
			case 'b' : op_stop(); break;

			/*Enter Power- Down mode */
			case 'c' : op_sleep(); break;

			/* Perform HIL Test */
			case 'd' : op_hil(); break;

			/* Mute System */
			case 'e': op_force(); break;

			/* Reset Module */
			case 'f' :app_reset();break;
		}	
		c= 'a';

	}
	/* Get new state */
	else
	    c = UDR0;
	
	
}

}
