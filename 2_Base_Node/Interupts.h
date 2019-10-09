#include "stdint.h"

/* Shared Variables for HMI */
extern volatile int update_UI_flag ;
extern volatile int State_position ;
extern volatile int current_state  ;

/* Function Prototypes */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
