/*
 * Description:    ds1307 lib for atmel studio
 * Name:           ds1307.h
 * Reference:      www.exploreembedded.com
 * Created:        16.1.2018
 * Author:         Ali Gholami
 * License:        Open-source 
 * Core:           8 bit ATMEL_MiCROCHIP
 * Last update:    16.01.2018
 * Test Des:       OK for atmega328p,8mhz
 * Website:        https://atmels.wordpress.com/
 */ 

#ifndef INCFILE1_H_
#define INCFILE1_H_

#include "stdint.h"
#include <avr\io.h>
#include <util\delay.h>


typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}rtc_t;

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
	uint8_t mode;
}alarm_t;


#define DS3231_ReadMode_U8          (0xD1)
#define DS3231_WriteMode_U8         (0xD0)
#define DS3231_REG_Seconds          (0x00)
#define DS3231_REG_Minutes          (0x01)
#define DS3231_REG_Hour             (0x02)
#define DS3231_REG_Day              (0x03)
#define DS3231_Date                 (0x04)
#define DS3231_Month                (0x05)
#define DS3231_Year                 (0x06)
#define DS3231_REG_ALARM_1          (0x07)
#define DS3231_REG_ALARM_2          (0x0B)
#define DS3231_REG_CONTROL          (0x0E)
#define DS3231_REG_STATUS           (0x0F)
#define DS3231_REG_TEMPERATURE      (0x11)

/* Enable Alarms */
#define AlarmsOn 0x03

/* Added defines for Alarm 1 */
#define DS3231_AlarmEverySecond			 (0x0F)
#define DS3231_AlarmSecondsMatch		 (0x0E)
#define DS3231_AlarmMinutesSecondsMatch  (0x0C)
#define DS3231_Alarm1TimeMatch			 (0x08)
#define DS3231_AlarmDateAndTimeMatch	 (0x00)
#define DS3231_AlarmDayAndTimeMatch		 (0x10)

/* Added defines for Alarm 2 */
#define DS3231_AlarmEveryMinute			 (0x07)
#define DS3231_AlarmMinutesMatch		 (0x06)
#define DS3231_AlarmHourMinutesMatch	 (0x04)
#define DS3231_AlarmDateHourMinutesMatch (0x05)
#define DS3231_AlarmDayHourMinutesMatch  (0x10)

void    ds3231_init(void);
void    ds3231_SetDateTime(rtc_t *rtc);
void    ds3231_GetDateTime(rtc_t *rtc);

/* Added Functions for Alarms */
void ds3231_SetFirstAlarm(alarm_t *alarm1);
void ds3231_SetSecondAlarm(alarm_t *alarm2);

void ds3231_ClearAlarms(void);
/* end */
int8_t  rtc_get_temp();

uint8_t dec2bcd(char num);
uint8_t bcd2dec(char num);
/**************************************************************************************************/

#endif /* INCFILE1_H_ */
