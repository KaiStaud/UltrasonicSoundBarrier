/* ADC functionality covers:

-> aquiring temperature data
-> aquiring current battery voltage
*/

#include "stdint.h"
#include <avr/interrupt.h>

/* Initialize ADCs */
void ADC_init(void);

/* Change ADC Channel */
void change_channel(uint8_t channel);

/* Single Conversion */
uint8_t single_conversion(void);

/* Convert ADC 0 data to °C */
uint8_t get_temperature(void);

/* Convert ADC 1 data to V */
uint8_t get_battery_voltage(void);

/* ADC 0 ISR */
ISR(ADC_vect);
