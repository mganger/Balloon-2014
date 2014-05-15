//This program is desinged to only test the interrupt functions of the Arduino
//It only blinks a light

#include <avr/io.h>
#include <avr/interrupt.h>
 
#define LEDPIN 2

void setup(){
	pinMode(LEDPIN, OUTPUT);

	// initialize Timer1
	cli();             // disable global interrupts
	TCCR1A = 0;        // set entire TCCR1A register to 0
	TCCR1B = 0;
 
	// enable Timer1 overflow interrupt:
	TIMSK1 = (1 << TOIE1);
	// Set CS10 bit so timer runs at clock speed:
	TCCR1B |= (1 << CS10);
	// enable global interrupts:
	sei();


}

void loop(){}
