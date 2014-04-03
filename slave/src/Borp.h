/*
 * Borp.h - Library for sending data from an Arduino over a serial connection, 
 * specifically designed for the Arudino Due and MM2 radio chips.
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


#ifndef Borp_h		//Checks to see if this library has been included already
#define Borp_h		//This ensures that it is not inlcuded twice


class Borp
{

	public:

		//constuctor initializes the Serial communication. Pin refers to 
		//which Serial it uses (Serial1, Serial2, Serial3, etc)
		Borp(int pin, int baud);

		//This function takes an array (from the data class) and sends it
		void phoneHome(unsigned char data);

		//This is used to test the transmission
		void testTransmission(int num);
	private:
		int pin;					//Stores the Serial pin (i.e. tx3)
		int baud;					//Stores the baud rate.
};

#endif			//Ends check for included libraries

