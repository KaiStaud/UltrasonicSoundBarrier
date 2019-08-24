/*
 * DeepSleep.c
 *
 * Created: 24.08.2019 16:24:28
 *  Author: kai-s
 */ 
#include "avr/io"
#include "avr/sleep.h"
#include "DeepSleep.h"

void set_mode(uint8_t sleep_mode)
{
	SMCR |=(1<<sleep_mode);
	
}
void ISR(PCINT0_vect)
{
	set_mode(IDLE);
}