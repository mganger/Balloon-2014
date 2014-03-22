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
		int * returnData();
		int * returnData(int index);
		void Data();
		void Data(int temp, int pres, int alt);
		void setTempPin(int pin);
		int[] returnData();
		int[] returnData(int index);
		void writeData();

					//Public methods to set private variables
		void setAltiPin(int pin);
		void setHumiPin(int pin);
		void setPresPin(int pin);
		void setTempPin(int pin);
		void setCO2_Pin(int pin);
		void setN2O_Pin(int pin);
		void setCO__Pin(int pin);
		void setIR__Pin(int pin);
		void setUV__Pin(int pin);
		void setO3__Pin(int pin);

		void writeData();				//Writes data from the buffer to the disk
		void setAltPin();

	private:
		int temp, pres, alti;				//Three possible measurements
		short unsigned int tempPin, presPin, altPin, 
