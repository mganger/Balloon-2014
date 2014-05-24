/*
 * src.ino
 * This file is part of Balloon 2014
 *
 * Copyright (C) 2014 - Houghton College Science Honors
 *
 * Balloon 2014 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Balloon 2014 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Balloon 2014. If not, see <http://www.gnu.org/licenses/>.
 */

//This program is designed to run diagnostics on a radio connection, much lke a
//ping. Everything is divided by two for roundtrip

#include <SoftwareSerial.h>
#define _SS_MAX_RX_BUFF 256
SoftwareSerial radio(2,3);	//Rx,Tx

#define TIMEOUT 1000000		//timeout of transmission in microseconds/
#define RETRIES 10		//number of pings per test
#define WELCOME "This is the welcome message to diagnostics"

//returns microseconds if connected, -1 for connection timeout, and 0 for fail
long int ping(byte charNumber){

	//construct a string with the right number of characters
	char array[charNumber+1];
	char comparray[charNumber];
	array[charNumber] = '\0';
	for(int i = 0; i < charNumber; i++){
		array[i] = random(33,126);
	}

	unsigned long int time = micros();
	radio.print(array);
	while(radio.available() == 0){
		if(micros() - time <= TIMEOUT) return -1;
	}
	for(int i = 0; i < charNumber; i++){
		comparray[i] = radio.read();
	}
	unsigned long int endtime = micros();

	//check to see if the arrays are the same
	for(int i = 0; i < charNumber; i++){
		if(array[i] != comparray[i]) return 0;
	}
	return micros() - endtime;
}

long int ping(){
	char randnum = 67;	// random(33,126);
	unsigned long int time = micros();
	Serial.print(randnum);
	radio.print(randnum);
	delay(10);
	while(radio.available() == 0){
		if((micros() - time <= TIMEOUT)){
			return -1;
		}
	}
	unsigned long int endtime = micros();
	char recieved = radio.read();
	Serial.print(recieved);

	if(recieved != randnum){
		return 0;
	}
	return micros() - endtime;
}

void setup(){
	Serial.begin(115200);
	Serial.print(WELCOME);
	Serial.println();
	randomSeed(analogRead(0));

	//Use this to test the pinging capabilities if you already know the baud
	Serial.println("Ping Test");
	radio.begin(115200);
	radio.listen();
	//Character Test
	while(1){
	for(int i = 0; i < 1000; i++){
		Serial.print(ping()); Serial.print('\t');
		delay(1);
	}
	}

	//First we find the baud rate that the radio is operating on
	Serial.print("Detecting Baud Rate:");
	unsigned long int baud[] = {1200,2400,4800,9600,19200,38400,57600,76800,115200};
	for(unsigned long int i = 0;; i++){
//		Serial.print("Trying ");Serial.println(baud[i%9]);
		radio.begin(baud[i%9]);
//		Serial.println("Began serial communications");
		delay(100);
//		Serial.println("Pinging");
		if(ping(5) >= 0){
			static int baudRate = baud[i];
			Serial.println(baudRate);
			break;
		}
//		Serial.println("End pinging");
		radio.end();
//		Serial.print("Loop: ");
//		Serial.println(i);
	}

	while(1){
		//test io connection speed
		Serial.print("Packet Throughput:\t");
		double packetSpeed;
		for(int i = 0; i < RETRIES; i++){
			packetSpeed += ping() / 1000 / 2;
		}
		Serial.println(packetSpeed);
	
		//test character io speed
		Serial.print("Character Throughput:\t");
		double characterSpeed;
		for(int i = 0; i < RETRIES; i++){
			characterSpeed += ping(255)/255/2/1000;
		}
		Serial.println(characterSpeed);
	
		delay(1000);
	}
}

void loop(){}
