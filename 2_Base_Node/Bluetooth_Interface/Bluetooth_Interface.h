#include <stdint.h>

/* This function enables / disables Bluetooth Module*/
void Bluetooth_set_power(uint8_t enable);

/* Get connection state of users */
uint8_t Bluetooth_get_connection_state(void);

/* Write Data to BT Database */
void Bluetooth_write_database(uint8_t data[],uint32_t datarate);

/*  Read Data back from BT Database */
const char* Bluetooth_read_database(void);

/* Set new password */
void Bluetooth_set_password(uint8_t password);

/* Set module mode */
void Bluetooth_set_mode(uint8_t mode);
