#ifndef __USART_HEADER__
#define __USART_HEADER__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BAUD 9600                           // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)    // set baudrate value for UBRR
 

// function to initialize USART
void usart_init (void)
{
    UBRRH = (BAUDRATE>>8);  // set baud rate high
    UBRRL = BAUDRATE;       // set baud rate low
    UCSRB |= (1 << TXEN)  | (1 << RXEN);  //enable receiver and transmitter
    UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);  // 8bit data format
}
 
// function to send data - NOT REQUIRED FOR THIS PROGRAM IMPLEMENTATION
void usart_transmit (unsigned char data)
{
    while (!( UCSRA & (1<<UDRE)));            // wait while register is free
    UDR = data;                             // load data in the register
}
 
// function to receive data
unsigned char usart_recieve (void)
{
    while(!(UCSRA) & (1<<RXC));  // wait while data is being received
    return UDR;   // return 8-bit data
}

#endif __USART_HEADER__