#include "stdint.h"

/* Draw the new state*/
void lcd_redraw_state(uint8_t source, uint8_t state);

/* Redraw time and date*/
void lcd_redraw_time(void);

/* Show an alert on screen*/
void lcd_redraw_alert(void);

/*Show successfull quitation */
void lcd_redraw_quit(void);
