#include "avr/interrupt.h"
#include "stdint.h"

/* USART Init Function */
void uart_init(void);

/* USART Transmit Function : String transmit only*/
/* Return Parameters : none ; Input Parameters : char message[] */ 
void uart_tx(char message[]);

/* USART Transmit Function : Integer transmit only*/
/* Return Parameters : none ; Input Parameters : int number */ 
void uart_tx_int(uint32_t number);

/* USART Receive Function */
/* Return Parameters : char* ; Input Parameters : none */
char * uart_rx(void); 
ISR(USART_RX_vect);
