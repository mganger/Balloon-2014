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
#include "AltSoftSerial.h"
AltSoftSerial gps;
#include <stdlib.h>

#define SIZE 100
double latitude;
double longitude;
double altitude;
double time;

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

void readGPS(){
	char array[SIZE];
	char checksum[3] = "\0\0";
	//fill with null characters
	for(int i = 0; i < SIZE; i++){
		array[i] = '\0';
	}
	
//	//get a line
//	for(int i = 0; (gps.read() != '$') & (i < SIZE); i++);
//	int number = gps.readBytesUntil('*',array,SIZE);
//	gps.readBytesUntil('\r',checksum,2);
//	Serial.println(array);

	//get a line
	char tmp;
	char check = '\0';
	while(gps.available()){
		tmp = gps.read();
		if(tmp == '$') break;
	}

	int i = 0;
	for(int i = 0; i < SIZE; i++){
		tmp = gps.read();
		if(tmp == '*') break;
		check = check ^ tmp;
		array[i] = tmp;
	}
	if(array[3] == 'G') return;
	
		

	//check to see if we want these points
	if(check != htoi(checksum)){
		return;
	}
	if((array[3] != 'G') & (array[18] == ',')){
		return;
	}
	Serial.println(array);

	char degreearray[] = "\0\0";
	char minutearray[] = "\0\0";
	char deciminutearray[] = "\0\0\0\0";
	char altiarray[] = "\0\0\0\0\0\0\0";

	//if all's well, update the latitude and longitude
	//latitude
	degreearray[0] = array[18];
	degreearray[1] = array[19];
	minutearray[0] = array[20];
	minutearray[1] = array[21];
	deciminutearray[0] = array[23];
	deciminutearray[0] = array[24];
	deciminutearray[0] = array[25];
	deciminutearray[0] = array[26];

//	latitude = (atoi(degreearray)*60000 + atoi(minutearray)*10000 + atoi(deciminutearray))/(double)60000;



	//longitude
	degreearray[0] = array[31];
	degreearray[1] = array[32];
	for(int i = 0; i < 7; i++){
		minutearray[i] = array[i+33];
	}
//	longitude = (atoi(degreearray)*60000 + atoi(minutearray)*10000 + atoi(deciminutearray))/(double)60000;


	//altitude
//	for(int i = 0; array[i+52] != ','; i++){
//		altiarray[i] = array[i+52];
//	}
//	altitude = atof(altiarray);
}

void setup(){
	Serial.begin(115200);
	Serial.println("reset");
	gps.begin(9600);
	gps.listen();
	Serial.println("gps begin");
	while(1){
		if(gps.available()){
			UDR0 = gps.read();
		}
	}
}

void loop(){
	if(gps.available()){
		readGPS();
//		Serial.print("Latitude:  ");Serial.println(latitude);
//		Serial.print("Longitude: ");Serial.println(longitude);
//		Serial.print("Altitude:  ");Serial.println(altitude);
//		Serial.println();
	}
//	Serial.print('-');
}
