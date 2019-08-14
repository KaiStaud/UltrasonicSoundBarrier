/*
 * setup.c
 *
 * Created: 14.08.2019 16:46:30
 *  Author: kai-s
 */ 
#include "avr/io.h"
#include "setup.h"
#include "Globals.h"

/*Initialize the Peripherals*/
void setup_peripherals()
{	LED_Port |= 0xFF;
	Pulse_Port |= (1<<Pulse_Pin);
	ADC0_Port  |= (0<<ADC0_Port);
	
}