#include "DataProcessing.h"
#include "STM_MY_LCD16X2.h"
#include "stdio.h"
#include "string.h"

void BT_to_HMI(char rxData[])
{	/****Display example ***/
	/*20:35______12.10			*/
	/*___non blocked__			*/
	/*____SLEEP MODE__			*/
	/*100%________100%			*/
	
	
	
	/* Split String add ',' */
	char information[3][16] = {"NULL","NULL","NULL"};
	uint8_t lcd_line=0;
	char *ptr;
	
	ptr = strtok(rxData,",");
	LCD1602_clear();
	
	while(ptr != NULL)
	{		switch(lcd_line)
			{
				case 0: printf("1st Line %s \r\n",ptr); LCD1602_1stLine(); LCD1602_print(ptr); break;
				case 1: printf("2nd Line %s \r\n",ptr); LCD1602_2ndLine(); LCD1602_print(ptr);break;
				case 2: printf("3rd Line %s \r\n",ptr);break;
				case 3: printf("4th Line %s \r\n",ptr);break;
			}
			/*Search for next string */
		 	ptr = strtok(NULL, ",");
			lcd_line++;
	}
}

uint8_t calc_own_charge(uint16_t battery_voltage)
{
	uint8_t charge;
	return charge;
}	

uint32_t backlight_pwm(uint16_t sensor1,uint16_t sensor2 ,uint16_t sensor3)
{
	uint32_t pwm;
	return pwm;
}	
void draw_display(uint8_t line, char date[5], char time[5], char state[7], char mode[5],  int own_charge, int slave_charge)
{
	switch(line)
	{	
		/* Draw Date and Time*/
		case 0: LCD1602_1stLine(); LCD1602_print(time); LCD1602_setCursor(1,12); LCD1602_print(date); break;
		
		/*Draw state */
		case 1: LCD1602_setCursor(2,1); LCD1602_print(state);break;
		
		/* Draw MCU State */
		case 2: LCD1602_setCursor(1,4); LCD1602_print(mode);break;
		
		/* Draw Charge information */
		case 3: LCD1602_2ndLine();LCD1602_PrintInt(own_charge); LCD1602_setCursor(2,12); LCD1602_PrintInt(slave_charge);break;
	
		default: break;
	}	
}
