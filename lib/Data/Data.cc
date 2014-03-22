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

 #include "Data.h"

Data::Data(){
	//constructor to initialize to -1
	reset();
}

void Data::reset(){
	//Set the pin values to sentinal value
	int tempPin = -1
	int altiPin = -1
	int presPin = -1
	int humiPin = -1
	int CO2_Pin = -1
	int CO__Pin = -1
	int N2O_Pin = -1
	int UV__Pin = -1
	int O3__Pin = -1
}

void Data::readSensorData(){
	
}

//Below is a ridiculous number of functions. They are set functions for each of 
//the possible variables

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

void Data::setN20_Pin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		int N2O_Pin = pin;
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

void Data::setIR__Pin(int pin){
	if((pin <= 65) && (pin >= 0 )){
		int IR__Pin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setHumiPin(pin){
	if((pin <= 65) && (pin >= 0 )){
		int humiPin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::UV__Pin(pin){
	if((pin <= 65) && (pin >= 0 )){
		int UV__Pin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}

void Data::setCO__Pin(pin){
	if((pin <= 65) && (pin >= 0 )){
		int CO__Pin = pin;
	}else {
		Serial.print("Error: pin invalid, dummy: ");
		Serial.println(pin);
	}
}
