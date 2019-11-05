#include "avr/interrupt.h"
#include "stdint.h"

extern char message[];
extern char c;

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
