#include "Globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART.h" 
#include "Sonar.h"
#include "ADC.h"
#include "Buttons.h"



int main(void)
{
	DDRB = (1<<5)|(1<<4);
	DDRC = 0xFF;
	DDRD = 0x00;
	uart_init();
	Buttons_init();
	sonar_init();
	ADC_init();	
	sei();
//	send_pulse();
//	_delay_ms(30);
//	uart_tx_int(calc_distance(20));
	while(1)
    {
		uart_tx_int(get_temperature());
	}
}
