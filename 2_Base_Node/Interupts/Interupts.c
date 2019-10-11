#include "main.h"
#include "Interupts.h"

#define UI_Start = 0;
#define UI_End = 6;

/* Shared Variables  with main.c */
volatile int update_UI_flag = 0;
volatile int State_position =0;
volatile int current_state = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{	/* Set Flag -> update UI */
	update_UI_flag = 1;
	
	if(GPIO_Pin == B1_Pin)
			State_position++;
		
	else if(GPIO_Pin == Incremental_Encoder_Edge1_Pin )
	{
		/* Detect clockwise Rotation */
		if(GPIOA -> IDR & GPIO_IDR_IDR4)
		{
			GPIOA -> ODR ^= 1<<5;
			State_position++;

		}
		/* Detect counter-clockwise Rotation */
		else
		{
			GPIOA -> ODR ^= 1<<5;
			State_position--;
		}
	}
	/* Switch to new Mode */
	else if(GPIO_Pin == Incremental_Encoder_Button_Pin)
  {
		current_state = State_position;
	}
	/* Prevent unused argument(s) compilation warning */
  //UNUSED(GPIO_Pin);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}
