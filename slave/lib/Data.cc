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
#define PERIOD 1000/FREQ				//period in milliseconds
#define FREQ 10						//frequency of readings



////////////////////////////////////////////////////////////////////////////////
//Constructor to initialize and rest function

Data::Data(){
	//constructor to initialize to -1
	reset();
	pinMode(tempPin,OUTPUT);
}

void Data::reset(){
	//Set the readings to sentinal value
	temp = -1;
	alti = -1;
	pres = -1;
	humi = -1;
	CO2_ = -1;
	CO__ = -1;
	N2O_ = -1;
	UV__ = -1;
	O3__ = -1;

	index++;						//increment the index by 1 on
}

//End initialize/reset
//****************************************************************************//



////////////////////////////////////////////////////////////////////////////////
//Functions to return data (to pass to borp, etc.)

void Data::returnData(int * dataArray){

	//Makes an int array with the size representing the number of readings

	dataArray[0] = temp;
	dataArray[1] = alti;
	dataArray[2] = pres;
	dataArray[3] = humi;
	dataArray[4] = CO2_;
	dataArray[5] = CO__;
	dataArray[6] = N2O_;
	dataArray[7] = UV__;
	dataArray[8] = O3__;
	return;

//	memcpy(&dataArray[10], &point.timeCollect, 4);
//		Serial.println(dataArray[10]);
//	dataArray[11] = *((int*)&index);
//	dataArray[12] = *((int*)&timeCollect);
//		Serial.println(dataArray[12]);
//	dataArray[13] = *((int*)&timeCollect);

}

int *Data::returnData(int * dataArray, int index){

	if((millis() - timeCollect) >= PERIOD){		//time since last reading
		returnData(dataArray);				//return newest reading
	}else{
		//retrieves data point with a certain index
		//it probably is on the SD card, could be on the EEPROM
	}
}

//End return data functions
//****************************************************************************//


////////////////////////////////////////////////////////////////////////////////
//Functions for reading the data

void Data::readSensorData(){
	timeCollect = millis();
//	Serial.println(timeCollect);
	readTemp(tempPin);
}

void Data::readTemp(int pin){
	temp = analogRead(pin);
}

void Data::readAlti(int pin){
	//read from the sensor and write to **** variable
}

void Data::readHumi(int pin){
	//read from the sensor and write to **** variable
}

void Data::readPres(int pin){
	//read from the sensor and write to **** variable
}

void Data::readCO2_(int pin){
	//read from the sensor and write to **** variable
}

void Data::readN2O_(int pin){
	//read from the sensor and write to **** variable
}

void Data::readCO__(int pin){
	//read from the sensor and write to **** variable
}

void Data::readIR__(int pin){
	//read from the sensor and write to **** variable
}

void Data::readO3__(int pin){
	//read from the sensor and write to **** variable
}

//End read functions
//****************************************************************************//



////////////////////////////////////////////////////////////////////////////////
//Below is a ridiculous number of functions. They are set functions for each of 
//the possible variables, continue at your own risk.

void Data::setTempPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		int tempPin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy:  ");
		Serial.println(pin);
	}
}

void Data::setAltiPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		int altiPin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setPresPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		int presPin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setCO2_Pin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		int CO2_Pin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setCO__Pin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		int CO__Pin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setN2O_Pin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		int N2O_Pin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setIR__Pin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		int IR__Pin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setHumiPin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		int humiPin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setUV__Pin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		int UV__Pin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

//End set functions
//****************************************************************************//


