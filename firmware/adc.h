#ifndef __ADC_HEADER__
#define __ADC_HEADER__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(ADC_vect)
{ 
	ADCSRA |= 1<<ADSC; // Start Conversion
	// TODO : SHOW Battery level on PORTC
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