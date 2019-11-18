#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include "Globals.h"
#include "Wakeups.h"

void wakeups_init(void)
{
	/* Setup Interrupts */
	PCICR  =(1<<PCIE1)|(1<<PCIE2);
	PCMSK1 =(1<<PCINT11);
	PCMSK2 =(1<<PCINT16)|(1<<PCINT18);

	//wdt_init();
}

void wdt_init(void)
{
	MCUSR = 0;
	wdt_disable();
	return;
}

/* RTC  ~INT- Pin ISR */
ISR(PCINT1_vect)
{

}
/* User Button ISR */
ISR(PCINT2_vect)
{
/* Button Interrupt */
if(!(PIND & (1<<2)))
{	
	// Doesn't work : c = 'd';
	//app_reset();
}
/* UART Interrupt -> only for waking up  MCU */
else ;
}
