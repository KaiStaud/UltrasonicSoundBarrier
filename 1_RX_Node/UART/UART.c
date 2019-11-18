/* Private Includes */
#include "UART.h"
#include "avr/io.h"
//#include "Globals.h"
/* Official C Includes */
#include "stdio.h"
#include "string.h"
#include "Globals.h"
#include "avr/io.h"

//#define F_CPU 16000000UL
#define Baudrate 9600UL
#define Baudvalue (((F_CPU / (16*Baudrate))) - 1)

void uart_init(void)
{	stdout = &mystdout;
	/* Set Baudrate to 9600 Baud/s*/
	UBRR0H =(Baudvalue>>8);
	UBRR0L = Baudvalue;

	/* Enable RX and TX Functionality */
	UCSR0B = (1<<RXEN0) |(1<<TXEN0);//|(1<<RXCIE0) ;

	/* Set UART and 8 Bits */
	UCSR0C = (1<<UCSZ00) |(1<<UCSZ01);
}

void usart_tx(char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1<<UDRE0)));
    // Start transmission
    UDR0 = data; 
}
 
// this function is called by printf as a stream handler
int usart_putchar_printf(char var, FILE *stream) {
    // translate \n to \r for br@y++ terminal
    if (var == '\n') usart_tx('\r');
    usart_tx(var);
    return 0;
}
