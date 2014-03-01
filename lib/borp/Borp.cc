/*
Borp.cc - Library for sending data from an Arduino over a serial connection, specifically developed for the Arduino Due and MM2 radio chips.
Balloon Over Radio Protocl (B.O.R.P)
Created by Houghton College Science Honors program 2014
*/

#include "Arduino.h" 		//Includes all the standard Arduino Libraries
#include "borp.h"		//Includes header file for B.O.R.P. Libraries

Borp::Borp(int pin)		//Constructor for Borp declares what pin the serial connection to the radio is and and the baud rate to be used in transmission.
{
	Serial.begin(115200);		
	pinMode(pin,Output);		//Declares the baud rate to be used in transmission. 
	_pin = pin;			//I picked 115,200 baud because it was the highest rate 
					//that Arduino can handle. It is also a viable option 
					//according to version 1.6 of the MM2 manual. We could make
					//Baud Rate a variable that is passed to the BORP constructor.
}

Borp::phoneHome(struct data)
{
	Serial.write(data.temperature);
	Serial.write(data.pressure);
	Serial.write(data.altitude);
}

Borp::testTransmission(int num)
{
	Serial.write(num);
}
