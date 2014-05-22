/*
 * slave.cc
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

#define PERIOD 1000/FREQ			//period in milliseconds
#define FREQ 10					//frequency of readings
#define SIZE 14					//keep updated with actual number

#include "Data.h"

void setup(){
	//Constuct data object to store points
	Data data;

	for(;;){
		//Collects sensor data, indexes the point
		data.readSensorData();
		Serial.println("Read the sensor data"); //TODO
		//Writes point to the SD card. Counts up to 9,999,999*PACKETSIZE points
		if(!data.saveData()){
			Serial.println("Data saved"); //TODO
		}

		//create an array to be read into
		unsigned long int array[50];
		//read the sensor data into the array
		data.returnData(array);

		//Pause so data is collected on even time intervals
		while((millis() - data.timeSince())<PERIOD){
		}
	}
}

//We leave the loop empty. This makes object creation much easier
void loop(){
	Serial.println("ERROR: Completed setup and entered loop");
	delay(1000);
}
