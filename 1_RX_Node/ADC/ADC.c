#include <avr/io.h>
#include "ADC.h"
#include "Globals.h"
#include "UART.h"

uint8_t battery_voltage[2] = {0,0};

/* Initialize ADCs */
void ADC_init(void)
{	/*Select 5V Reference */
	ADMUX = (1<<REFS0);
	/* ADC Input Frequency = F_CPU / 1028 */
	ADCSRA = (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	/* Enable ADC and ADC Interupt, Enabel Auto Triggering */
	ADCSRA |=(1<<ADEN);//|(1<<ADIE);//|(1<<ADATE);
	/* Start ADC in Freerunning Mode */
	ADCSRA |=(1<<ADSC);
	/* Wait for First Conversion to Complete (Dummy Readout) */
	//while(ADCSRA & (1<<ADSC));
}

void change_channel(uint8_t channel)
{
	/* Halt the ADC */
	ADCSRA ^=(1<<ADEN);
	ADMUX&=~0xFF; 
	
	/*measure main battery voltage */
	if(channel ==0)
		ADMUX |= (1<<REFS0);
	
	/* RTC backup battery measurement */
	else if (channel ==2)
		ADMUX |= (1<<REFS0)|(1<<MUX1);
	
 	/* Enable ADC again */
	ADCSRA ^=(1<<ADEN);
}

uint16_t single_conversion(uint8_t channel)
{
change_channel(channel);
ADCSRA |=  (1<<ADSC);
while(ADCSRA & (1<<ADSC));
return ADC;
}

/* Convert ADC data to V */
uint8_t get_battery_voltage(void)
{
	return battery_voltage;
}

ISR(ADC_vect)
{
/* Check the channel  and write Data to buffer*/

/* Channel 2 */
if(ADMUX &(1<<MUX1))
	{
		battery_voltage[1] = ADC;
		uart_tx("  Channel 2:  ");
		uart_tx_int(ADC);
		uart_tx("\r\n");
		change_channel(0);
	}
/* Channel 0 */
else
	{
		battery_voltage[0] = ADC;
		uart_tx("Channel 0:  ");
		uart_tx_int(ADC);
		change_channel(2);
	}
	ADCSRA |= (1<<ADSC);

}

