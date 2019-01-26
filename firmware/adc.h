#ifndef __ADC_HEADER__
#define __ADC_HEADER__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void adc_init()
{
    // AREF = AVcc
    ADMUX = (1<<REFS0);
 
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

void adc_read(uint8_t ch)
{
  // select the corresponding channel 0~7
  // ANDing with ’7′ will always keep the value
  // of ‘ch’ between 0 and 7
  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
 
  // start single convertion
  // write ’1′ to ADSC
  ADCSRA |= (1<<ADSC);
 
  // wait for conversion to complete
  // ADSC becomes ’0′ again
  // till then, run loop continuously
  while(ADCSRA & (1<<ADSC));
	switch(((ADC - 600) >> 5) % 8) { // [0~1023] -> [0~8]
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
	}
}

#endif __ADC_HEADER__