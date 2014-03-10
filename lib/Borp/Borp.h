/*
* Borp.h - Library for sending data from an Arduino over a serial connection, specifically designed for the Arudino Due and MM2 radio chips.
* Balloon Over Radio Protocol (B.O.R.P)
* Created by Hougthon College Science Honors program 2014
* 
* Borp.h
* This file is part of <program name>
*  Copyright (C) 2014 - Michael Ganger
*  <program name> is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*  <program name> is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*  You should have received a copy of the GNU General Public License
* along with <program name>. If not, see <http://www.gnu.org/licenses/>.
 */



*/

#ifndef Borp_h		//Checks to see if this library has been included already
#define Borp_h		//This ensures that it is not inlcuded twice

//#include "Arduino.h"	//includes standard arduino libraries

class Borp
{

	public:
		Borp(int pin, int baud);		//The constructor initializes the borp, it has to have the same name as the class
		void phoneHome(struct data);		//This will be the function that actually pipes data to the radio
		void testTransmission(int num);		//This can be used to test the radios until we build our struct data;
	private:
		int pin;				//Stores what pin the serial radio is connected to
		int baud;				//Stores the defined baud rate.
};

#endif			//Ends check for included libraries

