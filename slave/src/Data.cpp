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
#define PACKETSIZE 1000
#define SIZE 14

//Pin definitions
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

#include "Data.h"
#include "Arduino.h"
#include "SPI.h"		//Library for SPI communicatinos
#include "SD.h"			//Library for SD  communications
#include "IntersemaBaro.h"	//Library for altimeter data
#include "Adafruit_Sensor.h"	//Library for Adafruit sensors
#include "SoftwareSerial.h"	//Library for Software Serial communications
#include "Wire.h"		//Library for i2c communication
#include "TSL2561.h"		//Library for digital luminosity/lux sensor
#include "Adafruit_TMP006.h"	//Library for non-contact temperature sensing

//Global variable necessary for Lux Calculations
//Adafruit_TSL2561_Unified tsl3 = Adafruit_TSL2561_Unified(TSL2561_ADDR_GROUND, 12345);
Intersema::BaroPressure_MS5607B baro(true);

//******************************************************************************
//Constructor, reset, init

Data::Data(){
	File initFile;
	pinMode(10,OUTPUT);	//set Digital 10 to CS for SD card
	if(!SD.begin(10)){
		Serial.println("The SD Card has failed or is not present");
	}
	else{
		initFile = SD.open("Startup Sequence.LOG",FILE_WRITE);
		initFile.println();
		initFile.println();
		initFile.println("---------------");
		initFile.print("Time since boot: ");
		initFile.println(millis());
		initFile.print("GPS Status: ");
		//Check to see what i2c sensors are ready
		initFile.close();
	}
	unsigned long int dataArray[SIZE];
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
	midIRup = INIT;
	midIRdown = INIT;

	index++;		//increment the index by 1 on reset
}

//******************************************************************************
//Functions to return data as array

void Data::printData(){

//If you change the number of readings here you must update POINTSIZE in Data.h
	for(int i = 0; i < sizeof(dataArray)/sizeof(dataArray[0]); i++)
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
	timeCollect = millis();
	readLUX();
	readPres();
	readUV();
	readIR();
	readHumi();
	readCO2();
	readTemp();
	readO3();
	readMidIR();
}

void Data::readCO2()
{
	dataArray[CO2] = analogRead(0);
}

void Data::readIR()
{
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
	dataArray[PRES] = baro.getPressure();
}

void Data::readMidIR()
{
	Adafruit_TMP006 tmp(0x40);  //Create tmp sensor with address 0x40  [GND,GND]
	Adafruit_TMP006 tmp2(0x41);  //Create tmp sensor with address 0x41 [GND,VCC]
	
	//you can also use tmp.begin(TMP006_CFG_1SAMPLE) or 2SAMPLE/4SAMPLE/8SAMPLE to have
	//lower precision, higher rate sampling. default is TMP006_CFG_16SAMPLE which takes
	//4 seconds per reading (16 samples)
	if(!tmp.begin(TMP006_CFG_1SAMPLE)) 
	{
		Serial.println("No top IR thermometer found");
	}
	if(!tmp2.begin(TMP006_CFG_1SAMPLE)) 
	{
		Serial.println("No bottom IR thermometer found");
	}
	
	//Loop
	float objt = tmp.readObjTempC();		//Returns Kelvins 
	float objt2 = tmp2.readObjTempC(); 		//Returns Kelvins

	dataArray[MIDIRUP] = objt;
	dataArray[MIDIRDOWN] = objt;

//	float diet = tmp.readDieTempC(); 		//Returns Kelvins
//	float diet2 = tmp2.readDieTempC(); 		//Returns Kelvins
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

		dataArray[VISDOWN] = vis;
		dataArray[IRDOWN] = ir;
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
		dataArray[IRUP] = ir;
		dataArray[VISUP] = vis;
	}
	else
	{
		Serial.println("LUX sensor 2 is broked");
	}
}

bool Data::saveData()
{
	pinMode(10,OUTPUT);	//set Digital 10 to CS for SD card
	File dataFile;		//dataFile for SD card
	if(!SD.begin(10))
	{
		Serial.println("SD Card cannot open");
		return 1;
	}

	if(index % PACKETSIZE == 0)
	{
		char filename[18] = "0/0/0/0/0/0/0.CSV";
		tahu(index,filename);
		if (!SD.exists(filename))
		{
			dataFile.close();
			dataFile = SD.open(filename, FILE_WRITE);
			if(!dataFile)
			{
				Serial.print("Could not create file: ");
				Serial.println(filename);
				return 1;
			}else
			{
				Serial.print("Logging to: ");
				Serial.println(filename);
			}
		}
	}

	for(int i = 0; i < 12;i++)
	{
		dataFile.print(dataArray[i]);
		dataFile.print(",");
	}
	dataFile.flush();
	return 0;
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
