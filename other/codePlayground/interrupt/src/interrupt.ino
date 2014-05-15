//This program is desinged to only test the interrupt functions of the Arduino
//It only blinks a light

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TimerOne.h"
 
#define LEDPIN 13

//global variable to switch the pin
bool switcheroo = HIGH;

void switchPin(){

	digitalWrite(LEDPIN,switcheroo);
	switcheroo = !switcheroo;

}

void setup(){

	pinMode(LEDPIN, OUTPUT);
	//setup the timer and interrupts
	Serial.begin(115200);
	Timer1.initialize(1000000); //Call interrupt every 1000ms
	Timer1.attachInterrupt(switchPin);
	Timer1.start();




//	//initialization blinking
//	for(int i = 0; i<1000; i++){
//		digitalWrite(LEDPIN,switcheroo);
//		switcheroo = !switcheroo;
//		delay(100);
//	}

	//other way to change the pin output value
//	DDRB = B10000000;
//	PORTB = B11111111;

	//// initialize Timer1
	//cli();             // disable global interrupts
	//TCCR1A = 0;        // set entire TCCR1A register to 0
	//TCCR1B = 0;
 
	// enable Timer1 overflow interrupt:
	//TIMSK1 = (1 << TOIE1);
	// Set CS10 bit so timer runs at clock speed:
	//TCCR1B |= (1 << CS10);
	// enable global interrupts:
	//sei();


}

void loop(){}
