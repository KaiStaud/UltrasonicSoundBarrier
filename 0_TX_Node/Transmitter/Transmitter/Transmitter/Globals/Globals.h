/*
 * Globals.h
 *
 * Created: 30.08.2019 17:55:25
 *  Author: kai-s
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_

#define F_CPU 16000000
#define MSBFIRST 0
#define  LSBFIRST 1

/* SPI Interface */
#define SPI_PORT	DDRB
#define MASTER_MODE 1
#define SLAVE_MODE	0
#define SCK			1
#define MISO		3
#define MOSI		2
#define CS_0_PORT	DDRB
#define CS_0_PIN		0

/* I2C Interface */
#define I2C_PORT	DDRD
#define SDA			1
#define SCL			0
/* Slave Addresses */
#define PCF8574_ADDR 0x38 //MSB to LSB : 0100 000

/* ADC Pins		*/
#define ADC_Port


/*	Sleep Modes  */
#define IDLE		0x0
#define POWERSAVE	0x3
#define POWERDOWM	0x2
#define STANDBY		0x6
#define DEEPSLEEP	0x7








#endif /* GLOBALS_H_ */