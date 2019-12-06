#include <avr/io.h>
#include <avr/interrupt.h>

//extern uint8_t alarm_count;
extern char d; 

void wakeups_init(void);
/* Soft-Reset-> further info @ https://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_softreset */
void wdt_init(void) __attribute__((naked)) __attribute__((section(".init3")));

/* RTC ISR */
ISR(PCINT1_vect);

/* Button + UART RX ISR */
ISR(PCINT2_vect);
