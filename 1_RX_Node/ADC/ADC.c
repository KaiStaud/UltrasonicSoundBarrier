#include <avr/io.h>
#include "ADC.h"
#include "Globals.h"

uint16_t battery_voltage[2] = {0,0};
uint16_t temperature_buff =0;
float temperature = 0;

/* Initialize ADCs */
void adc_init(void)
{	/*Select 5V Reference start @ channel 1 */
	ADMUX = (1<<REFS0);
	/* ADC Input Frequency = F_CPU / 1028 */
	ADCSRA = (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	/* Enable ADC and ADC Interupt */
	ADCSRA |=(1<<ADEN)|(1<<ADIE);
	/* Start ADC in Freerunning Mode */
	ADCSRA |=(1<<ADSC);
}

void change_channel(uint8_t channel)
{
	/* Halt the ADC */
	ADCSRA ^=(1<<ADEN);
	ADMUX&=~0xFF; 
	
	/* Measure the voltage on LM35 ADJ Pin */
	if(channel ==CHANNEL_LM35_ADJ)
		ADMUX |= (1<<REFS0)|(1<<MUX0);
	
	/* measure main battery voltage */
	else if(channel ==CHANNEL_MAIN_SUPPLY)
		ADMUX |= (1<<REFS0);
	
	/* RTC backup battery measurement */
	else if (channel ==CHANNEL_BACKUP_SUPPLY)
		ADMUX |= (1<<REFS0)|(1<<MUX0)|(1<<MUX1);
	
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

float get_temp(void)
{
	temperature = (temperature_buff*50)/1024;
	return temperature;
}

void get_raw_data(uint16_t* carriage)
{
	carriage[0] = battery_voltage[0];
	carriage[1] = battery_voltage[1];
	carriage[2] = temperature_buff;
}

ISR(ADC_vect)
{
/* Check the channel  and write Data to buffer*/

if((ADMUX & 0x0F) ==CHANNEL_LM35_ADJ)
	{
		temperature_buff = ADC;
		change_channel(CHANNEL_MAIN_SUPPLY);
	}

else if((ADMUX & 0x0F) == CHANNEL_MAIN_SUPPLY)
	{
		battery_voltage[1] = ADC;
		change_channel(CHANNEL_BACKUP_SUPPLY);
	}
/* Channel  */
else if((ADMUX & 0x0F) == CHANNEL_BACKUP_SUPPLY)
	{
		battery_voltage[0] = ADC;
		change_channel(CHANNEL_LM35_ADJ);
	}
	ADCSRA |= (1<<ADSC);

}
