#ifndef uart_h
#define uart_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

/* USART Init Function */
void uart_init(void);

void uart_init();
void usart_tx( char data );
int usart_putchar_printf(char var, FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);

#endif
