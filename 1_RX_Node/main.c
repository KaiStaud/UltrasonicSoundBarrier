#define F_CPU 16000000UL
/* Global Include */
#include "Globals.h"
/* AVR own Includes */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/* Private Includes */
#include "UART.h" 
#include "Sonar.h"
#include "ADC.h"
#include "Buttons.h"
#include "I2C.h"
#include "I2C.h"
#include "DS3231.h"

uint8_t temp = 0;

typedef struct 
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}HistoricData;

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
	uint8_t mode;
}AlarmData;

int main()
{	DDRB = (1<<1);
	uart_init();
	Buttons_init();
	sonar_init();
	uart_tx("Initialisierung abgeschlossen\r\n");
	ADC_init();	

	sei();
	
	/* Externe Lib */
	//i2c_init();
	//i2c_start(0x70);
	//i2c_write(0x01);
	//i2c_stop();
	
	/* Eigene Lib */
	//I2C_init();
	//I2C_start();
	//I2C_write(0x70);
	//I2C_write(0x01);

	
	HistoricData newtime;
	newtime.sec =dec2bcd(50);
	newtime.min =dec2bcd(59);
	newtime.hour= dec2bcd(20);
	newtime.weekDay = dec2bcd(0);
	newtime.date =dec2bcd(0);
	newtime.month =dec2bcd(0);
	newtime.year = dec2bcd(0);

	AlarmData newAlarm;
	newAlarm.sec =dec2bcd(0);
	newAlarm.min =dec2bcd(0);
	newAlarm.hour= dec2bcd(21);
	newAlarm.weekDay = dec2bcd(0);
	newAlarm.date =dec2bcd(0);
	newAlarm.month =dec2bcd(0);
	newAlarm.year = dec2bcd(0);
	newAlarm.mode = DS3231_AlarmEverySecond;

	ds3231_init();
	ds3231_SetDateTime(&newtime);
	//_delay_ms(20000);
	ds3231_GetDateTime(&newtime);
	//uart_tx_int(newtime.sec);

	
	while(1)
    {
	
		temp =get_temperature();
		send_pulse();
		_delay_ms(50);

		//uart_tx_int(calc_distance(temp));
		//uart_tx("\r\n");
	

		/*
		ds3231_GetDateTime(&newtime);
		uart_tx_int(bcd2dec(newtime.hour));
		uart_tx(" : ");
		uart_tx_int(bcd2dec(newtime.min));
		uart_tx(" : ");
		uart_tx_int(bcd2dec(newtime.sec));
		uart_tx("\r\n");
		_delay_ms(1000);
		*/
    }
}

