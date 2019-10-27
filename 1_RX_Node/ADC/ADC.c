#include <avr/io.h>
#include "ADC.h"
#include "Globals.h"
#include "UART.h"

uint8_t temperature = 20;
uint8_t battery_voltage = 0;

double kappa = 1.1 / (1024*0.01); 

/* Initialize ADCs */
void ADC_init(void)
{	/*Start Temperature conversion 1.1V Reference */
	ADMUX = (1<<REFS0)|(1<<REFS1);
	/* ADC Input Frequency = F_CPU / 1028 */
	ADCSRA = (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	/* Enable ADC and ADC Interupt, Enabel Auto Triggering */
	ADCSRA |=(1<<ADEN),//|(1<<ADIE)|(1<<ADATE);
	/* Start ADC in Freerunning Mode */
	ADCSRA |=(1<<ADSC);
	/* Wait for First Conversion to Complete (Dummy Readout) */
	while(ADCSRA & (1<<ADSC));
}

void change_channel(uint8_t channel)
{
if(1)
ADMUX |= (1<<REFS0)|(1<<MUX0);

else
ADMUX |= (1<<REFS0)|(1<<REFS1); 
}

uint8_t single_conversion(void)
{
	/* Start Conversion */
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	return ADC;
}

/* Convert ADC 0 data to °C */
uint8_t get_temperature(void)
{
	temperature = single_conversion() * kappa;
	return temperature;
}

/* Convert ADC 1 data to V */
uint8_t get_battery_voltage(void)
{
	return battery_voltage;
}

ISR(ADC_vect)
{
/* Check the channel  and write Data to buffer*/
/*Channel 1 */
if(ADMUX & (1<<MUX0))
	{
 		battery_voltage = ADC*5/1024;
		
	}
/* Channel 0 */
else
	{
		temperature = ADC * kappa;
		/* change  to channel 0 */

	}
}

