#include <stdint.h>
/*Initialize the RTC Time at startup */
void init_time(void);

/* Initialize the first two alarms */
void init_alarms(void);

/* Extract time data from user input */
void string_to_int(uint8_t* time);
