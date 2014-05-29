/*
 * Data.cc
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
#define INIT -1
#define PACKETSIZE 1000

//Array definitions
#define INDEX 		0
#define TIMECOLLECT 	1
#define TEMP 		2
#define PRES 		3
#define HUMI 		4
#define CO2 		5
#define UV 		6
#define O3 		7
#define IRUP 		8
#define IRDOWN 		9
#define VISUP 		10
#define VISDOWN 	11
#define MIDIRUP 	12
#define MIDIRDOWN 	13
#define GPS_LAT		14
#define GPS_LONG	15
#define GPS_ALT		16
#define GPS_TIME	17

#include "Data.h"
#include "Arduino.h"
#include "global.h"
#include "SPI.h"		//Library for SPI communications
#include "SD.h"			//Library for SD  communications
#include "IntersemaBaro.h"	//Library for altimeter data
#include "Adafruit_Sensor.h"	//Library for Adafruit sensors
#include "Wire.h"		//Library for i2c communication
#include "TSL2561.h"		//Library for digital luminosity/lux sensor
#include "Adafruit_TMP006.h"	//Library for non-contact temperature sensing
#include "AltSoftSerial.h"	//Improved Software Serial communications


//Global declaration of the alt softserial
AltSoftSerial gps; //(8=Rx,9=Tx)


//Global variable necessary for Lux Calculations
//Adafruit_TSL2561_Unified tsl3 = Adafruit_TSL2561_Unified(TSL2561_ADDR_GROUND, 12345);
Intersema::BaroPressure_MS5607B baro(true);

//create the ir sensor objects
Adafruit_TMP006 ir(0x40);		//bottom ir sensor with address 0x40  [GND,GND]
Adafruit_TMP006 ir2(0x44);		//top ir sensor with address 0x44 [VCC,GND]

//create lux sensor objects
TSL2561 lux(0x29);		//lux
TSL2561 lux2(0x39);		//lux


//******************************************************************************
//Constructor, reset, init

Data::Data(){
	File initFile;
	pinMode(10,OUTPUT);	//set Digital 10 to CS for SD card
	gps.begin(9600);
//	gps.setTimeout(1000);
//	if(!SD.begin(10)){
//		Serial.println("The SD reader has failed or is not present");
//	}
//	else{
		Serial.println("CREATING STARTUP LOG FILES");
//		initFile = SD.open("start.log",FILE_WRITE);
		if(!initFile){
			Serial.println("Could not create startup file");
		}else{
		initFile.println();
		initFile.println();
		initFile.println("---------------");
		initFile.print("Time since boot: ");
		initFile.println(micros());
		initFile.print("GPS Status: ");
		//Check to see what i2c sensors are ready
		initFile.flush();
		initFile.close();
		}
//	}
	memset(dataArray,INIT,SIZE*4);
	Serial.println("Initialized Array");
	dataArray[INDEX] = 0;
	//initialize the pressure sensor
}

void Data::reset(){
	//Set the readings to sentinal value
	memset(&dataArray[TIMECOLLECT+1],INIT,(12)*4);
	dataArray[INDEX]++;
}

//******************************************************************************
//Functions for reading the data

void Data::readSensorData()
{
	reset();
	dataArray[TIMECOLLECT] = millis();


//GPS
	readGPS();


//Analog
	dataArray[CO2] = analogRead(0);
	dataArray[TEMP] = analogRead(1);
	dataArray[HUMI] = analogRead(2);
	dataArray[UV] = analogRead(2);
	dataArray[O3] = analogRead(3);


//Pressure
	baro.init();
	dataArray[PRES] = baro.getPressure();


//IR sensors
	dataArray[MIDIRUP] = ir.readObjTempC();		//in Celsius
	dataArray[MIDIRDOWN] = ir2.readObjTempC();


//Lux
	lux.setGain(TSL2561_GAIN_0X);	//Bright situations
	lux.setTiming(TSL2561_INTEGRATIONTIME_13MS);
	dataArray[VISDOWN] = lux.getLuminosity(TSL2561_VISIBLE);
	dataArray[IRDOWN] = lux.getLuminosity(TSL2561_INFRARED);



	lux2.setGain(TSL2561_GAIN_0X);	//Bright situations
	lux2.setTiming(TSL2561_INTEGRATIONTIME_13MS);
	dataArray[IRUP]  = lux2.getLuminosity(TSL2561_VISIBLE);
	dataArray[VISUP] = lux2.getLuminosity(TSL2561_INFRARED);
}

bool Data::saveData()
{
	File dataFile;		//dataFile for SD card
	if(!SD.begin(10))
	{
		Serial.println("SD Card cannot open");
		return 1;
	}
	dataFile = SD.open("dataFile.txt",FILE_WRITE);
	for(int i = 0; i < SIZE; i++)
	{
		dataFile.print(dataArray[i]);
		dataFile.print(",");
	}
	if(!dataFile.println())
	{
		Serial.println("Data has been saved");
	}else{
		Serial.println("SD CARD FAILED... Data has been lost");
	return 0;
	}
}
char * Data::tahu(int i, char * a)
{
	for(int h = 12; h >= 0; h -=2)
	{
		a[h] = (i % 10) + 48;
		i /= 10;
	}
	return a;
}

//time coversion, only takes numbers. Returns -1 if it fails
long int Data::timeConv(char* input){
	for(int i = 0; i < 6; i++){
		if((input[i] < 48 ) | (input[i] > 57)) return -1;
	}
	//s + s*10 + m*60 + m*600 + h*3600 + h*36000
	return (long)(input[5]-48) + (long)(input[4]-48)*10 + (long)(input[3]-48)*60 + (long)(input[2]-48)*600 + (long)(input[1]-48)*3600 + (long)(input[0]-48)*36000;
}

//degree conversion
long int Data::degConv(char* input){
	for(int i = 0; i < 9; i++){
		if(input[i] == '.') continue;
		if((input[i] < 48 ) | (input[i] > 57)) return -1;
	}
	//in microdegrees
	long int degree = 10000000*(input[0]-48);
	degree += 1000000*(input[1]-48);

	long int min = 0;
	min += (long)100000*(input[2]-48);
	min += (long)10000*(input[3]-48);
	min += (long)1000*(input[5]-48);
	min += (long)100*(input[6]-48);
	min += (long)10*(input[7]-48);
	min += (long)(input[8]-48);

	degree += 100*min/60;


	return degree;
}

//altitude conversion to decimeters
long int Data::altConv(char* input){
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
	for(int i = decimal-1; i >= 0; i--){
		altitude += (long)(input[i]-48)*multiplier;
		multiplier *= 10;
	}

	return altitude*100;
}

void Data::readGPS()
{
	char latitude[12];
	char longitude[12];
	char altitude[12];	//needs null-terminating character
	char time[12];

	memset(latitude,0,12);
	memset(longitude,0,12);
	memset(altitude,0,12);	//needs null-terminating character
	memset(time,0,12);

	char array[101];
	memset(array,0,101);
	char checksum[2];
	char check = 0;

	//get a line
	while(gps.read() != '$')delay(2);
	delay(4);
	char tmpchar;
	for(int i = 0; i < 100;){
		tmpchar = gps.read();
		if (tmpchar == -1) continue;
		if (tmpchar == '*') break;
		array[i] = tmpchar;
		check = check ^ tmpchar;
		i++;
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

	long int tmp = timeConv(time);
	if(tmp >= 0) dataArray[GPS_TIME] = tmp;
	tmp = degConv(latitude);
	if(tmp >= 0) dataArray[GPS_LAT] = tmp;
	tmp = degConv(&longitude[1]);
	if(tmp >= 0) dataArray[GPS_LONG] = tmp;
	tmp = altConv(altitude);
	if(tmp >= 0) dataArray[GPS_ALT] = tmp;
}

unsigned long int Data::timeSince()
{
	return dataArray[TIMECOLLECT];
}
