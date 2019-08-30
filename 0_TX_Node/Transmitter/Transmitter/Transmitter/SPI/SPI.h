/*
 * SPI.h
 *
 * Created: 30.08.2019 21:11:02
 *  Author: kai-s
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "stdint.h"

void SPI_init();
void SPI_write(uint8_t CS,uint8_t data);
uint8_t SPI_read();




#endif /* SPI_H_ */