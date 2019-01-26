#ifndef __MORSE_HEADER__
#define __MORSE_HEADER__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

char* morse_it(unsigned char c) {

	if (c > 96 && c < 123) {
		c -= 32;
	}
	if ((c > 46 && c < 58)
	||  (c > 64 && c < 91)) {
    	switch (c) {
    	case 'A': return ".-  ";
    	case 'B': return "-...  ";
    	case 'C': return "-.-.  ";
    	case 'D': return "-..  ";
    	case 'E': return ".  ";
    	case 'F': return "..-.  ";
    	case 'G': return "--.  ";
    	case 'H': return "....  ";
    	case 'I': return "..  ";
    	case 'J': return ".---  ";
    	case 'K': return "-.-  ";
    	case 'L': return ".-..  ";
    	case 'M': return "--  ";
    	case 'N': return "-.  ";
    	case 'O': return "---  ";
    	case 'P': return ".--.  ";
    	case 'Q': return "--.-  ";
    	case 'R': return ".-.  ";
    	case 'S': return "...  ";
    	case 'T': return "-  ";
    	case 'U': return "..-  ";
    	case 'V': return "...-  ";
    	case 'W': return ".--  ";
    	case 'X': return "-..-  ";
    	case 'Y': return "-.--  ";
    	case 'Z': return "--..  ";
    	case '0': return "-----  ";
    	case '1': return ".----  ";
    	case '2': return "..---  ";
    	case '3': return "...--  ";
    	case '4': return "....-  ";
    	case '5': return ".....  ";
    	case '6': return "-....  ";
    	case '7': return "--...  ";
    	case '8': return "---..  ";
    	case '9': return "----.  ";
    	case ' ': return "     ";
    	default:
    	    break;
    	}
	}
	return "-----";
}

#endif __MORSE_HEADER__