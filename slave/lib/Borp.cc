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

 




//Constructor for Borp declares what pin the serial connection to the radio is 
//and and the baud rate to be used in transmission.
//Baud rate should be the lowest baud rate required to transmit the amount of 
//data we are collecting. Baud rates that are too high can max out the 
//processing power of the Arduino and ultimately slow transmissions down.

Borp::Borp(int pin, int baud)		
{
	Serial.begin(baud);	
	pinMode(pin,OUTPUT);
}

void Borp::phoneHome(int* data)			//takes an array
{
	//Calculate MD5 Hash, then broadcast the hash as well as the data itself.
	unsigned char* hash = MD5::make_hash((char*)data);
	Serial.write(hash);
	Serial.write(data,sizeof(data) / sizeof(data[0]));
}

void Borp::testTransmission(int num)
{
	Serial.println(num);
}
