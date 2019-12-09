#include <avr/io.h>
#include "ADC.h"
#include "Globals.h"

uint16_t battery_voltage[2] = {0,0};
uint16_t temperature_buff =0;
float temperature = 0;

/* Initialize ADCs */
void adc_init(void)
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
	/* Measure the voltage on LM35 ADJ Pin */
	if(channel ==CHANNEL_LM35_ADJ)
		ADMUX |= (1<<REFS0);
	/*measure main battery voltage */
	else if(channel ==CHANNEL_MAIN_SUPPLY)
		ADMUX |= (1<<REFS0)|(1<<MUX1);
	
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

/* Convert ADC data to V */
uint8_t get_battery_voltage(void)
{
	return battery_voltage[0];
}

float get_temp(void)
{
temperature_buff = single_conversion(CHANNEL_LM35_ADJ);
//temperature = (temperature_buff*500)/1024;

 temperature = (temperature_buff*50)/1024;
return temperature;
}

ISR(ADC_vect)
{
/* Check the channel  and write Data to buffer*/

if(ADMUX ==CHANNEL_LM35_ADJ)
	{
		temperature_buff = ADC;
		change_channel(CHANNEL_MAIN_SUPPLY);
	}

else if(ADMUX == CHANNEL_MAIN_SUPPLY)
	{
		battery_voltage[1] = ADC;
		change_channel(CHANNEL_BACKUP_SUPPLY);
	}
/* Channel  */
else if(ADMUX == CHANNEL_BACKUP_SUPPLY)
	{
		battery_voltage[0] = ADC;
		change_channel(CHANNEL_LM35_ADJ);
	}
	ADCSRA |= (1<<ADSC);

}
