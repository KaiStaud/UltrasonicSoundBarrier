/*
 * I2C.c
 *
 * Created: 28.08.2019 19:24:44
 *  Author: kai-s
 */

#include "avr/io.h"
#include "I2C.h"
#include "Globals.h"

/* Initialize I2C */
void I2C_init()
{
	/* Set SCL Speed to 100kHz*/
	TWBR = 0x10;
}
/* Send Start Command */
unsigned char I2C_start()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);	
	/*wait, until start condition has been sent --> ACK*/
	while (!(TWCR & (1<<TWINT)));
	return TWSR;
	
}
/* Send Stop Bit */
void I2C_stop()
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}
/* Send Data */
unsigned char I2C_send(unsigned char byte)
{
	/*TWDR contains byte to send*/
	TWDR = byte;
	/*send content of TWDR*/
	TWCR = (1<<TWINT) | (1<<TWEN);
	/*wait, until byte has been sent --> ACK*/
	while (!(TWCR & (1<<TWINT)));
	return TWSR;	
}

/* Address */
unsigned char I2C_send_Address(unsigned char I2C_address, unsigned char rw)
{	
	unsigned char addr_byte = 0;
	addr_byte = I2C_address << 1;
	/*set RW-Bit, if necessary*/
	addr_byte |= rw;
	addr_byte |= 0b01000000;
	
	I2C_send(addr_byte);
	return TWSR;
}

/* Transmit Data to Slave */
void I2C_write(unsigned char I2C_address, unsigned char data)
{
	I2C_init();
	I2C_start();
	I2C_send_Address(I2C_address,0);
	I2C_send(data);
	I2C_stop();
}