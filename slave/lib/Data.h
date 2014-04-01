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

#ifndef __DATA_H_INCLUDED__		//If this library is not defined..
#define __DATA_H_INCLUDED__		//Define this variable and read the code
							//Otherwise, go to the bottom (and skip)
							//This is to prevent defining it twice

class Data { 

	public:
		Data();						//Constructor

		unsigned long int timeCollect;	//milliseconds, collection time

		void returnData(int* dataArray);				//returns a pointer to an array of
		int * returnData(int * dataArray, int index);	//newest or specified index

		void saveData();				//writes to the SD card
		void readSensorData();			//reads from the sensors


		void setAltiPin(int pin);		//Public methods to set 
		void setHumiPin(int pin);		//private variables
		void setPresPin(int pin);		//They only accept valid pins 0-64
		void setTempPin(int pin);
		void setCO2_Pin(int pin);
		void setN2O_Pin(int pin);
		void setCO__Pin(int pin);
		void setIR__Pin(int pin);
		void setUV__Pin(int pin);
		void setO3__Pin(int pin);

	private:
		int temp, pres, alti, humi;		//Private variables to hold sensor
		int CO2_, CO__, N2O_, UV__, O3__;	//values for different measurements


		//TODO If we put these in an array, it will be easier to set things up
		int tempPin, presPin, altiPin;	//Private variables to hold the pin
		int humiPin, CO2_Pin, CO__Pin;	//for each sensor
		int N2O_Pin, UV__Pin, O3__Pin;

		unsigned long int index;			//Holds current collection index


		void readTemp(int pin);			//these functions should be private
		void readAlti(int pin);			//and called by readSensorData()
		void readHumi(int pin);			//Each group should customize that
		void readPres(int pin);			//funciton to only call the needed
		void readCO2_(int pin);			//read****() for their project
		void readN2O_(int pin);
		void readCO__(int pin);
		void readIR__(int pin);
		void readO3__(int pin);

		void reset();					//resets all readings to null
} point;								//defines the object point

#endif
