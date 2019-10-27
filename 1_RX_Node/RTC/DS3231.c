/*
 * Description:    ds3231 lib for atmel studio
 * Name:           ds3231.c
 * Reference:      
 * Created:        16.1.2018
 * Author:         Ali Gholami
 * License:        Open-source 
 * Core:           8 bit ATMEL_MiCROCHIP
 * Last update:    17.1.2018
 * Test Des:       OK for atmega328p,8mhz
 * Website:        https://atmels.wordpress.com/
 */ 

#include  "DS3231.h"
#include  "I2C.h"

void ds3231_init(void)
{
    i2c_init();                             // Initialize the I2c module.
    /*gemoddet */ i2c_start(DS3231_WriteMode_U8);        // Start I2C communication
    //i2c_write(DS3231_WriteMode_U8);          // Connect to ds3231 
    i2c_write(DS3231_REG_CONTROL);          // Select the ds3231 ControlRegister 
    i2c_write(0x00);                        // Write 0x00 to Control register to disable SQW-Out
    i2c_stop();                             // Stop I2C communication after initializing ds3231
}

/***************************************************************************************************
                    void ds3231_SetDateTime(rtc_t *rtc)
****************************************************************************************************/

void ds3231_SetDateTime(rtc_t *rtc)
{
    i2c_start(DS3231_WriteMode_U8);                          // Start I2C communication
    //i2c_write(DS3231_WriteMode_U8);      // connect to ds3231 by sending its ID on I2c Bus
    i2c_write(DS3231_REG_Seconds);       // Request sec RAM address at 00H

    i2c_write(rtc->sec);                    // Write sec from RAM address 00H
    i2c_write(rtc->min);                    // Write min from RAM address 01H
    i2c_write(rtc->hour);                    // Write hour from RAM address 02H
    i2c_write(rtc->weekDay);                // Write weekDay on RAM address 03H
    i2c_write(rtc->date);                    // Write date on RAM address 04H
    i2c_write(rtc->month);                    // Write month on RAM address 05H
    i2c_write(rtc->year);                    // Write year on RAM address 06h
	
    i2c_stop();                              // Stop I2C communication after Setting the Date
}

/***************************************************************************************************
                     void ds3231_GetDateTime(rtc_t *rtc)
****************************************************************************************************/
void ds3231_GetDateTime(rtc_t *rtc)
{
    i2c_start(DS3231_WriteMode_U8);                            // Start I2C communication
    //i2c_write(DS3231_WriteMode_U8);        // connect to ds3231 by sending its ID on I2c Bus
    i2c_write(DS3231_REG_Seconds);         // Request Sec RAM address at 00H
    i2c_stop();                            // Stop I2C communication after selecting Sec Register

    i2c_start(DS3231_ReadMode_U8);                            // Start I2C communication
    //i2c_write(DS3231_ReadMode_U8);            // connect to ds3231(Read mode) by sending its ID

    rtc->sec = i2c_readAck();                // read second and return Positive ACK
    rtc->min = i2c_readAck();                 // read minute and return Positive ACK
    rtc->hour= i2c_readAck();               // read hour and return Negative/No ACK
    rtc->weekDay = i2c_readAck();           // read weekDay and return Positive ACK
    rtc->date= i2c_readAck();              // read Date and return Positive ACK
    rtc->month=i2c_readAck();            // read Month and return Positive ACK
    rtc->year =i2c_readNack();             // read Year and return Negative/No ACK

    i2c_stop();                              // Stop I2C communication after reading the Date
}

int8_t rtc_get_temp()
{
	uint8_t MSB;
	uint8_t LSB;

	i2c_start(DS3231_WriteMode_U8);                          // Start I2C communication
	//i2c_write(DS3231_WriteMode_U8);        // connect to ds3231 by sending its ID on I2c Bus
	i2c_write(DS3231_REG_TEMPERATURE);    // Request Sec RAM address at 11H
	i2c_stop();                           // Stop I2C communication after selecting Sec Register
	i2c_start(DS3231_ReadMode_U8);                          // Start I2C communication
	//i2c_write(DS3231_ReadMode_U8);       // connect to DS3231(Read mode) by sending its ID
	MSB = i2c_readAck();                    // read second and return Positive ACK
	LSB= i2c_readNack();                    // read minute and return Positive ACK
	i2c_stop();                           // Stop I2C communication after reading the Date
    return ( MSB + ((LSB >> 6) * 0.25));
	
}

/* Set the first Alarm */
void ds3231_SetFirstAlarm(alarm_t *alarm1)
{
    i2c_start(DS3231_WriteMode_U8);    					    	// Start I2C communication
    i2c_write(DS3231_REG_ALARM_1);       						// Request sec RAM address at 07H

    i2c_write((alarm1->sec) |( ((alarm1->mode )&0x01) <<7 ));	// Write sec from RAM address 08H
    i2c_write((alarm1->min) |( ((alarm1->mode )&0x02) <<7 ));	// Write min from RAM address 09H
    i2c_write((alarm1->hour)|( ((alarm1->mode )&0x04) <<7 ));	// Write hour from RAM address 02H
    
	if(alarm1 -> mode == DS3231_AlarmDateAndTimeMatch) 			//write Date in 0Ah
	i2c_write((alarm1->date)|( ((alarm1->mode )&0x08) <<7 ));   
	else if(alarm1 -> mode == DS3231_AlarmDayAndTimeMatch)		// write Day in 0Ah
	i2c_write( (alarm1 ->weekDay)|(((alarm1->mode)&0x08)<<7)|(1<<6));
    i2c_stop();                              					// Stop I2C communication
}

/* Set the second Alarm */
void ds3231_SetSecondAlarm(alarm_t *alarm2)
{
	i2c_start(DS3231_WriteMode_U8);    					    	// Start I2C communication
    i2c_write(DS3231_REG_ALARM_2);       						// Request sec RAM address at 0BH

	i2c_write((alarm2->min) |( ((alarm2->mode )&0x01) <<7 ));	// Write min from RAM address 0CH
  
	i2c_write((alarm2->hour)|( ((alarm2->mode )&0x02) <<7 ));	// Write hour from RAM address 0DH
    
	if(alarm2 -> mode == DS3231_AlarmDateHourMinutesMatch)		//write Date in 0Eh
	i2c_write((alarm2->date)|((alarm2->mode)&0x04));                 
	else if(alarm2 -> mode == DS3231_AlarmDayHourMinutesMatch)	// write Day in 0Eh
	i2c_write((alarm2->weekDay) |((alarm2->mode)&0x04)|(1<<6) );         
    i2c_stop();                              					// Stop I2C communication

}
uint8_t dec2bcd(char num)
{
	return ((num/10 * 16) + (num % 10));
}

// Convert Binary Coded Decimal (BCD) to Decimal

uint8_t bcd2dec(char num)
{
	return ((num/16 * 10) + (num % 16));
}
