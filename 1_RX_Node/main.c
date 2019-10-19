
/* Includes */
#include <avr/io.h>
#include "Globals.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"

/* Start of Application */
int main()
{
uart_init();
while(1)
{
/* Send Char*/ 
uart_tx("Hello");
//_delay_ms(1000);
}

}
