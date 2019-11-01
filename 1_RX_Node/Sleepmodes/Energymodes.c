#include <avr/io.h>
#include <avr/sleep.h>
#include "Globals.h"
#include "Energymodes.h"

char modes[7] ={'a','b','c','d','e','f','g'};
void Change_PowerMode(char c)
{
 int mode_index =0;
	
	PORTB ^= (1<<3)|(1<<4);
	PORTD ^= (1<<5)|(1<<6);
	uart_tx(c);
	switch(c)
	{
	/* Run State */
	case 'a':PORTD |= (1<<5);break;

	/* Stop CPU */ 
	case 'b': break;

	/* Enter Sleep Mode */
	case 'c': 
	/* Set All Pins to Inputs */ 
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
		
	DDRB |= 0x00;
	DDRC |= 0x00;
	DDRB |= 0x00;
	/* Disable the ADC */	
	ADCSRA ^=(1<<7);

	/* Disable BOD */
	MCUCR |=(3<<5); //Set BODS and BODSE
	MCUCR = (MCUCR & ~(1<<5))|(1<<6);

	/* Enter Power Down Mode */
	/*
	SMCR |=(1<<2) power down mode
	SMCR |= 1 enable sleep
	*/
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  	sleep_enable();  
  	sleep_mode(); 
	/* Leave Sleep Mode */
	sleep_disable();   
	DDRB  = (1<<LED_3_PIN)|(1<<LED_4_PIN);
	DDRD = (1<<LED_1_PIN)|(1<<LED_2_PIN);
	
	
	PORTB  = (1<<LED_3_PIN);
	PORTD = (1<<LED_1_PIN)|(1<<LED_2_PIN);
	break;

	/* Perform HIL Test */
	case 'd': PORTB |=(1<<3); PORTD=(1<<5);break;
	
	/* Force State */
	case 'e': PORTB |=(1<<3); PORTD=(1<<5);break;

	/* Mute System */
	case 'f': break;

	case 'g':
	 
	default:;
	}	

}

void wakeup_init(void)
{
/* RTC generates an Low Level Interrupt @ PCINT11 */
PCICR  =(1<< PCIE1);
PCMSK1 =(1<< PCINT11);
}

ISR(PCINT1_vect)
{
/* Solve if Module needs to be waken up or put down to sleep */

}
