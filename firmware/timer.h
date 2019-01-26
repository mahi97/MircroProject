#ifndef __TIMER_HEADER__
#define __TIMER_HEADER__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void timer_init() {
  TCCR2 |= (1<<WGM20) | (1<<WGM21); //select Fast PWM mode 
            
  TCCR2 |= (1<<COM21) //clear OC2 on compare match
        |  (1<<CS20) | (1<<CS21) | (1<<CS22); //Clock Prescaler is 1024

  OCR2 = 0;
}

#endif __TIMER_HEADER__