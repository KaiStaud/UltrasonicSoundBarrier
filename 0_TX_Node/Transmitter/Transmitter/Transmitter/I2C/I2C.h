/*
 * I2C.h
 *
 * Created: 30.08.2019 20:47:02
 *  Author: kai-s
 */ 
#ifndef I2C_H_
#define I2C_H_

#include "stdint.h"

void I2C_init();
int I2C_read(uint8_t I2C_address);
void I2C_write(uint8_t I2C_address,int data); 


#endif /* PWM_H_ */
