/*
 * Data.h
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



#include <getData.h>

class Data { 

	public:
		int * getData();		//Do we want this to return an array? Yes
		int * getData(int index);
		void setTemp();			//Public methods to set private variables
		void setPres();
		void setAlt();
		void writeData();		//Writes data from the buffer to the disk
	//Stores the pin used by each of the sensors
	//Should be defined in the slave code for simplicity
	//Expand as neccessary (maybe we can dynamically assign variables?)
		short unsigned int tempPin, presPin, altPin
	private
		int temp, pres, alt;		//Three possible measurements


Data::Data(int Temp, int Pres, int Alt)
{
	_temp = Temp;
	_pres = Pres;
	_alt = Alt;
}

Data::Data()
{

	alt = -1;
}

Data::setTemp()	//This needs a better name, maybe readSensor()?
{
	// underscore + Capital letter is bad practice, apparently.
	//need to change to lowercase
	//take reading from tempPin, store in temp
	_temp = analogRead(tempPin);
	//take reading from presPin, store in pres
	_pres = analogRead(presPin);
	//take reading from altPin, store in alt
	_alt = analogRead(altPin);
}

Data::getData()
{
	//Parse all data as an array of concatenated ints
	//We need an array because the data will be very long
	//The largest data type is a "long long"-64bit
	//64 bits of resolution would give us 5 sensors at 12 bits of resolution.
}

Data::getData(int index)
{
	//Checks to see if current index is in the buffer
	//Load data from disk into the buffer,then return parsed data
}

Data::writeData()
{
	//Writes data from buffer to Disk
	if (!SD.begin(4))			//tests for SD card on 50, 51, 52, and 4
							//4 is the chip select line
							//connects to pins 11, 12, 13, and 4 on unos
	{
	Serial.println("SD initialization failed.");		//Prints fail for testing
	return;
	}				//Should this snippet of code go in the setup of slave?

	// On the Ethernet Shield, CS is pin 4. It's set as an output by default.
	// Note that even if it's not used as the CS pin, the hardware SS pin 
	// (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  	// or the SD library functions will not work. 
	pinMode(10, OUTPUT);	//supposedly, this is neccessary for the code
}
