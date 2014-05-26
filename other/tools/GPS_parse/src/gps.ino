/*
 * gps.ino
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

//Test program to parse gps data
#include <SoftwareSerial.h>
#define _SS_MAX_RX_BUFF 256 
SoftwareSerial gps(2,3); //Rx,Tx

#define SIZE 100
double latitude;
double longitude;
double time;

//returns true if they are the same up to the max, zero for fail
bool compare(char* array, char* standard, int max){
	for(int i = 0; standard[i] != '\0'; i++){
		if(array[i] != standard[i]){
			return 0;
		}
		if(i == max) break;
	}
	return 1;
}

void readGPS(){
	char array[SIZE];
	//fill with null characters
	for(int i = 0; i < SIZE; i++){
		array[i] = '\0';
	}
	gps.readBytesUntil('$', array, SIZE);
	if(array[0] == '$'){
		if(array[18] == ','){
			Serial.println("No Connection");
		}
	}
	Serial.print("\r\n");
	return;
}

void setup(){
	Serial.begin(115200);
	gps.begin(9600);
//	while(1){
//		if(gps.available()){
//			Serial.write(gps.read());
//		}
//	}
	while(1){
		if(gps.available()){
			readGPS();
		}
	}
}

void loop(){}
