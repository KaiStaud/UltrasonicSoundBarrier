#include <avr/io.h>
#include "ADC.h"
#include "Globals.h"
uint8_t ADC_Data[2] ={0,0};
uint8_t temperature = 0;
uint8_t battery_voltage = 0;

/* Initialize ADCs */
void ADC_init(void)
{
/* Select V_CC as reference voltage */ 
ADMUX |= ( 1<<REFS0);
/* Start aquiring data from ADC0 */
ADMUX &=~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
/*Prescaler = 128 */
ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
/* Enable Interupt and ADC, start first conversion */
ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADIE);
/* Start in free running mode */
}

void change_channel(uint8_t channel)
{

}

/* Convert ADC 0 data to °C */
uint8_t get_temperature(void)
{temperature = ADC_Data[0];
return temperature;
}

/* Convert ADC 1 data to V */
uint8_t get_battery_voltage(void)
{
return battery_voltage;
}

/* ADC 0 ISR */
ISR(ADC_vect)
{
/* Check the channel  and write Data to buffer*/
if(ADMUX & ADC_ADC0)
 ADC_Data[0] = ADC;
else if(ADMUX & ADC_ADC1)
 ADC_Data[1] = ADC;
}

