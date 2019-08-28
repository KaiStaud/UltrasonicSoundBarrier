/*
 * Globals.h
 *
 * Created: 14.08.2019 16:33:24
 *  Author: kai-s
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_
/* Physical Pin for Infrared- LED*/
#define Pulse_Port PORTB
#define Pulse_Pin  7

/* Physical Connection to Voltage Divider */
#define ADC0_Port PORTB
#define ADC0_Pin	0

/* Battery Status LED Register */
#define LED_Port DDRB

/*Wakeup Pin for Phototransistor */
#define Wakeup_Port PORTB
#define Wakeup_Pin 4

/* SPI Pins*/
#define SPI_Port DDRB
#define SS	 0
#define SCK	 1
#define MOSI 2
#define MISO 3

#define Dutycycle 25






#endif /* GLOBALS_H_ */