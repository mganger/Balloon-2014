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

#include "Data.h"
#include "Arduino.h"
#include "SPI.h"		//Library for SPI communications
#include "SD.h"			//Library for SD  communications
#include "IntersemaBaro.h"	//Library for altimeter data
#include "Adafruit_Sensor.h"	//Library for Adafruit sensors
#include "SoftwareSerial.h"	//Library for Software Serial communications

Intersema::BaroPressure_MS5607B baro(true);

//******************************************************************************
//Constructor, reset, init

Data::Data(){
	File initFile;
	pinMode(10,OUTPUT);	//set Digital 10 to CS for SD card
	if(!SD.begin(10)){
		Serial.println("The SD reader has failed or is not present");
	}
	else{
		Serial.println("CREATING STARTUP LOG FILES");
		delay(2000);
		initFile = SD.open("start.log",FILE_WRITE);
		if(!initFile){
			Serial.println("Could not create startup file");
		}else{
		initFile.println();
		initFile.println();
		initFile.println("---------------");
		initFile.print("Time since boot: ");
		initFile.println(micros());
		initFile.print("GPS Status: ");
		initFile.flush();
		initFile.close();
		}
	}
	memset(dataArray,INIT,SIZE*4);
	Serial.println("Initialized Array");
	printData();
	dataArray[INDEX] = dataArray[INDEX] +1;
	//initialize the pressure sensor
}

void Data::reset(){
	//Set the readings to sentinal value
	memset(&dataArray[TIMECOLLECT+1],INIT,(SIZE-2)*4);
	dataArray[INDEX]++;
}

//******************************************************************************
//Functions to return data as array

void Data::printData(){
//If you change the number of readings here you must update SIZE in Data.h
	for(int i = 0; i < SIZE; i++)
	{
		Serial.print(dataArray[i]);
		Serial.print(",");
	}
	Serial.println();
}

//******************************************************************************
//Functions for reading the data

void Data::readSensorData()
{
	reset();
	dataArray[TIMECOLLECT] = millis();
	readPres();
	readUV();
	readHumi();
	readCO2();
	readTemp();
	readO3();
}

void Data::readCO2()
{
	dataArray[CO2] = analogRead(0);
}

void Data::readTemp()
{
	dataArray[TEMP] = analogRead(1);
}

void Data::readHumi()
{
	dataArray[HUMI] = analogRead(2);
}

void Data::readUV()
{
	dataArray[UV] = analogRead(2);
}

void Data::readO3()
{
	dataArray[O3] = analogRead(3);
}

void Data::readPres(){
	baro.init();
	dataArray[PRES] = baro.getHeightCentiMeters();
}

bool Data::saveData()
{
	File dataFile;		//dataFile for SD card
//	if(!SD.begin(10))
//	{
//		Serial.println("SD Card cannot open");
//		reset();
//		return 1;
//	}

//	if(dataArray[INDEX] % PACKETSIZE == 0)
//	{
//		char filename[18] = "0/0/0/0/0/0/0.CSV";
//		char foldername[18] = "0/0/0/0/0/0/0.CSV";
//		tahu(dataArray[INDEX],filename);
//		tahu(dataArray[INDEX],foldername);
//		foldername[11] = '\0';
//		Serial.print(foldername);
//		Serial.print(": ");
//		Serial.println(filename);
//		SD.mkdir(foldername);
//		if(!SD.exists(filename))
//		{
//			dataFile.close();
//			dataFile = SD.open(filename, FILE_WRITE);
//			Serial.println(dataFile);
//			delay(1000);
//			if(!dataFile)
//			{
//				Serial.print("Could not create file: ");
//				Serial.println(filename);
//				reset();
//				return 1;
//			}else
//			{
//				Serial.print("Logging to: ");
//				Serial.println(filename);
//			}
//		}
//	}

	dataFile = SD.open("Log.log",FILE_WRITE);
	if(dataFile){
		Serial.println("Datafile: Log.log has been opened for writing");
		for(int i = 0; i < SIZE;i++)
		{
			dataFile.print(dataArray[i]);
			dataFile.print(",");
		}
		dataFile.println();
		dataFile.flush();
		dataFile.close();
		return 0;
	}else{
		Serial.print("Datafile: Log.log cannot be created... ");
		Serial.println("Data has been lost");
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

void Data::readGPS()
{

}

unsigned long int Data::timeSince()
{
	return dataArray[TIMECOLLECT];
}
