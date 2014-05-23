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
#define SIZE 14

class Data { 

	public:
		Data();				//Constructor

		unsigned long int dataArray[SIZE];

		unsigned long int timeSince();	//returns time since last collect

		void printData();		//Diagnostics
		bool saveData();		//writes to the SD card
		void readSensorData();		//reads from the sensors

	private:


		//Global variable necessary for Lux Calculations 
//		Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345); 

		void readLUX();
		void readPres();
		void readUV();
		void readHumi();
		void readCO2();
		void readTemp();
		void readO3();
		void readGPS();
		void readMidIR();

		char* tahu(int,char*);

		void reset();					//resets all readings to null
};

#endif
