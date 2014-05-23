/*
 * src.ino
 * This file is part of Balloon 2014
 *
 * Copyright (C) 2014 - Houghton College Science Honors
 *
 * Balloon 2014 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Balloon 2014 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Balloon 2014. If not, see <http://www.gnu.org/licenses/>.
 */

//This program tests the gps, sd card, and radios.

#include <SoftwareSerial.h>
#include <SD.h>

#define CHIPSELECT 10

void setup(){
	Serial.begin(9600);
	Serial.println();
	Serial.println("Serial communications open");

	SoftwareSerial gps(2, 3); //Rx,Tx
	gps.begin(9600);
	Serial.println("GPS serial communications open");
	while(!gps.isListening()){}
	Serial.println("GPS is online");

	//Check to see if the SD card is open
	while(!SD.begin(CHIPSELECT)) {
		Serial.println("Card failed, or not present");
		delay(1000);
	}
	Serial.println("SD card opened");

	//Create the file
	char filename[] = "A.LOG";
	while(SD.exists(filename)){
		filename[0]++;
	}
	File dataFile = SD.open(filename, FILE_WRITE);
	dataFile.println();
	dataFile.println();
	dataFile.println("-------------------");
	dataFile.println();
	Serial.print("Writing to ");
	Serial.println(filename);
	Serial.println();

	char tmp;
	char packet[257];
	unsigned long int timeLast = millis();
	while(1){
		memset(packet,'\0',257);
		for(int i = 0; i < 256;){
			if(gps.available()){
				tmp = gps.read();
				packet[i] = tmp;
				UDR0 = tmp;
				i++;
			}
		}
		dataFile.print(packet);
		dataFile.flush();
	}
}

void loop(){}
