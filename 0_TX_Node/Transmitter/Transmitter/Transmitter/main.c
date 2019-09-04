/*
 * Transmitter.c
 *
 * Created: 30.08.2019 17:39:15
 * Author : kai-s
 */ 


#include <avr/io.h>
#include "PWM.h"
#include "I2C.h"
#include "Globals.h"

int main(void)
{
 I2C_write(PCF8574_ADDR,0xCA);
 while(1);  
}

