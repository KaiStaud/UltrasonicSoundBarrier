#include "Globals.h"
/* official c headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/* avr libc includes */
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
/* private includes */
#include "App.h"
#include "ADC.h"
#include "Sonar.h"
#include "UART.h"
#include "twi.h"
#include "rtc.h"
#include "rtc_startup.h"
#include "Wakeups.h"
#include "EEPROM.h"

uint16_t min_voltages[2] = {819,553};

uint32_t  ambient_temp = 0;
char 	health[3] ={'x','x','x'};
uint8_t distance = 0;
uint8_t mute = 0;

struct tm* t = NULL;
uint8_t hour=0, min=0, sec=0;

uint16_t data_carriage[3] = {0,0,0};

void app_init(void)
{
	wdt_reset();
	wdt_disable();

	/* Clear all Interupts */
	cli();
	DDRC = 0x00;
	RTCPort |=(1<<RTCPin);

	PCICR  =(1<<PCIE1)|(1<<PCIE2);
	PCMSK1 =(1<<PCINT11);
	PCMSK2 =(1<<PCINT18);


	/* Initialize Core  and Peripherals */
	uart_init();
	adc_init();
	wakeups_init();
	sonar_init();
	uart_init();
	sei();
	twi_init_master();
	rtc_reset_alarm();
	rtc_init();
	/* If RTC is not configured ask for Initialization */
	if(eeprom_read_byte((uint8_t*)0x06)== 0xFF)
	{
		/* Set the initial time and first two Alarms */
		init_time();
		/* Set initial Alarms  */
		init_alarms();
		/* Update configuration byte in EEPROM */
		eeprom_update_byte((uint8_t*)0x06,0x01);
	}
	/* If already configured do nothing */ 
	rtc_write_byte(~0b00000011, 0x0f);
	printf("Init finished");
}

void app_reset(void)
{
	/* Soft RTC Reset */
	/* Dump EEPROM */
	clear_eeprom();
	/* Force an Hardware Reset */
	wdt_enable(WDTO_2S);
	_delay_ms(3000);
}

/* Configure Alarms over UART */
void app_config(void)
{	/* Read Time */
	init_time();
	/* Read Alarms */
	return_eeprom(); // Already stored Alarms 
	init_alarms();
	printf("Leaving Configuration menue");
}

/* Collect continuosly data */
void op_normal(void)
{
	get_raw_data(&data_carriage);
	//printf("%i %i %i\n",data_carriage[0],data_carriage[1], data_carriage[2]);
	
	/* Measure TOF + Distance */
	send_pulse();
	_delay_ms(60);
	distance = calc_distance(get_temp());
	
	/* Check batteries and give alarm if nec. */
	//send_package(data,distance);
	debug(data_carriage, distance);
	t = rtc_get_time();
	rtc_write_byte(~0b00000011, 0x0f);
}

/*Enter Idle Mode */
void op_stop(void)
{	rtc_write_byte(~0b00000011, 0x0f);
	printf("Idling MCU");
	set_sleep_mode(SLEEP_MODE_IDLE);  
	sleep_enable();  
	sleep_bod_disable();
  	sleep_mode(); 
	/* Leave Sleep Mode */
	sleep_disable();
	/* Clear alarm on RTC */
	rtc_write_byte(~0b00000011, 0x0f);  
	printf("Back to standard run mode");
}

/*Enter Deep Sleep*/
void op_sleep(void)
{
rtc_write_byte(~0b00000011, 0x0f);
printf("entering sleep mode");
/* Set All Pins to Inputs */ 
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
		
	DDRB |= 0x00;
	DDRC |= 0x00;
	DDRB |= 0x00;
	/* Disable the ADC */	
	ADCSRA &=~ (1<<7);
	SMCR |=(1<<2); // Power down mode
	SMCR |=1; // enable sleep instructions
	MCUCR |= (3<<5); //set BODSE and BODS at the same time 
	MCUCR = (MCUCR&~(1<<5))|(1<<6);//set BODS clera BODSE at the same time
	__asm__ __volatile__("sleep");

	/* Disable BOD and put CPU to Sleep */
	sleep_bod_disable();
	/* Leave Sleep Mode */
	sleep_disable();
	/* Clear alarm on RTC */
	rtc_write_byte(~0b00000011, 0x0f);  
	ADCSRA |= (1<<7);
	/* Regenerate Pinout */
	SonarPort |= (1<<SonarPin);
	RTCPort |= (1<<RTCPin);

	_delay_ms(1000);  
	printf("Back up runnning"); 



}
void op_button(void)
{
	app_reset();
}

void op_mute(void)
{
	mute = !mute;
}

void debug(uint16_t *data,uint8_t distance)
{
	uint8_t i,f;
	ds3231_get_temp_int(&i,&f);
	printf("%i,%i,%i,%i,%i\n",data[2],i,distance,data[0],data[1]);
}

void send_package(uint32_t *batteries, uint8_t distance)
{
	int i=0;
	if(mute)
	{
	for(i=0; i<2;i++)
		{
			if(batteries[i] < min_voltages[i])
				printf("Low Voltage Alert for Battery %i",i);
		}
	}
	printf("Distance:%i",(int)distance);
}

