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
double calc_distance(uint8_t theta_a);

/* interrupt routine*/
ISR(TIMER1_CAPT_vect);
