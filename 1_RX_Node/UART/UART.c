/* Private Includes */
#include "UART.h"
#include "avr/io.h"
#include "Globals.h"

/* Official C Includes */
#include "stdio.h"

#define Baudrate 9600UL
#define Baudvalue (((F_CPU / (16*Baudrate))) - 1)

void uart_init(void)
{
/* Set Baudrate to 9600 Baud/s*/
UBRR0H =(Baudvalue>>8);
UBRR0L = Baudvalue;

/* Enable RX and TX Functionality */
UCSR0B |= (1<<RXEN0) |(1<<TXEN0)|(1<<RXCIE0) ;

/* Set UART and 8 Bits */
UCSR0C = (1<<UCSZ00) |(1<<UCSZ01);
}

void uart_tx(char message[])
{
uint8_t message_index = 0;
/* Compute string length */
//uint8_t message_length = strlen(message);

/* Transmit every character on its own*/
while(message[message_index] != '\0')
{
while (!(UCSR0A & (1<<UDRE0)));  /* wait for transmission to complete */                         
UDR0 = message[message_index];
message_index++;
}
	
}

void uart_tx_int(uint32_t number)
{
char int_to_str[12];
sprintf(int_to_str, "%lu", number);

uart_tx(int_to_str);

}

ISR(USART_RX_vect)
{
char c = UDR0;
UDR0 = c;
}

char * uart_rx(void); 
