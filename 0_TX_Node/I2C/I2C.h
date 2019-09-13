/*
 * I2c.h
 *
 * Created: 28.08.2019 19:25:04
 *  Author: kai-s
 */ 


#ifndef I2C_H_
#define I2C_H_


/* Initialize I2C */
void I2C_init();

/* Send Start Command */
unsigned char I2C_start();

/* Send Stop Bit */
void I2C_stop();

/* Write Data */
unsigned char I2C_send(unsigned char byte);

/* Send Address on  I2C bus */
unsigned char I2C_send_Address(unsigned char I2C_address, unsigned char rw);


/* Transmit Data to Slave */
void I2C_write(unsigned char I2C_address, unsigned char data);



#endif /* I2C_H_ */