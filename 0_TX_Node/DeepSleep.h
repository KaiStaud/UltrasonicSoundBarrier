/*
 * DeepSleep.h
 *
 * Created: 24.08.2019 16:18:07
 *  Author: kai-s
 */ 


#ifndef DEEPSLEEP_H_
#define DEEPSLEEP_H_

#define IDLE				0x00
#define POWER_DOWN			0x02
#define POWER_SAVE			0x03
#define STANDBY				0x07
#define EXTENDED_STANDBY	0x08

void set_mode(uint8_t sleep_mode);
void external_wakeup(void);




#endif /* DEEPSLEEP_H_ */