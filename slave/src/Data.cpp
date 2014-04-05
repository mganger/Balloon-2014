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

#define DATACOUNT 9					//number of sensors being read

#include "Data.h"
#include "Arduino.h"

//******************************************************************************
//Constructor, reset, init

Data::Data(){
	//constructor to initialize to -1
	reset();
}

void Data::reset(){
	//Set the readings to sentinal value
	temp = -1;
	alti = -1;
	pres = -1;
	humi = -1;
	CO2 = -1;
	CO = -1;
	N2O = -1;
	UV = -1;
	O3 = -1;
	IR = -1;

	index++;						//increment the index by 1 on
}

void Data::initPins(){
	//loop through the pins in the array
	for(int i = 0; i < sizeof(sensorPin); i++){
		//only set pinMode if they are positive (i.e. sentinel value is < 1) 
		if(sensorPin[i] > 0){
			pinMode(sensorPin[i],INPUT);
		}
	}
}

//******************************************************************************
//Functions to return data as array

unsigned char * Data::returnData(int * dataArray){

	//updates the dataUnion

	dataUnion.dataArray[0] = indexArray[0];
	dataUnion.dataArray[1] = indexArray[1];
	dataUnion.dataArray[2] = timeArray[0];
	dataUnion.dataArray[3] = timeArray[1];
	dataUnion.dataArray[4] = temp;
	dataUnion.dataArray[5] = alti;
	dataUnion.dataArray[6] = pres;
	dataUnion.dataArray[7] = humi;
	dataUnion.dataArray[8] = CO2;
	dataUnion.dataArray[9] = CO;
	dataUnion.dataArray[10] = N2O;
	dataUnion.dataArray[11] = UV;
	dataUnion.dataArray[12] = O3;
	dataUnion.dataArray[13] = IR;

	return &dataUnion.packet;

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

void Data::readTemp(){
	temp = analogRead(sensorPin[0]);
}

void Data::readAlti(){
	alti = analogRead(sensorPin[1]);
	//read from the sensor and write to **** variable
}

void Data::readHumi(){
	humi = analogRead(sensorPin[7]);
	//read from the sensor and write to **** variable
}

void Data::readPres(){
	pres = analogRead(sensorPin[2]);
	//read from the sensor and write to **** variable
}

void Data::readCO2(){
	CO2 = analogRead(sensorPin[3]);
	//read from the sensor and write to **** variable
}

void Data::readN2O(){
	N2O = analogRead(sensorPin[5]);
	//read from the sensor and write to **** variable
}

void Data::readCO(){
	CO = analogRead(sensorPin[4]);
	//read from the sensor and write to **** variable
}

void Data::readIR(){
	IR = analogRead(sensorPin[6]);
	//read from the sensor and write to **** variable
}

void Data::readUV(){
	UV = analogRead(sensorPin[8]);
	//read from the sensor and write to **** variable
}

void Data::readO3(){
	//read from the sensor and write to **** variable
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
