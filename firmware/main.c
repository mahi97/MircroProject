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
#include "morse.h"


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

void apply_btns(unsigned char* btns);
void apply_buzzer(unsigned char* buf, int num);

int main() {

	init();
	lcd_init();
	usart_init();
	adc_init();
	timer_init();
	sei();
	unsigned char btns[3];
	unsigned char buffer[100];
	int j = 0;
	while(1) {
		adc_read(0);
		// PORTC = 0xFF;
		lcd_clear();
		LCD_String("Hello");
		if (usart_recieve() == 0x99) { // A message is started
			int number_of_btns = usart_recieve();
			int i = 0;
			for (i = 0; i < number_of_btns; i++) {
				btns[i] = usart_recieve();
			}
			unsigned char data;
			j = 0;
			while (++j) {
				data = usart_recieve();
				if (data == 0x88) {
					break;
				}
				buffer[j] = data;
			}
		}
		// apply_btns(btns);
		buffer[0] = '.';
		buffer[1] = '-';
		// buffer[2] = '-';
		// buffer[3] = '-';
		// buffer[4] = ' ';
		// buffer[5] = '.';
		// buffer[6] = '-';
		// buffer[7] = '.';
		// buffer[8] = '-';
		// buffer[9] = '.';
		apply_buzzer(buffer, 2);


	}
}

void apply_btns(unsigned char* btns) {
	if (btns[0] == 'T') {

	} else {

	}

	if (btns[1] == 'T') {
		DDRB = 0xFF;
		PORTB = 0x00;
		lcd_init();
		lcd_clear();
	} else {
		DDRB = 0x00;
		PORTB = 0x00;
	}

	if (btns[0] == 'T') {
		PORTC = 0xFF;
		LCD_String("DEBUG");
	} else {
		PORTC = 0x00;
	}
}

void apply_buzzer(unsigned char* buf, int num) {
	int k = 0;
	int unit = 100;
	for (k = 0; k < num; k++) {
		char* m = morse_it(buf[k]);
		int l = 0;

		while (m[l] != '\0') {
			if (m[l] == '.') {
				OCR2 = 255;
				_delay_ms(unit);
			} else if (m[l] == '-') {
				OCR2 = 128;
				_delay_ms(unit*3);
			} else if (m[l] == ' ') {
				OCR2 = 0;
				_delay_ms(unit*2);
			}
			OCR2 = 0;
			_delay_ms(unit);
			l++;
		}
		OCR2 = 0;
		_delay_ms(unit*3);
	}
}
