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
#include <Wire.h>		//Library for I2C communications
#include <SPI.h>		//LIbrary for SPI communicatinos
#include <SD.h>			//Library for SD  communications
#include "IntersemaBaro.h"	//Library for altimeter data
#include "Adafruit_Sensor.h"	//Library for Adafruit sensors
#include "Adafruit_TSL2561_U.h"	//Library for Lux Sensor

//Global variable necessary for Lux Calculations
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
Intersema::BaroPressure_MS5607B baro(true);

//******************************************************************************
//Constructor, reset, init

Data::Data(){
	//constructor to initialize to 4294967295
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

	index++;						//increment the index by 1 on
}

//******************************************************************************
//Functions to return data as array

void Data::returnData(int * dataArray){

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
}

	//This function does not actually use the variable int index. What does this function do differently than returnData(int * dataArray) ?
void Data::returnData(int * dataArray, int index){
		returnData(dataArray);				//return newest reading
		//retrieves data point with a certain index
		//it probably is on the SD card, could be on the EEPROM
}

//******************************************************************************
//Functions for reading the data

void Data::readSensorData(){
	timeCollect = millis();
	readTemp();
}

void Data::readCO2()
{
	CO2 = analogRead(0);
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

void DataL::setupSD()
{
	while(!SD.begin(10));
	char filename[] = "LOGGER000000.txt";
	 filename[6] = i/100000 + '0';
         filename[7] = i/10000 + '0';
         filename[8] = i/1000 + '0';
         filename[9] = i/100 + '0';
         filename[10] = i/10 + '0';
         filename[11] = i%10 + '0';
	if(!SD.exists(filename))
	{
		dataFile = SD.open(filename, FILE_WRITE);
		break;
	}
}

void Data::saveData()
{
	for(int i = 0;i < 10;i++)
	{
		dataFile.print(dataArray[i]);
		dataFile.print(",");
	}
	dataFile.println();
	dataFile.flush();
}

//******************************************************************************
//Getters

unsigned long int Data::timeSince(){
	return timeCollect;
}
