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


class Data { 

	public:
		Data();				//Constructor

		unsigned long int dataArray[10];

		unsigned long int timeSince();	//returns time since last collect

		void returnData(unsigned long int* dataArray);			//returns a pointer to an array of
		void returnData(unsigned long int * dataArray, unsigned long int index);	//newest or specified index

		void saveData();				//writes to the SD card
		void readSensorData();				//reads from the sensors

	private:

		unsigned long int timeCollect;	//milliseconds

		unsigned long int pres, alti, LUX, UV, IR;		//Private variables to hold sensor
		unsigned long int temp, humi, CO2, O3;			//values for different measurements

		unsigned long int index;		//Holds current collection index

		//Global variable necessary for Lux Calculations 
//		Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345); 

		void setupLUX();
		void readLUX();	
		void readAlti();
		void readPres();
		void readUV();	
		void readIR();	
		void readHumi();
		void readCO2();
		void readTemp();
		void readO3();
		void readGPS();

		void reset();					//resets all readings to null
};

#endif
