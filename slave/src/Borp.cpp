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

#include "Borp.h"
#include "Arduino.h"

#define BASE 10
#define SIZE 8

//Manually writes the long int array as ascii to the hardware serial
void broadcast(unsigned long int * dataArray,int length){
	char check = 0;
	char checksum[3] = {'*',0,0};
	Serial.write('$');
	for(int i = 0; i < length; i++ ){
		unsigned long int num = dataArray[i];
		char tmp[SIZE];
		memset(tmp,0,SIZE);
		for(int h = SIZE-1;h >=0 ;h--){
			tmp[h] = num % BASE + 48;
			num /= BASE;
			check = check ^ tmp[h];
		}
		Serial.write((byte*)tmp,SIZE);
		Serial.write(',');
	}
	checksum[1] = check/16 +48;
	checksum[2] = check%16 +48;
	Serial.write((byte*)checksum,3);
	Serial.write((byte*)"\r\n",2);
}

long int ping(){

	//flush the buffer
	while(Serial.available()){
		Serial.read();
	}

	//make a random character
	byte randnum = random(33,126);
	byte received = 0;

	//save the time in microseconds
	unsigned long int endtime;
	unsigned long int time = micros();

	//send the character
	Serial.write(randnum);

	//wait for it to come back
	Serial.readBytes((char*)&received,1);
	endtime = micros();
	if(received == 0){
		return -1;
	}

	//check for failure
	if(received != randnum){
//		packetFail++;
		return 0;
	}

	//if everything went well, return the amount of time to ping
//	packetSuccess++;
	return endtime - time;
}

//Prints the int array as ascii to the serial ports
bool compareArrays(char * array1, char* array2, int size){
	for(int i = 0; i < size; i++){
		if(array1[i] != array2[i]){
			return 0;
		}
	}
	return 1;
}

long int listen(){
	//check to see if there is something from the master; -1 == nothing
	if(Serial.available() == 0){
		return -1;
	}
	delay(2);			//For the buffer to fill up
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
	char reviveRadio[] = "as you were";
	char request[] = "request ";

	//scan through and compare the chars of input and keyphrases
	//cutdown = 1
	//killRadio = 2
	//powerSave = 3
	if(compareArrays(input,cutDown, sizeof(cutDown)/sizeof(cutDown[0]))) return -2;
	if(compareArrays(input,killRadio, sizeof(killRadio)/sizeof(killRadio[0]))) return -3;
	if(compareArrays(input,powerSave, sizeof(powerSave)/sizeof(powerSave[0]))) return -4;
	if(compareArrays(input,reviveRadio,sizeof(reviveRadio)/sizeof(reviveRadio[0]))) return -5;

	//check for the request
	if(compareArrays(input,request,8)){
		return atoi(&input[8]);
	}
	return 0;

	delete[] &cutDown;
	delete[] &killRadio;
	delete[] &powerSave;
}
