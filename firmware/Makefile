all:
	~/avr/bin/avr-gcc -g -Os -Wall -mmcu=atmega16 -c -o main.o main.c
	~/avr/bin/avr-gcc -g -Os -Wall -mmcu=atmega16 main.o -o main.obj
	~/avr/bin/avr-objcopy -R .eeprom -O ihex main.obj main.hex

install:
	#avrdude -c stk500 -p m16 -U flash:w:main.hex:i -P /dev/tty.usbserial
	avrdude -c usbasp -p m16 -U flash:w:main.hex:i
