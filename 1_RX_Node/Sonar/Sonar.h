/* Function Protoypes for sonar function */
#include <stdint.h>
#include <avr/interrupt.h>

void sonar_init(void);
void send_pulse(); /* Simulate One Pulse Mode*/
uint8_t get_time();
uint8_t calc_distance(uint8_t t_p);
ISR(TIMER1_CAPT_vect);
