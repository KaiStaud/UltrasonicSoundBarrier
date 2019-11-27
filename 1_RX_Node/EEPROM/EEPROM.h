/* official c headers */
#include <stdint.h>

/* Create new timestamp */
void save_timestamp(uint8_t h, uint8_t m, uint8_t s, uint8_t alarm_num);

/* Load timestamps from memory */
void load_timestamps(uint8_t* alarms);

/* Delete all written variables -> 255 */
void clear_eeprom(void);

/* Return the complete memory */
void return_eeprom(void);

/* Transfer a current timestamp to RTC */
void transfer_timestamp(void);
