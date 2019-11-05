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

void app_init(void)
{
	wdt_reset();
	wdt_disable();
	wdt_reset();

	/* Clear all Interupts */
	cli();
	DDRC = 0x00;
	/* Enable all four status LEDs */
	DDRB  = (1<<LED_3_PIN)|(1<<LED_4_PIN);
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
	send_package(batteries,distance);
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
/* Perform HIL */
void op_hil(void)
{

}
void op_force(void)
{

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
int i;
	for(i=0; i<2; i++)
	{
		if(batteries[i]<min_voltages[i])
			health[i] = 'L';
		else
			health[i] = 'G';	
	}
	if(health[0]==health[1])
		health[2] = 'D';
	else
		health[2] = 'G';
}
