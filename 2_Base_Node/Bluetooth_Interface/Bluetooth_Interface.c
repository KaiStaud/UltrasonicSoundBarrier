#include <stdio.h>
#include <string.h>

#include "main.h"
#include "stm32f1xx_hal_uart.h"

uint8_t battery_charge= 0;
char *detection[3] = {"Blocked!","--Free--","Testmode"};

/* This function enables / disables Bluetooth Module*/
void Bluetooth_set_power(uint8_t enable)
{
	if(enable)
		HAL_GPIO_WritePin(BT_Enable_GPIO_Port, BT_Enable_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(BT_Enable_GPIO_Port, BT_Enable_Pin, GPIO_PIN_RESET);
}	

/* Get connection state of users */
uint8_t Bluetooth_get_connection_state(void)
{
	uint8_t connection_state= 0;
	
	connection_state = HAL_GPIO_ReadPin(BT_Connection_GPIO_Port,BT_Connection_Pin);
	
	return connection_state;

}	

/* Write Data to BT Database */
void Bluetooth_write_database(uint8_t data[], uint32_t datarate)
{	uint8_t length=0;
	uint16_t Size = 30;
	uint32_t Timeout =30;
	/* Before Transmitting: Calculate Size and Timeout of Message */
	while(data[length] != '\0')
	{	
		//USART1 -> DR = data[length];
		//while(!(USART1 ->SR & USART_SR_TC));
		length++;
	}
		/* Calculate Timeout : x Bits = Data+ Parity+ Start+Stop  = N+4
			Timeout = x Bits / Baudrate *1000  -> Timeout = (length)/datarate *10000*/
	Timeout = length*10000/datarate;
	HAL_UART_Transmit(&huart1,data,Size,Timeout);
}

/*  Read Data back from BT Database */
const char* Bluetooth_notify_database(void)
{	
	
}

/* Set new password */
void Bluetooth_set_password(uint8_t password)
{	char at_command[12] = "AT+PIN";
	char pin[]= "0000";
	/* Create String from uint8_t password */
	sprintf(pin,"%d",password);
	/* add password to at command */
	strcat(at_command,pin);
	/* Write AT Command */
	HAL_UART_Transmit(&huart1,(uint8_t*)at_command,14,10);
}	
/* Set module mode */
void Bluetooth_set_mode(uint8_t mode)
{
}
