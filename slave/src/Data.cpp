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
	dataArray[1] = time;
	dataArray[2] = temp;
	dataArray[3] = alti;
	dataArray[4] = pres;
	dataArray[5] = humi;
	dataArray[6] = CO2;
	dataArray[7] = CO;
	dataArray[8] = N2O;
	dataArray[9] = UV;
	dataArray[10] = O3;
	dataArray[11] = IR;
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

//******************************************************************************
//Getters

unsigned long int Data::timeSince(){
	return timeCollect;
}


//******************************************************************************
//Setters

void Data::setTempPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		sensorPin[0] = pin;
	}else {
		Serial.print("Error: pin invalid, dummy:  ");
		Serial.println(pin);
	}
}

void Data::setAltiPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		sensorPin[1] = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setPresPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		sensorPin[2] = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setCO2Pin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		sensorPin[3] = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setCOPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		sensorPin[4] = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setN2OPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		sensorPin[5] = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setIRPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		sensorPin[6] = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setHumiPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		sensorPin[7] = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}
void Data::setO3Pin(int pin){
	if((pin <= 65) && (pin >=0 )){
		sensorPin[9] = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setUVPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		sensorPin[8] = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}
