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
#define SIZE 18


class Data { 

	public:
		Data();				//Constructor

		unsigned long int dataArray[SIZE];

		unsigned long int timeSince();	//returns time since last collect

		void printData();		//Diagnostics
		void readSensorData();		//reads from the sensors
		void checkDistance();		//checks the time and distance

	private:
		void readGPS();

		long int timeConv(char*);	//converts gps time to seconds
		long int degConv(char*);	//converts gps coordinates to microdegrees
		long int altConv(char*);	//converts gps altitude to mm
		unsigned long int gpsTimeLast;	//the last time we read from the gps

		char* tahu(int,char*);		//itoa for file wrtiting

		void reset();			//resets all readings to null
};

#endif
