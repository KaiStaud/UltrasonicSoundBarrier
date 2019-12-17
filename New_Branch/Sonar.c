#include "Globals.h"

/* AVR libc Includes */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <math.h>

#include <stdio.h>

/* Private Includes */
#include "Sonar.h"
#include "ADC.h"

/* Time of Flight in Clock Cycles */
volatile uint32_t timer_ticks =0;
double time_sec = 0;
uint16_t offset =0;

void sonar_init(void)
{	DDRB |= (1<<SonarPin);
	/* Rising Edge ,CLK Prescaler 8 */
	TCCR1B = (1<<ICES1)|(1<<CS11);
	/* Enable Input Capture Interupt */
	TIMSK1 = (1<<ICIE1);
}
void send_pulse(void) /* Simulate One Pulse Mode*/
{
	SonarPort  |=  (1<<SonarPin);
	_delay_us(10);
	SonarPort  ^= (1<<SonarPin);
}

void get_time(void)
{
	time_sec =  timer_ticks * tau;
}

void set_offset(void)
{
}

uint8_t get_offset(void)
{
uint8_t int_offset=0;
return int_offset;
}


/* final method to calculate distance in cm */
uint16_t calc_distance(float theta_a)
{	
	double v_sonic = 331.5 * sqrt((theta_a +273.15)/273.15);
	double distance = 0;
	
	/* get updated time of flight */
	get_time();

	distance = (time_sec*v_sonic)/2*100 - offset;
	
	return distance;
}

/* Input Capture Interruptroutine : get TOF */
ISR(TIMER1_CAPT_vect)
{

/* Switch the Selected Edge*/
TCCR1B ^= (1<<ICES1);

/* detect rising edge */
if(!(TCCR1B & TCCR1B_ICES1))
{
TCNT1 = 0;
//PORTB ^=(1<<5);
}

/*detect falling edge */
else
{
timer_ticks = ICR1;
//TOF = TCNT1;
//PORTB ^=(1<<4);

}

}
