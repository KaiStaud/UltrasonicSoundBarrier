#include <avr/io.h>
#include <avr/sleep.h>
#include "Globals.h"
#include <avr/wdt.h>
#include <util/delay.h>
#include "Energymodes.h"

void Change_PowerMode(char c)
{
 int mode_index =0;
 wdt_disable();
 wdt_reset();
	
	PORTB ^= (1<<3)|(1<<4);
	PORTD ^= (1<<5)|(1<<6);
	uart_tx(c);
	switch(c)
	{
	/* Run State */
	case 'o':PORTD |= (1<<5);break;

	/* Stop CPU */ 
	case 'x': break;

	/* Enter Sleep Mode */
	case 's': 
		/* Set All Pins to Inputs */ 
		PORTB = 0x00;
		PORTC = 0x00;
		PORTD = 0x00;
		
		DDRB |= 0x00;
		DDRC |= 0x00;
		DDRB |= 0x00;
		/* Disable the ADC */	
		ADCSRA ^=(1<<7);
		/* Disable BOD and put CPU to Sleep */
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
		sleep_enable();  
		sleep_bod_disable();
	  	sleep_mode(); 
		/* Leave Sleep Mode */
		sleep_disable();   
		DDRB  = (1<<LED_3_PIN)|(1<<LED_4_PIN);
		DDRD = (1<<LED_1_PIN)|(1<<LED_2_PIN);
	
	
		PORTB  = (1<<LED_3_PIN);
		PORTD = (1<<LED_1_PIN)|(1<<LED_2_PIN);
	break;

	/* Perform HIL Test */
	case 'h': PORTB |=(1<<3); PORTD=(1<<5);break;
	
	/* Force State */
	case 'f': PORTB |=(1<<3); PORTD=(1<<5);break;

	/* Mute System */
	case 'm': break;
		/* Reset complete system */
	case 'r':
		/* Reset RTC */
		RST_PORT |= (1<<RST_PIN);
		/* Dump EEPROM */

		/* Force an Hardware Reset */
		wdt_enable(WDTO_2S);
		_delay_ms(3000);
		

	break;
	default:break;
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
