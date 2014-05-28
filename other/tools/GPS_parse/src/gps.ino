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
char latitude[12];
char longitude[12];
char altitude[12];	//needs null-terminating character
char time[12];

//time coversion, only takes numbers. Returns -1 if it fails
long int timeConv(char* input){
	for(int i = 0; i < 6; i++){
		if((input[i] < 48 ) | (input[i] > 57)) return -1;
	}
	//s + s*10 + m*60 + m*600 + h*3600 + h*36000
	return (input[5]-48) + (input[4]-48)*10 + (input[3]-48)*60 + (input[2]-48)*600 + (input[1]-48)*3600 + (input[0]-48)*36000;
}




//degree conversion
long int degConv(char* input){
	for(int i = 0; i < 9; i++){
		if(input[i] == '.') continue;
		if((input[i] < 48 ) | (input[i] > 57)) return -1;
	}
	//in microdegrees
	long int degree = 1000000*(input[0]-48)*10 + (input[1]-48);
	degree += 10000000*(input[2]-48)/60 + 1000000*(input[3]-48)/60 + 100000*(input[5]-48)/60 + 10000*(input[6]-48)/60 + 1000*(input[7]-48)/60 + 100*(input[8]-48)/60;
	return degree;
}


//altitude conversion to decimeters
long int altConv(char* input){
	int decimal = 0;
	long int multiplier = 10;
	for(int i = 0; i < 9; i++){
		if(input[i] == '.'){
			decimal = i;
			break;
		}
		if((input[i] < 48 ) | (input[i] > 57)) return -1;
	}
	if((input[decimal+1] < 48 ) | (input[decimal+1] > 57)) return -1;


	long int altitude = (input[decimal+1] - 48);
	for(int i = decimal-1; i > 0; i--){
		altitude += (input[i]-48)*multiplier;
		multiplier *= 10;
	}

	return altitude*100;
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

int getline(char* input, char* output, char delim){
	for(int i = 0; i < SIZE; i++){
		if(input[i] != delim){
			output[i] = input[i];
			continue;
		}
		return i+1;
	}
}

int getline(char* input, char delim){
	for(int i = 0; i < SIZE; i++){
		if(input[i] != delim){
			continue;
		}
		return i+1;
	}
}

void readGPS(){
	char array[SIZE];
	char checksum[2];
	//fill with null characters
	for(int i = 0; i < SIZE; i++){
		array[i] = '\0';
	}
	

	//get a line
	gps.readBytesUntil('$', array, SIZE);
	memset(array,SIZE,'\0');
	int number = gps.readBytesUntil('*',array,SIZE);
	char check = array[0];
	for(int i = 1; i < number; i++){
		check = check ^ array[i];
	}
	gps.readBytes(checksum,2);

	//check to see if we want these points
	if(check != htoi(checksum)){
		return;
	}

	if(array[3] != 'G'){
		return;
	}
	if(array[18] == ','){
		return;
	}

	memset(time,12,0);
	memset(altitude,12,0);
	memset(longitude,12,0);
	memset(latitude,12,0);
	//GPGGA
	int total = getline(array,',');
	int count = total;
	//time
	count = getline(&array[total],time,',');
	total += count;
	//latitude
	count = getline(&array[total],latitude,',');
	total += count;
	//N
	count = getline(&array[total],',');
	total += count;
	//longitude
	count = getline(&array[total],longitude,',');
	total += count;
	//W
	count = getline(&array[total],',');
	total += count;
	//1
	count = getline(&array[total],',');
	total += count;
	//8
	count = getline(&array[total],',');
	total += count;
	//1.14
	count = getline(&array[total],',');
	total += count;
	//altitude
	count = getline(&array[total], altitude,',');
	//M
	//-34.0
	//M
	//<blank>
}

void setup(){
	Serial.begin(115200);
	Serial.println("reset");
	gps.begin(9600);
	gps.listen();
	Serial.println("gps begin");
}

void loop(){
	if(gps.available()){
		readGPS();
		Serial.println(timeConv(time));
		Serial.println(degConv(latitude));
		Serial.println(degConv(&longitude[1]));
		Serial.println(altConv(altitude));
	}

}
