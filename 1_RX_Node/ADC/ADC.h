#include "stdint.h"
#include <avr/interrupt.h>

/* Initialize ADCs */
void adc_init(void);

/* Change ADC Channel */
void change_channel(uint8_t channel);

/* trigger a single adc conversion */
uint16_t single_conversion(uint8_t channel);

/* Get the Temperature in °C */
float get_temp(void);

/* Get access to raw adc data */
void get_raw_data(uint16_t* carriage);

/* ADC 0 ISR */
ISR(ADC_vect);
