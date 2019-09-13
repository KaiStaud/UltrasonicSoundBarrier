/*
 * SPI.c
 *
 * Created: 30.08.2019 21:11:12
 *  Author: kai-s
 */ 
#include <avr/io.h>
#include "SPI.h"
#include "Globals.h"

/*AD8400 Data gets transferred at rising_edge(sck) -> CPOL = 0 */


/* Initialize SPI Comunication */
void SPI_init(uint8_t SPI_MODE)
{	SPI_PORT |=(1<<SCK)|(1<<MISO)|(1<<MOSI);
	CS_0_PORT|=(1<<CS_0_PIN);
	/* Run @ max Speed 4Mhz*/
	SPCR |=(SPI_MODE<<MSTR);
	SPCR |= (1<<SPIE)|(1<<SPE)|(MSBFIRST<<DORD)|(0<<CPOL)|(0<<CPHA);
}

/* Write Data to Slave */
void SPI_write(uint8_t CS_Port, uint8_t CS_Pin,uint8_t data)
{/* CS is active when low */
 CS_Port &=~ (1<<CS_Pin);
 SPDR = data;
 /* wait for transmission to complete*/
 while(!(SPSR & (1<<SPIF)));
 CS_Port |=(1<<CS_Pin);
}

/* Read Data from Master */
uint8_t SPI_read()
{
	uint8_t MOSI_data= 0;
	return MOSI_data;
}