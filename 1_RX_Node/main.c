#include "Globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART.h" 
#include "Sonar.h"
#include "Buttons.h"

int main(void)
{
	 DDRB = (1<<5)|(1<<4);
	 DDRC = 0xFF;
	 DDRD = 0x00;
	 uart_init();
	 Buttons_init();
	 sonar_init();	

	 sei();
	
	/* Testsignal on Port C0 */
	_delay_ms(500);   
	PORTC ^= 0xFF;
	_delay_ms(500);
	PORTC ^= 0xFF;

	while(1)
    {
	
	}
}
