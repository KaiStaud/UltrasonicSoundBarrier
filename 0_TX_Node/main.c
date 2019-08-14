/*
 * Emitter_Circuit.c
 *
 * Created: 14.08.2019 16:32:19
 * Author : kai-s
 */ 

#include <avr/io.h>
#include "setup.h"
#include "PWM.h"

int main(void)
{	setup_peripherals();
	PWM_Init();
	PWM_Operation(1);
    /* Replace with your application code */
    while (1) 
    {
    }
}

