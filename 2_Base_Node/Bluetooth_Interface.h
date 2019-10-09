#include <stdint.h>

/* This function enables / disables Bluetooth Module*/
void Bluetooth_set_power(uint8_t enable);

/* Get connection state of users */
uint8_t Bluetooth_get_connection_state(void);

/* Write Data to BT Database */
void Bluetooth_write_database(uint8_t data[],uint32_t datarate);

/*  Read Data back from BT Database */
void Bluetooth_read_database(void);
