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
		int * getData();	//Do we want this to return an array?
		int * getData(int index);
		void setTemp();		//Public methods to set private variables
		void setPres();
		void setAlt();
		void writeData();	//Writes data from the buffer to the disk
	private
		int temp, pres, alt;	//Three possible measurements


Data::Data(int thisTemp, int thisPres, int thisAlt)
{
	temp = thisTemp;
	pres = thisPres;
	alt = thisAlt;
}

Data::Data()		//Overloaded constructors allow for the same function to do different things given different of arguements 
{
	temp = -1;	//We can call an empty data constructor to reset all variables
	pres = -1;
	alt = -1;
}

Data::setTemp()
{
	//take reading from tempPin, store in temp;
	//take reading from presPin, store in pres;
	//take reading from altPin, store in alt;
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
}
