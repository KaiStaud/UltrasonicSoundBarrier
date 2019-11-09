/* official c headers */
#include <stdint.h>

/* Create new timestamp */
void save_timestamp(char* timestamp);
/* Load timestamp from memory */
void load_timestamp(uint8_t i);
/* Delete all written variables -> 255 */
void clear_eeprom(void);

