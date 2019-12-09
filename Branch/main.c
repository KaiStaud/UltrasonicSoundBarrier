#include "Globals.h"
#include "util/delay.h"
#include <avr/io.h>
#include "App.h"
#include "UART.h"
#include <stdio.h> 

extern char d;

int main(void)
{
char c = 'a'; 
	app_init();
	_delay_ms(500);  
	//printf("Hello from AVR STUDIO 4.19");
    while(1)
	{
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

			/* Can't be reached : Button Input */
			case 'd' : op_button(); break;

			/* Mute System */
			case 'e': op_mute(); break;

			/* Reset Module */
			case 'f' :app_reset();break;

			case 'g' :app_config();break;
		
			default: break;
		}
		c= 'a';
		//printf("D Value = %c\n",d);
		/* Combinatory Logic: assign next state depending on interrupt and current state */
		c = d;
	} 
 
    else
		c = UDR0;
	}
}
