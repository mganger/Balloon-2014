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

#define TIMEOUT 1000000		//timeout of transmission in microseconds
#define TIME_THRESH 10		//timeout threshold
#define RETRIES 10		//number of pings per test
#define TIMESHIFT 1.00488461885	//ratio Actual/Arduino (see code below)
#define SMOOTHING 2		//amount to smooth data
#define WELCOME "\r\nHoughton College Radio Diagnostics\r\nVersion 1.0\r\n"

//globals
SoftwareSerial radio(2,3);	//Rx,Tx
int timeoutCount = 0;		//flagged by ping

//returns microseconds if connected, -1 for connection timeout, and 0 for fail
long int ping(byte charNumber){

	//construct a string with the right number of characters
	char array[charNumber+1];
	char comparray[charNumber+1];
	array[charNumber] = '\0';
	Serial.print(array);
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

	//flush the buffer
	while(radio.available()){
		radio.read();
	}
	char randnum = random(33,126);
	char recieved;
	unsigned long int endtime;
	unsigned long int time = micros();
	radio.print(randnum);
	while(micros() - time < TIMEOUT){
		recieved = radio.read();
		if (recieved > -1){
			endtime = micros();
			break;
		}
	}
	if(micros() - time >= TIMEOUT){
		timeoutCount++;
		return -1;
	}
	if(recieved != randnum) return 0;
	return endtime - time;

}

void detectBaudRate(){
	Serial.print("Detecting Baud Rate: ");
	unsigned long int baud[] = {1200,2400,4800,9600,19200,38400,57600,76800,115200};
	for(unsigned long int i = 0;; i++){
		//Serial.print(baud[i%9]);
		radio.begin(baud[i%9]);
		delay(100);
		if(ping() >= 0){
			int baudRate = baud[i];
			Serial.println(baudRate);
			break;
		}
		radio.end();
	}
}

void setup(){
	Serial.begin(115200);
	Serial.print(WELCOME);
	Serial.println();
	randomSeed(analogRead(0));

//	//Use this code block to manually calibrate the microsecond timer
//	while(1){
//		Serial.println(micros());
//		delay(1000);
//	}


	//First we find the baud rate that the radio is operating on
	detectBaudRate();

	//Ping test
//	Serial.println("Ping Test");
//	//Character Test
//	while(1){
//	for(int i = 0; i < 1000; i++){
//		Serial.print(ping()); Serial.print('\t');
//	}
//	}

	//Run diagnostics
	double packetRate = 0;
	unsigned long int timeLast = millis();
	while(1){
		//test io connection speed
		unsigned long int packetPeriod = 0;
		int count = 0;
		for(int i = 0; i < RETRIES; i++){
			unsigned long int time = ping();
			if(time > 0){
				packetPeriod += time;
				count++;
			}
		}
		double avgPeriod = (double)packetPeriod/count;
		packetRate += (((double)1000000/(avgPeriod * TIMESHIFT)) - packetRate)/SMOOTHING;

		if(millis() - timeLast >= 1000){
			Serial.print("Packet Throughput:\t");
			Serial.print(packetRate);
			Serial.println(" Hz");
			timeLast = millis();
		}
	
		//test character io speed
//		Serial.print("Character Throughput:\t");
//		double characterSpeed;
//		for(int i = 0; i < RETRIES; i++){
//			characterSpeed += ping(255)/255/2/1000;
//		}
//		Serial.println(characterSpeed);
//	
//		delay(1000);

		if(timeoutCount >= TIME_THRESH){
			timeoutCount = 0;
			detectBaudRate();
		}
	}
}

void loop(){}
