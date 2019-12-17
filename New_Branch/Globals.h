#ifndef globals_h
#define globals_h

#define F_CPU 16000000UL
#define Timer_1_PSC 8
#define tau 0.0000005
/* Physical Connections to Sonar module */
#define SonarPort PORTB
#define SonarPin  1

/* Full Swipe Button Connection */
#define ButtonPort PIND
#define ButtonPin  1

/* RTC Interrupt Pin */
#define RTCPort PORTC
#define RTCPin	2

#define TCCR1B_ICES1 0x40

/* Lower limit of battery SOA */
#define Mainvoltage_min 819
#define Backupvoltage_min 553

/* ADC Channels */
#define CHANNEL_MAIN_SUPPLY 0x00
#define CHANNEL_BACKUP_SUPPLY 0x03
#define CHANNEL_LM35_ADJ 0x01

#endif
