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
#define INIT 4294967295

#include "Data.h"
#include "Arduino.h"
#include "SPI.h"		//LIbrary for SPI communicatinos
#include "SD.h"			//Library for SD  communications
#include "IntersemaBaro.h"	//Library for altimeter data
#include "Adafruit_Sensor.h"	//Library for Adafruit sensors
#include "Adafruit_TSL2561_U.h"	//Library for Lux Sensor
#include "Adafruit_GPS.h"	//Library for GPS

//Global variable necessary for Lux Calculations
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
Intersema::BaroPressure_MS5607B baro(true);

//******************************************************************************
//Constructor, reset, init

Data::Data(){
//Setup GPS 
//	SoftwareSerial mySerial(3,2);
//	Adafruit_GPS GSP(&mySerial);
//	#define GPSECHO true
//	boolean usingInterrupt = false;
//	void useInterrupt(boolean);
//
//	Adafruit_GPS GPS(&mySerial);
//	GPS.begin(9600);
//	GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
//	GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
//	GPS.sendCommand(PGCMD_ANTENNA);

//constructor to initialize to 4294967295
	index = 0;
	reset();
}

void Data::reset(){
	//Set the readings to sentinal value
	temp = INIT;
	alti = INIT;
	pres = INIT;
	humi = INIT;
	CO2 = INIT;
	UV = INIT;
	O3 = INIT;
	IR = INIT;
	LUX = INIT;

	index++;		//increment the index by 1 on reset
}

//******************************************************************************
//Functions to return data as array

void Data::returnData(unsigned long int * dataArray){

	dataArray[0] = index;
	dataArray[1] = timeCollect;
	dataArray[2] = temp;
	dataArray[3] = alti;
	dataArray[4] = pres;
	dataArray[5] = humi;
	dataArray[6] = CO2;
	dataArray[7] = UV;
	dataArray[8] = O3;
	dataArray[9] = IR;
	dataArray[10] = LUX;
}

void Data::returnData(unsigned long int * dataArray,unsigned long int index){
		returnData(dataArray);
		//retrieves data point with a certain index from the SD
}

//******************************************************************************
//Functions for reading the data

void Data::readSensorData()
{
	timeCollect = millis();
	readLUX();
	readAlti();
	readPres();
	readUV();
	readIR();
	readHumi();
	readCO2();
	readTemp();
	readO3();
}

void Data::readCO2()
{
	CO2 = analogRead(0);
}

void Data::readIR()
{
	IR = 345;
}

void Data::readTemp()
{
	temp = analogRead(1);
}

void Data::readHumi()
{
	humi = analogRead(2);
}

void Data::readUV()
{
	UV = analogRead(2);
}

void Data::readO3()
{
	O3 = analogRead(3);
}

void Data::readAlti(){
	baro.init();
	alti = baro.getHeightCentiMeters();
}

void Data::readPres(){
	baro.init();
	pres = baro.getPressure();
}

void Data::setupLUX()
{
//	sensor_t sensor;		//Used to display sensor details
//	tsl.getSensor(&sensor);		//Possibly not needed
	tsl.enableAutoRange(true);
	tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
	if(!tsl.begin())
	{
		Serial.print("Lux Sensor is broken or not connected");
	}
	tsl.enableAutoRange(true);
	tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
}

void Data::readLUX()
{
	sensors_event_t event;
	tsl.getEvent(&event);
	if(event.light)
	{
		LUX = event.light;
	}
}

void Data::saveData()
{
	File dataFile;
	if(SD.begin(10))
	{
		for(int i = 0; i < 1000000; i++)
		{
			char filename[] = "LOGGER0000000.txt";
			filename[6] = i/1000000 + '0';
			filename[7] = i/100000 + '0';
        		filename[8] = i/10000 + '0';
        		filename[9] = i/1000 + '0';
        		filename[10] = i/100 + '0';
        		filename[11] = i/10 + '0';
        		filename[12] = i%10 + '0';
			if(!SD.exists(filename))
			{
				dataFile = SD.open(filename, FILE_WRITE);
				break;
			}
		}
	}
	for(int i = 0;i < 10;i++)
	{
		dataFile.print(dataArray[i]);
		dataFile.print(",");
	}
	dataFile.print("\n");
	dataFile.flush();
}

void Data::readGPS()
{

}

unsigned long int Data::timeSince()
{
	return timeCollect;
}
