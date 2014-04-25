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

#include "Borp.h"
#include "Data.h"

void setup(){
	//Constuct data and radio (at 115200 baud)
	Borp radio;
	Data data;

	for(;;){
		//Collects sensor data, indexes the point
		data.readSensorData();
		//Writes point to the SD card. Counts up to 9,999,999 files
		//Currently commented out because it hangs if there is no sd card
//		data.saveData();

		//create an array to be read into
		unsigned long int array[50];
		//read the sensor data into the array
		data.returnData(array);
		//send the array over the Serial port (as ASCII)
		//This needs to be handled on a request basis in the future
		radio.phoneHome(array,POINTSIZE);
		//delete the array to save memory

		//resend data when we have time in between readings
		while((millis() - data.timeSince())<PERIOD){
			long int request = radio.listen();

			//If the request is for a real point, we try to fill it
			//If the request is above 2^31 - 1, it will overflow
			if (request > 0){
				unsigned long int array[POINTSIZE];
				data.returnData(array, request);
			}
			else if(request == -1)		//Nothing to report
				break;
			else if(request == -2)		//Cutdown!!!!!
				digitalWrite(8,HIGH);
			else if(request == -3)		//Kill Radio
				digitalWrite(7,LOW);	//Send radio to Diagnostic mode
			else if(request == -4)		//Temporarily Kill Radio
				sleepRadio();
			else if(request == -5)		//Return Radio to normal function after sleeping
				reviveRadio();

			//Garbage cleanup
			delete[] &request, array;
		}
	}
}

//We leave the loop empty. This makes object creation much easier
void loop(){
	Serial.println("ERROR: Completed setup and entered loop");
	delay(1000);
}
