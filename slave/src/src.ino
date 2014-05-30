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
#define SIZE 		18		//keep updated with actual number
#define CUTDOWN "Cutdown pin is digital 3"

#include "Data.h"
#include "Borp.h"
#include <SD.h>
#include <SPI.h>

File file;

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
	Serial.println(CUTDOWN);
	Serial.println();

	//Sacred SD code: Bought with many tears
	pinMode(10,OUTPUT);
	SD.begin(10);
	file = SD.open("DATA.TXT",FILE_WRITE);

	//Constuct data object to store points
	Data data;

	for(;;){
		//Collects sensor data, indexes the point
		data.readSensorData();
		//Writes point to the SD card. Counts up to 9,999,999*PACKETSIZE points

		//Function to transmit over radio connection
		broadcast(data.dataArray,SIZE);

		for(int i = 0; i < SIZE; i++)
		{
		        file.print(data.dataArray[i]);
		        file.print(",");
		}
		file.println();
		file.flush();

		cutdown();

		//Pause so data is collected on even time intervals
		while((millis() - data.timeSince())<PERIOD);
	}
}

//We leave the loop empty. This makes object creation much easier
void loop(){
	Serial.println("ERROR: Completed setup and entered loop");
	delay(1000);
}

void cutdown()
{
  if(millis() >30000 && millis()< 60000){
  Serial.print("High!");
  digitalWrite(3,HIGH);
}else if(millis() > 60000)
{
  Serial.print("LOW");
 digitalWrite(3,LOW); 
}
  if(millis() >85000 && millis()< 120000){
  Serial.print("High!");
  digitalWrite(3,HIGH);
}else if(millis() > 120000)
{
  Serial.print("LOW");
 digitalWrite(3,LOW); 
}
}
