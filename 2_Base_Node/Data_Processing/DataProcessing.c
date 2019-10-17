#include "DataProcessing.h"
#include "STM_MY_LCD16X2.h"
#include "stdio.h"
#include "string.h"

void BT_to_HMI(char rxData[])
{
	
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
}
