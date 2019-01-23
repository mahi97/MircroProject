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

	DDRB = 0x00;
	PORTB = 0x00;

	DDRC = 0x00;
	PORTC = 0x00;

	DDRD = 0x00;
	PORTD = 0x00;


}

int main() {

	init();
	lcd_init();
	usart_init();
	adc_init();
	timer0_init();

	while(1) {
	

	}
}

