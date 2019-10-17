#include "stdint.h"

void BT_to_HMI(char rxData[]);
uint8_t calc_own_charge(uint16_t battery_voltage);
uint32_t backlight_pwm(uint16_t sensor1,uint16_t sensor2 ,uint16_t sensor3);
void draw_display(uint8_t line, char date[5], char time[5], char state[7], char mode[5], int own_charge,int slave_charge);

