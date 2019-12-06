/* Function Protoypes for sonar function */
#include <stdint.h>
#include <avr/interrupt.h>

/* init function for active sonar module */
void sonar_init(void);

/* emit a 10usec pulse */
void send_pulse(void); /* Simulate One Pulse Mode*/

/* calculate the passed time in seconds*/
void get_time(void);

/* calculate the distance */
uint16_t calc_distance(float theta_a);

/* Get the Sonar Offset */
void set_offset(void);

/* Return Sonar Offset */
uint8_t get_offset(void);

/* interrupt routine*/
ISR(TIMER1_CAPT_vect);
