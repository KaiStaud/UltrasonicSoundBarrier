#define F_CPU 16000000UL
#define Timer_1_PSC 8
#define tau 0.0000005
/* Physical Connections to Sonar module */
#define SonarPort PORTB
#define SonarPin  1

#define ButtonPort PIND
#define ButtonPin  1


#define TCCR1B_ICES1 0x40
#define ADC_ADC0 0x00
#define ADC_ADC1 0x01

#define DS3231_Addr 0x68
#define Test_Addr 0x38


/* Sonar Connections */
#define TRIG_PORT PORTB
#define TRIG_PIN  1

/* LED Connections */
#define LED_3_4_PORT PORTB
#define LED_1_2_PORT PORTD
#define LED_1_PIN 5
#define LED_2_PIN 6
#define LED_3_PIN 3
#define LED_4_PIN 4

/* Real Time Clock Connections */
#define RST_PORT PORTC
#define RST_PIN 1

/* User Button Connections */
#define BUTTON_PORT PORTD
#define BUTTON_PIN	2 

/* Hardware Reset Connection */
#define RESET_PORT PORTD
#define RESET_PIN	4

#define Mainvoltage_min 819
#define Backupvoltage_min 553

/* ADC Channels */
#define CHANNEL_MAIN_SUPPLY 0x02
#define CHANNEL_BACKUP_SUPPLY 0x03
#define CHANNEL_LM35_ADJ 0x00
