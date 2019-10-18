#include "stdint.h"

/* change mcu_state through button or bt*/
uint8_t switch_state(void);

/* Scroll through statemachines, not changing mcu state*/
uint8_t scroll_state(uint8_t direction);
