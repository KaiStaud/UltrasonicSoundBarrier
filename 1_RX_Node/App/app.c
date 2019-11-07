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
/* private includes */
#include "Globals.h"
#include "App.h"
#include "ADC.h"
#include "DS3231.h"
#include "Sonar.h"
#include "UART.h"
#include "Wakeups.h"

uint32_t min_voltages[2] = {819,553};

int8_t  ambient_temp;
uint32_t batteries[2];
char 	health[3] ={'x','x','x'};
uint8_t distance;

uint8_t mute = 0;
void app_init(void)
{
	wdt_reset();
	wdt_disable();

	/* Clear all Interupts */
	cli();
	DDRC = 0x00;
	/* Enable all four status LEDs */
	DDRB  = (1<<LED_3_PIN)|(1<<LED_4_PIN)|(1<<5);
	DDRD = (1<<LED_1_PIN)|(1<<LED_2_PIN);

	PORTB = (1<<LED_3_PIN)|(1<<LED_4_PIN);
	PORTD = (1<<LED_1_PIN)|(1<<LED_2_PIN);	;

	PCICR  =(1<<PCIE1)|(1<<PCIE2);
	PCMSK1 =(1<<PCINT11);
	PCMSK2 =(1<<PCINT18);


	/* Initialize Core */
	adc_init();
	wakeups_init();
	ds3231_init();
	sonar_init();
	uart_init();
	sei();

	uart_tx("Init finished\r\n");

}

void app_reset(void)
{
	/* Reset RTC */
	RST_PORT |= (1<<RST_PIN);
	/* Dump EEPROM */

	/* Force an Hardware Reset */
	wdt_enable(WDTO_2S);
	_delay_ms(3000);
}

/* Configure Alarms over UART */
void app_config(void)
{
char new_alarm[20];
char input[20];
uint8_t index,element =0;
char *ptr;
char c = 'a';

uart_tx("Enter new Alarm,end menue by typing 'z'\r\n");

/* If end character is send close configuration */
while(c != 'z')
	{
		/* Wait for new chars */
		if(!(UCSR0A & (1<<RXC0)));
		
		else
		{
			c =UDR0;
			/* Add char to array */
			input[index] = c;
			index++;
		}
		
	}
	/* Terminate String */
	input[index-1] = 0;
	uart_tx(input);
	uart_tx("Leaving Configuration menue\r\n");
}

/* Collect continuosly data */
void op_normal(void)
{
	/* Get temperature */
	ambient_temp = rtc_get_temp();
	/* Measure TOF + Distance */
	send_pulse();
	_delay_ms(60);
	distance = calc_distance(ambient_temp);
	/* Check batteries and give alarm if nec. */
	batteries[0] = single_conversion(0);
	batteries[1] = single_conversion(2);
	//send_package(batteries,distance);
	//debug(ambient_temp,batteries,health, distance);

}

/*Enter Idle Mode */
void op_stop(void)
{
	uart_tx("Idling MCU\r\n");
	set_sleep_mode(SLEEP_MODE_IDLE);  
	sleep_enable();  
	sleep_bod_disable();
  	sleep_mode(); 
	/* Leave Sleep Mode */
	sleep_disable();  
	uart_tx("Back to standard run mode\r\n");
}

/*Enter Deep Sleep*/
void op_sleep(void)
{uart_tx("entering sleep mode\r\n");
/* Set All Pins to Inputs */ 
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
		
	DDRB |= 0x00;
	DDRC |= 0x00;
	DDRB |= 0x00;
	/* Disable the ADC */	
	ADCSRA ^= (1<<7);
	/* Disable BOD and put CPU to Sleep */
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
	sleep_enable();  
	sleep_bod_disable();
  	sleep_mode(); 
	/* Leave Sleep Mode */
	sleep_disable();  
	uart_tx("Back up runnning\r\n"); 
}
void op_button(void)
{
app_reset();
}

void op_mute(void)
{
mute = !mute;
}

void debug(int8_t ambient_temp, uint32_t *batteries,char *health,uint8_t distance)
{
	uart_tx("Ambient_Temp: ");
	uart_tx_int(ambient_temp);
	uart_tx(" Distanz: ");
	uart_tx_int(distance);
	uart_tx(" Hauptbatterie: ");
	uart_tx_int(batteries[0]);
	uart_tx(" Backupbatterie: ");
	uart_tx_int(batteries[1]);
	uart_tx("\r\n");

}

void send_package(uint32_t *batteries, uint8_t distance)
{
int i=0;
if(mute)
	{
	for(i=0; i<2;i++)
		{
			if(batteries[i] < min_voltages[i])
				{
					uart_tx("Low Voltage Alert for Battery ");
					uart_tx_int(i);
					uart_tx(",\r\n");
				}
		}
	}
uart_tx("Distance: ");
uart_tx_int(distance);
uart_tx("\r\n");
}

