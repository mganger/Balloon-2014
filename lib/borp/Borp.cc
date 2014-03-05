/*
Borp.cc - Library for sending data from an Arduino over a serial connection, specifically developed for the Arduino Due and MM2 radio chips.
Balloon Over Radio Protocl (B.O.R.P)
Created by Houghton College Science Honors program 2014
*/

#include "Arduino.h" 		//Includes all the standard Arduino Libraries
#include "borp.h"		//Includes header file for B.O.R.P. Libraries


//Constructor for Borp declares what pin the serial connection to the radio is and and the baud rate to be used in transmission.
//Baud rate should probably be 115200, as it is the highest rate that the Arduino can handle. It is also a viable option according to version 1.6 of the MM2 manual.  
Borp::Borp(int pin, int baud)		
{
	Serial.begin(baud);	
	pinMode(pin,Output); 
	_pin = pin;
	actualPin = pinConvert();		//still needs to be declared somewhere. actualPin is hex for something like 0x80, and we can directly modify the value (see writeData)
						//pinConvert can be used to convert the pin numbers (ie pin 13, 10, 4) to the registry values by some sort of mapping we design for the due. 
	writeData::writeData(struct data, int actualPin);
}

//Borp::phoneHome(struct data)
//{
//	Serial.write(data.temperature); //this is incorrect. Serial writes to USB. We need to go to the digital pins
//	Serial.write(data.pressure);
//	Serial.write(data.altitude);
//}

Borp::testTransmission(int num)
{
	Serial.write(num);
}
