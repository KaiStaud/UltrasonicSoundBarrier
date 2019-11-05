#include "stdint.h"
#include <avr/interrupt.h>

/* Initialize ADCs */
void adc_init(void);

/* Change ADC Channel */
void change_channel(uint8_t channel);

/* Single Conversion */
uint16_t single_conversion(uint8_t channel);

/* Convert ADC 1 data to V */
uint8_t get_battery_voltage(void);

/* ADC 0 ISR */
ISR(ADC_vect);
