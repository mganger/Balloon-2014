/*
 * analogCal.ino
 * This file is part of Balloon 2014
 *
 * Copyright (C) 2014 - Michael Ganger
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

//This program is designed to test pin A0 (and help too calibrate it)
//It opens the Serial port at 115200 and sends a millisecond timestamp, a pretty
//timestamp, and a reading from the port.

#define PERIOD	1000
#define PIN	A3

#include <Wire.h>
#include "IntersemaBaro.h"

Intersema::BaroPressure_MS5607B baro(true);
unsigned long int pressure;

void printTime(unsigned long int time){
	unsigned long int ms = millis();

	Serial.print(ms / 86400000);			//days
	unsigned long int rm = (ms % 86400000);		//days remainder
	Serial.print(":");

	Serial.print(rm / 3600000);			//hours
	rm      = rm %  3600000;			//hours remainder
	Serial.print(":");


	Serial.print(rm / 60000);
	rm      = rm %    60000;			//minutes remainder
	Serial.print(":");


	Serial.print(rm / 1000);			//seconds


	return;
}

void readPres()
{
	pressure = baro.getHeightCentiMeters();
}

void setup(){
	Serial.begin(115200);
	Serial.print("Intitializing...\n");
	unsigned long int timeLast = 0;
	baro.init();

	for(;;){
		if(millis() - timeLast >= PERIOD){
			timeLast = millis();
			Serial.print("\r\n");
			Serial.print(timeLast);
			Serial.print(",");
			printTime(timeLast);
			Serial.print(",");
			readPres();
			Serial.print(pressure);
		}

		if(Serial.available()){
			char array[50];
			delay(10);
			int number;
			for(int i = 0; Serial.available() && i < 50; i++){
				array[i] = Serial.read();
				number = i+1;
			}
			Serial.write(',');
			Serial.write((byte*)array,number);			
		}
	}
}

void loop(){
	Serial.println("Error: Entered the loop");
}
