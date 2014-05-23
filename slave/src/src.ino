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

#define PERIOD 		1000/FREQ	//period in milliseconds
#define	FREQ 		10		//frequency of readings in Hz
#define SIZE 		14		//keep updated with actual number
#define CENTER_LAT	41.996243	//latitude of center point
#define CENTER_LONG	77.987309	//longitude of the center point
#define MAXDISTANCE	80000		//distance (in meters) to stay within


#include "Data.h"

int checksum(char * chk)
{
	char a(chk[1]);
	for(int i = 2;chk[i]!='*';i++)
	{
		a = a ^ chk[i];
	}

	return (int)a;
}

double resultant(double lat, double lon){

	double x = (lon - CENTER_LONG) * 111974.434;
	double y = (lat - CENTER_LAT) * 82226.69901;
	return sqrt(x*x + y*y);
}

unsigned int htoi(char * s)
{
	unsigned int val = 0;

	for(int x = 0; x < 2; x++)
	{
		if(val > 255) return 0;
		else if(s[x] >= '0' && s[x] <='9')
		{
		   val = val * 16 + s[x] - '0';
		}
		else if(s[x]>='A' && s[x] <='F')
		{
		   val = val * 16 + s[x] - 'A' + 10;
		}
		else return 0;
	}
	return val;
}

void setup(){
	//Open diagnostics communication
	Serial.begin(115200);
	Serial.println();
	Serial.println();
	Serial.println("Houghton College Science Honors Balloon");
	Serial.println("v0.3.0");
	Serial.println();
	Serial.println("1 Willard Avenue,");
	Serial.println("Hougton, NY 14744");
	Serial.println("585-567-9235");
	Serial.println();


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

		data.printData();

		//Pause so data is collected on even time intervals
		while((millis() - data.timeSince())<PERIOD);
	}
}

//We leave the loop empty. This makes object creation much easier
void loop(){
	Serial.println("ERROR: Completed setup and entered loop");
	delay(1000);
}
