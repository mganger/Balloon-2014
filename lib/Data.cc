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



////////////////////////////////////////////////////////////////////////////////
//Constructor to initialize and rest function

Data::Data(){
	//constructor to initialize to -1
	reset();
}

void Data::reset(){
	//Set the pin values to sentinal value
	int tempPin = -1;
	int altiPin = -1;
	int presPin = -1;
	int humiPin = -1;
	int CO2_Pin = -1;
	int CO__Pin = -1;
	int N2O_Pin = -1;
	int UV__Pin = -1;
	int O3__Pin = -1;
}

//End initialize/reset
//****************************************************************************//



////////////////////////////////////////////////////////////////////////////////
//Functions to return data (to pass to borp, etc.)

int * Data::returnData(){
	//looks for the newest data point to send back
	//should already be in the memory
}

int *Data::returnData(int index){
	//retrieves data point with a certain index
	//it probably is on the SD card, could be on the EEPROM
}

//End return data functions
//****************************************************************************//


////////////////////////////////////////////////////////////////////////////////
//Functions for reading the data

void Data::readSensorData(){
	//Include necessary functions for specific groups sensor readings.
}

void Data::readTemp(int pin){
	//read from the sensor and write to **** variable
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

