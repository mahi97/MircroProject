#ifndef __ADC_HEADER__
#define __ADC_HEADER__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(ADC_vect)
{ 
	ADCSRA |= 1<<ADSC; // Start Conversion
	while(ADCSRA & (1<<ADSC));
	uint16_t i = ADC;
	switch(i >> 7) { // [0~1023] -> [0~8]
		case 0:
			PORTC = 0x07; // 0000 0111
		break;
		case 1:
			PORTC = 0x07; // 0000 0111
		break;
		case 2:
			PORTC = 0x0F; // 0000 1111
		break;
		case 3:
			PORTC = 0x1F; // 0001 1111
		break;
		case 4:
			PORTC = 0x3F; // 0011 1111
		break;
		case 5:
			PORTC = 0x7F; // 0111 1111
		break;
		case 6:
			PORTC = 0x7F; // 0111 1111
		break;
		case 7:
			PORTC = 0xFF; // 1111 1111
		break;
		default:
			PORTC = 0x03;
		break;
	}

}

void adc_init() {
	ADCSRA = (1 << ADEN)  // Enable the ADC
		   | (1 << ADIE)  //interrupt feature
		   | (1 << ADATE) // Enable auto trigger
		   | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // set the ACD clock pre-scalar to clk/128
	ADMUX = (1 << REFS0) | (1 << REFS1) // Select internal 2.56V as Vref,
	      | (1 << ADLAR);   // left justify data registers
	      //select ADC0 as input channel
	SFIOR &= (0x0F); // Free Running and Not High Speed Mode
}

#endif __ADC_HEADER__