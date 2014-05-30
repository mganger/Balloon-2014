/*
 * sd_gps.ino
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

#include <SPI.h>
#include <SD.h>

File file;
char array[300];

void setup(){
	Serial.begin(9600);
	pinMode(10,OUTPUT);
	SD.begin(10);
	file = SD.open("GPSLOG.TXT",FILE_WRITE);
	memset(array,0,300);
	for(;;){
		for(int i = 0;Serial.available(); i++){
			array[i] = Serial.read();
		}
		file.flush();
	}
}

void loop(){}
