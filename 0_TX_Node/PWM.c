/*
 * PWM.c
 *
 * Created: 14.08.2019 16:40:58
 *  Author: kai-s
 */ 
#include "avr/io.h"
#include "Globals.h"
#include "PWM.h"

void PWM_Init()
{/*Set on Bottom, clear on Match */
	TCCR0A |=(1<<COM0A1)|(1<<WGM00)|(1<<WGM01);
	/* PSC = 1024 */
	TCCR0B |=(1<<CS02)|(1<<CS00);
	/* Overflow Interupt */
	TIMSK0 =(1<<TOIE0);
	
}

void PWM_Operation(uint8_t Enable)
{
	if(Enable)
	OCR0A = Dutycycle *255/100;
}