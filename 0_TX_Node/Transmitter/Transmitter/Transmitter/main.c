/*
 * Transmitter.c
 *
 * Created: 30.08.2019 17:39:15
 * Author : kai-s
 */ 

#include "Globals.h"
#include <avr/io.h>
#include "util/delay.h"
#include "PWM.h"
#include "I2C.h"
#include "SPI.h"
//#include "Globals.h"

int main(void)
{	/* Initialization Procedure*/
	I2C_init();
	SPI_init(MASTER_MODE);
	/* End init */
	
	
 for(int i=0; i<257; i++)
 {
	I2C_write(PCF8574_ADDR,i);
	SPI_write(CS_0_PORT,CS_0_PIN,i);
	_delay_ms(500);	 
 }
 
 while(1);
   
}

