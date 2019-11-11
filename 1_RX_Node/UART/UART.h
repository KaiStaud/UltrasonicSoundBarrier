#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>

#include "avr/interrupt.h"
#include "stdint.h"


#define BAUD 19200
#define MYUBRR F_CPU/16/BAUD-1


/* USART Init Function */
void uart_init(void);

/* USART Transmit Function : String transmit only*/
void uart_tx(char message[]);

/* USART Transmit Function : Integer transmit only*/
void uart_tx_int(uint32_t number);

/* USART Transmit Function : Double transmit only*/
void uart_tx_double(double number);

/* USART Receive Function */
char * uart_rx(void); 
//ISR(USART_RX_vect);
ISR(PCINT2_vect);

void uart_init();
void usart_tx( char data );
int usart_putchar_printf(char var, FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);
