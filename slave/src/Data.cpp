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
#define PACKETSIZE 10

#include "Data.h"
#include "Arduino.h"
#include "SPI.h"		//Library for SPI communicatinos
#include "SD.h"			//Library for SD  communications
#include "IntersemaBaro.h"	//Library for altimeter data
#include "Adafruit_Sensor.h"	//Library for Adafruit sensors
#include "Adafruit_GPS.h"	//Library for GPS
#include "SoftwareSerial.h"	//Library for Software Serial communications
#include "Wire.h"
#include "TSL2561.h"

//Global variable necessary for Lux Calculations
//Adafruit_TSL2561_Unified tsl3 = Adafruit_TSL2561_Unified(TSL2561_ADDR_GROUND, 12345);
Intersema::BaroPressure_MS5607B baro(true);

//******************************************************************************
//Constructor, reset, init

Data::Data(){
	index = 0;
	reset();
}

void Data::reset(){
	//Set the readings to sentinal value
	temp = INIT;
	pres = INIT;
	humi = INIT;
	CO2 = INIT;
	UV = INIT;
	O3 = INIT;
	IRup = INIT;
	IRdown = INIT;
	visUp = INIT;
	visDown = INIT;

	index++;		//increment the index by 1 on reset
}

//******************************************************************************
//Functions to return data as array

void Data::returnData(unsigned long int * dataArray){

//If you change the number of readings here you must update POINTSIZE in Data.h
	dataArray[0] = index++;
	dataArray[1] = timeCollect;
	dataArray[2] = temp;
	dataArray[3] = pres;
	dataArray[4] = humi;
	dataArray[5] = CO2;
	dataArray[6] = UV;
	dataArray[7] = O3;
	dataArray[8] = IRup;
	dataArray[9] = IRdown;
	dataArray[10] = visUp;
	dataArray[11] = visDown;
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

void Data::readPres(){
	baro.init();
	pres = baro.getPressure();
}

void Data::readLUX()
{
	TSL2561 tsl(TSL2561_ADDR_LOW);
	TSL2561 tsl2(TSL2561_ADDR_FLOAT);
	//Set address to bottom lux sensor
	if(tsl.begin())
	{
	//Set settings for lux sensor
//		Serial.println("Lux sensor connected");
		tsl.setGain(TSL2561_GAIN_0X);	//Bright situations
//		tsl.setGain(TSL2561_GAIN_16X);	//Dim situations
		tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);

	//Take readings from light sensor
		uint16_t vis = tsl.getLuminosity(TSL2561_VISIBLE);
//		uint16_t full = tsl.getLuminosity(TSL2561_FULLSPECTRUM);
		uint16_t ir = tsl.getLuminosity(TSL2561_INFRARED);

	//Save data from top sensor

		visDown = vis;
		IRdown = ir;
	}
	else
	{
	Serial.println("5");
		Serial.println("LUX sensor 1 is broked");
	}

	if(tsl2.begin())
	{
	//Set settings for lux sensor
//		Serial.println("Lux sensor connected");
		tsl2.setGain(TSL2561_GAIN_0X);	//Bright situations
//		tsl2.setGain(TSL2561_GAIN_16X);	//Dim situations
		tsl2.setTiming(TSL2561_INTEGRATIONTIME_13MS);

	//Take readings from light sensor
		uint16_t vis = tsl2.getLuminosity(TSL2561_VISIBLE);
//		uint16_t full = tsl2.getLuminosity(TSL2561_FULLSPECTRUM);
		uint16_t ir = tsl2.getLuminosity(TSL2561_INFRARED);
		IRup = ir;
		visUp = vis;
	}
	else
	{
		Serial.println("LUX sensor 2 is broked");
	}
}

void Data::saveData()
{
	pinMode(10,OUTPUT);	//set Digital 10 to CS for SD card
	File dataFile;		//dataFile for SD card
	if(!SD.begin(10))
	{
		Serial.println("Yup, it's broked");
	}

	if(index % PACKETSIZE == 0)
	{
		char filename[18] = "0/0/0/0/0/0/0.CSV";
		tahu(index,filename);
	}

	if (!SD.exists(filename))
	{
		dataFile.close();
		dataFile = SD.open(filename, FILE_WRITE);
	}
	if(!dataFile)
	{
		Serial.print("Could not create file: ");
		Serial.println(filename);
	}
	Serial.print("Logging to: ");
	Serial.println(filename);

	for(int i = 0; i < 12;i++)
	{
		dataFile.print(dataArray[i]);
		dataFile.print(",");
	}
	dataFile.flush();
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
	return timeCollect;
}
