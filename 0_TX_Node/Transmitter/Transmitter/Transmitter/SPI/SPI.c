/*
 * SPI.c
 *
 * Created: 30.08.2019 21:11:12
 *  Author: kai-s
 */ 
#include "SPI.h"
#include "Globals.h"

/* Initialize SPI Comunication */
void SPI_init()
{	/* Run @ max Speed 4Mhz*/
	SPCR |= (1<<SPIE)|(1<<SPE)|(MSBFIRST<<DORD)|(0<<CPOL)|(0<<CPHA);
}

/* Write Data to Slave */
void SPI_write(uint8_t CS,uint8_t data)
{
 CS_0_PORT |= (1<<CS_0);
 SPDR = data;
 CS_0_PORT &=~(1<<CS_0);
}

/* Read Data from Master */
uint8_t SPI_read()
{
	uint8_t MOSI_data= 0;
	return MOSI_data;
}