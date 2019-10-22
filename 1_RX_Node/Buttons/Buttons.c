#include "Buttons.h"
void Buttons_init(void)
{
	/* Button Interupt */
	EICRA = (1<< ISC00);
	EIMSK = (1<< INT0);
}
/* Interuptroutine für Externe Interupts*/
ISR(INT0_vect)
{
	PORTB ^= (1<<4);
}
