#include "Globals.h"
#include "statemachines.h"
#include "LCD_Interface.h"

uint8_t current_state= 0;
uint8_t active_state = 0;

/* change mcu_state through button or bt*/
uint8_t switch_state(void)
{
	active_state = current_state;
	/* Redraw display*/
	lcd_redraw_state(1,active_state);
	/* Write to BT Database */
	return active_state;
}	

/* Scroll through statemachines, not changing mcu state*/
uint8_t scroll_state(uint8_t direction)
{
	if(direction)
	{
		if(current_state == UI_End)
			current_state = 0;
		else
			current_state++;

	}
	else
	{
		if(current_state == UI_Start)
			current_state = UI_End;
		else
			current_state--;

	}
	/* Redraw display*/
	lcd_redraw_state(0,current_state);
	
	/* Write to BT Database */
	
	return current_state;
}	
