/*
 * SPI.c
 *
 * Created: 28.08.2019 18:51:26
 *  Author: kai-s
 */ 
#include <avr/io.h>
#include "SPI.h"
#include "avr/interrupt.h"
#include "Globals.h"

void SPI_init()
{
	/*Set MOSI and SCK as Output*/
	SPI_Port |= (1<<MOSI)|(1<<SCK);
	/*Enable SPI as Master Mode*/
	SPCR |= (1<<SPIE)|(1<<SPE)|(1<<MSTR);
	
}

void SPI_write(uint8_t data)

{	/* Load Data into Data Register */
	SPDR = data;
	/*Wait until Transmission complete = Flag is set*/
	/* Flag is cleared by hardware in ISR */
	while(!(SPSR&(SPIF)))
	; 
}
ISR(SPI_STC_vect)
{
	/*Just toggle the onboard LED*/
	PORTB ^=(1<<13);
}