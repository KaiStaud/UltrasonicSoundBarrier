#include "Globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART.h" 
#include "Sonar.h"
#include "ADC.h"
#include "Buttons.h"

uint8_t temp = 0;


int main(void)
{
	uart_init();
	Buttons_init();
	sonar_init();
	ADC_init();	
	sei();

	while(1)
    {
	temp = get_temperature();
	send_pulse();
	_delay_ms(30);
	uart_tx_int(calc_distance(temp));
	uart_tx("\r\n");

	}
}

