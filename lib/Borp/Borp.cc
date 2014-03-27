/*
 * Borp.cc - Library for sending data from an Arduino over a serial connection,
 * specifically developed for the Arduino Due and MM2 radio chips.
 * Balloon Over Radio Protocl (B.O.R.P)
 * Created by Houghton College Science Honors program 2014
 *
 * Borp.cc
 * This file is part of Borp
 *
 * Copyright (C) 2014 - Houghton College Science Honors
 *
 * Borp is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Borp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Borp. If not, see <http://www.gnu.org/licenses/>.
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
	writeData::writeData(struct data, int actualPin);
}

Borp::phoneHome(Data point)
{
	Serial.write(point.temperature); 
	Serial.write(point.pressure);
	Serial.write(point.altitude);
}

Borp::testTransmission(int num)
{
	Serial.write(num);
}
