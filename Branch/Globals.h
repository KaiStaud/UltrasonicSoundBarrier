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

#define TCCR1B_ICES1 0x40

/* Sonar Connections */
#define TRIG_PORT PORTB
#define TRIG_PIN  1

/* Lower limit of battery SOA */
#define Mainvoltage_min 819
#define Backupvoltage_min 553

/* ADC Channels */
#define CHANNEL_MAIN_SUPPLY 0x00
#define CHANNEL_BACKUP_SUPPLY 0x03
#define CHANNEL_LM35_ADJ 0x01

#endif
