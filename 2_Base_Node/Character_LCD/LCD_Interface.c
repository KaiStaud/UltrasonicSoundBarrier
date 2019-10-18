#include "stdio.h"
#include "LCD_Interface.h"
#include "STM_MY_LCD16X2.h"
#include "Globals.h"

char mcu_states[7][16]={"Run","Stop","Force","Test","Sleep","OTA","Buildnumber"};


/* Draw the new state*/
void lcd_redraw_state(uint8_t source, uint8_t state)
{	/* Clear comand fails*/
	//LCD1602_clear();
		if(source)
		{	
		LCD1602_1stLine();
		LCD1602_print("                ");
		LCD1602_1stLine();
		LCD1602_print(mcu_states[state]);
		}
			
		else
		{
		LCD1602_2ndLine();
		LCD1602_print("                ");
		LCD1602_2ndLine();
		LCD1602_print(mcu_states[state]);
		}

	}

/* Redraw time and date*/
void lcd_redraw_time(void)
{
	
}
/* Show an alert on screen*/
void lcd_redraw_alert(void)
{
	
}

/*Show successfull quitation */
void lcd_redraw_quit(void)
{
	
}	
