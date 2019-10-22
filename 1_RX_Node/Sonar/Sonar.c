#include "Globals.h"
#include "Sonar.h"
#include "UART.h"
#include <avr/io.h>
#include <util/delay.h>

volatile uint32_t TOF=0;

void sonar_init(void)
{
	/* Rising Edge ,CLK Prescaler 1024 */
	TCCR1B = (1<<ICES1)|(1<<CS12);
	/* Enable Input Capture Interupt */
	TIMSK1 = (1<<ICIE1);
}
void send_pulse(void) /* Simulate One Pulse Mode*/
{
	SonarPort  |=  (1<<SonarPin);
	_delay_ms(500);
	SonarPort &=~ (1<<SonarPin);
}

uint8_t get_time()
{
	uint8_t time=0;
	return time;
}


uint8_t calc_distance(uint8_t t_p)
{
	uint8_t distance =0;
	return distance;
}

/* Interuptroutine für Input Capture */
ISR(TIMER1_CAPT_vect)
{

/* Flankenerkennung umstellen*/
TCCR1B ^= (1<<ICES1);

/* Rising Edge erkennen*/
if(TCCR1B & TCCR1B_ICES1)
{
TCNT1 = 0;
PORTB ^=(1<<5);
}
/*Falling Edge erkennen*/

else
{
//TOF = ICR1;
TOF = TCNT1;
PORTB ^=(1<<4);
uart_tx_int(TOF);
}

}
