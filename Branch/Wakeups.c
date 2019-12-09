#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include "Globals.h"
#include "Wakeups.h"
#include "App.h"
#include <stdio.h>

uint8_t alarm_count = 0;
char d = 'a';

void wakeups_init(void)
{
	/* Setup Interrupts */
	PCICR  =(1<<PCIE1)|(1<<PCIE2);
	PCMSK1 =(1<<PCINT10);
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
alarm_count++;
printf("Alarm!\n");
/* extern Flag doesn't get recognized by MCU */
	if (alarm_count==4) // After the forth event, let MCU stay in Run Mode
	{
	alarm_count=0; //reset counter
	d = 'a';
	}
	else
	d = 'c'; // Always put mcu back to sleep
	//printf("%c",c);
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
