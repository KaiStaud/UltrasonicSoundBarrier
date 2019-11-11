/* official c headers */
#include <stdint.h>

/* Create new timestamp */
void save_timestamp(char* timestamp);

/* Load timestamp from memory */
uint8_t* load_timestamp(uint8_t i);

/* Delete all written variables -> 255 */
void clear_eeprom(void);

/* Return the complete memory */
void return_eeprom(void);

/* Transfer a current timestamp to RTC */
void transfer_timestamp(void);
