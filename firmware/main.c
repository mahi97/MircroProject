#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#ifndef F_CPU
#define F_CPU 16000000UL                    // set the CPU clock
#endif

#include "lcd.h"                            // include LCD library
#include "adc.h"
#include "timer.h"
#include "usart.h" 


void init() {
	DDRA = 0x00;
	PORTA = 0x00;

	DDRB = 0xFF; // LCD
	PORTB = 0x00;

	DDRC = 0xFC; // LEDs and Keys
	PORTC = 0x03;

	DDRD = (1<<PD1)  // TXD Usart Output
	     | (1<<PD7); // OC2 TIMER OUTPUT
	PORTD = 0x00;

}

int main() {

	init();
	lcd_init();
	usart_init();
	adc_init();
	timer_init();
	sei();
	while(1) {
	

	}
}

