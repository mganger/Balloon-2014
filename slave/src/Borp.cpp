/*
 * Borp.cc - Library for sending data from an Arduino over a serial connection,
 * specifically developed for the Arduino Due and MM2 radio chips.
 * Balloon Over Radio Protocl (B.O.R.P)
 * Created by Houghton College Science Honors program 2014
 *
 * Borp.cc
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

//Constructor for Borp declares what pin the serial connection to the radio is 
//and and the baud rate to be used in transmission.
//Baud rate should be the lowest baud rate required to transmit the amount of 
//data we are collecting. Baud rates that are too high can max out the 
//processing power of the Arduino and ultimately slow transmissions down.

#include "Borp.h"
#include "Arduino.h"
//#include "MD5.h"

Borp::Borp(){
	Serial.begin(115200);
	serialOpen = 1;
}


//Prints the int array as ascii to the serial ports
void Borp::phoneHome( int* dataArray,int size){

	if(serialOpen){
		for(int i = 0; i < size; i++){
			Serial.print(dataArray[i]);
		}
		Serial.print('\n');
	}
}

bool Borp::compareArrays(char * array1, char* array2, int size){
	for(int i = 0; i < size; i++){
		if(array1[i] != array2[i]){
			return 0;
		}
	}
	return 1;
}

int Borp::listen(){
	//check to see if there is something from the master; -1 == nothing
	if(Serial.available() == 0){
		return -1;
	}

	//Throw together a string of what is sent from the master
	//Max size is 30 characters
	//We fill the rest with null
	char input[30];
	int index = 0;
	while(Serial.available()){
		Serial.readBytes(&input[index],1);
		index++;
	}

	for(;index < 30; index++){
		input[index] = '\0';
	}
	delete[] &index;			//to keep memory open



	//Special commands from the master, can be safely changed
	//The commands are lengthy on purpose (accident prevention).
	char cutDown[] = "cut down the balloon";
	char killRadio[] = "kill the communications";
	char powerSave[] = "enter powersave mode";

	//scan through and compare the chars of input and keyphrases
	//cutdown = 1
	//killRadio = 2
	//powerSave = 3
	if(compareArrays(input,cutDown, sizeof(cutDown)/sizeof(cutDown[0]))) return 1;
	if(compareArrays(input,killRadio, sizeof(killRadio)/sizeof(killRadio[0]))) return 2;
	if(compareArrays(input,powerSave, sizeof(powerSave)/sizeof(powerSave[0]))) return 3;
	return 0;

	delete[] &cutDown;
	delete[] &killRadio;
	delete[] &powerSave;
}
