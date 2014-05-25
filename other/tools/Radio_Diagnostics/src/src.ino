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

#define BUFFER 250		//keep within a safe buffer
#define TIMEOUT 2000		//timeout of transmission in microseconds
#define TIME_THRESH 10		//timeout threshold
#define RETRIES 10		//number of pings per test
#define TIMESHIFT 1.00488461885	//ratio Actual/Arduino (see code below)
#define SMOOTHING 2		//amount to smooth data
#define WELCOME "\r\n\r\nHoughton College Radio Diagnostics\r\nVersion 1.0\r\n"

//globals
SoftwareSerial computer(2,3);	//Rx,Tx
int timeoutCount = 0;		//flagged by ping
int packetFail = 0;
int packetSuccess = 0;
long int baudRate = 0;

void printDiag(){
	computer.println();
	computer.println("|Time\t\tTrials\t64b\tPacket\tChar\tLoss\tDisconnects");
	computer.println("|\t\t#\tms\tHz\tHz\t%\t#");
}

//returns microseconds if connected, -1 for connection timeout, and 0 for fail
long int ping(byte charNumber){
	if(charNumber == 1) return ping();

	//calculate timeout
	long int timeout = (8000000/baudRate)*charNumber *2;

	//flush the buffer
	while(Serial.available()){
		Serial.read();
	}

	//construct a string with the right number of characters
	char array[charNumber+1];
	char comparray[charNumber+1];
	array[charNumber] = '\0';
	comparray[charNumber] = '\0';

	//fill the array with random characters
	for(int i = 0; i < charNumber; i++){
		array[i] = random(33,126);
	}

	//send the string
	unsigned long int endtime;
	unsigned long int time = micros();
	Serial.print(array);

	//wait for the string to come back
	while(Serial.available() < charNumber){
		//return -1 and increment the flag if timeout, else do nothing
		if(micros() - time > timeout){
//			computer.println("Long Ping timeout");
			timeoutCount++;
			return -1;
		}
	}
	endtime = micros();

	//read the buffer into comparray
	for(int i = 0; i < charNumber; i++){
		comparray[i] = Serial.read();
	}

//	computer.println(array);
//	computer.println(comparray);

	//compare the arrays
	for(int i = 0; i < charNumber; i++){
		if(array[i] != comparray[i]){
			packetLoss++;
			return 0;
		}
	}

	//if everything went well, return the amount of time to ping
	packetSuccess++;
	return endtime - time;
}

long int ping(){

	//calculate timeout
	long int timeout = (8000000/baudRate)+1000;

	//flush the buffer
	while(Serial.available()){
		Serial.read();
	}

	//make a random character
	char randnum = random(33,126);
	char received;

	//save the time in microseconds
	unsigned long int endtime;
	unsigned long int time = micros();

	//send the character
	Serial.print(randnum);

	//wait for it to come back
	while(Serial.available() == 0){
		//return -1 and increment the flag if timeout, else do nothing
		if(micros() - time > timeout){
//			computer.println("Short Ping timeout");
			timeoutCount++;
			return -1;
		}
	}
	endtime = micros();

	//check to see if it there really is a character in the buffer
	received = Serial.read();
	if(received == -1){
//		computer.println("Ping failed");
		return 0;
	}

	//check for failure
	if(received != randnum){
//		computer.println("Characters do not match");
		packetLoss++;
		return 0;
	}

	//if everything went well, return the amount of time to ping
//	computer.print(randnum);computer.println(recieved);
	packetSuccess++;
	return endtime - time;
}

void detectBaudRate(){
	computer.print("Detecting Baud Rate: ");
	unsigned long int baud[] = {1200,2400,4800,9600,19200,38400,57600,76800,115200};
	byte baudcount[] = {0,0,0,0,0,0,0,0,0};
	for(unsigned long int i = 0;; i++){
//		computer.print("Trying ");computer.print(baud[i%9]);computer.print(" ");
		Serial.begin(baud[i%9]);
		delay(20);
		long int time = ping();

		//if ping returns affirmative, increment respective baudcount
		if(time > 0){
			baudcount[i%9]++;
			if(baudcount[i%9] >= 10){
				computer.println(baud[i%9]);
				baudRate = baud[i%9];
				break;
			}
		}
//		computer.println(time);
		Serial.end();
	}
	timeoutCount = 0;
}


void setup(){

	computer.begin(19200);
	computer.print(WELCOME);
	computer.println("Tabs may not align perfectly. Use caution");
	computer.println();
	randomSeed(analogRead(0));

//	//Use this code block to manually calibrate the microsecond timer
//	while(1){
//		computer.println(micros());
//		delay(1000);
//	}

	//Baud rate test
//	while(1) detectBaudRate();


	//First we find the baud rate that the Serial is operating on
	detectBaudRate();

	//Packet test
//	computer.println("Packet Test");
//	while(1){
//		computer.print(ping()); computer.print('\t');
//	}


	//Character Test
//	computer.println("Character Test");
//	while(1){
//		for(int i = 2; i < BUFFER; i++){
//			computer.print(ping(i));computer.print('\t');
//		}
//	}

	//Run diagnostics
	printDiag();
	double packetRate = 0;
	double charRate = 0;
	int diagCounter = 0;
	unsigned long int timeLast = millis();
	long int trials = 0;
	int disconnects = 0;
	while(1){


		//test io connection speed
		unsigned long int packetPeriod = 0;
		int count = 0;
		for(int i = 0; i < RETRIES; i++){
			long int time = ping()/2;
			if(time > 0){
				packetPeriod += time;
				count++;
			}
		}
		double avgPeriod = (double)packetPeriod/count;
		packetRate += (((double)1000000/(avgPeriod * TIMESHIFT)) - packetRate)/SMOOTHING;


		//test character io speed
		unsigned long long int charPeriod = 0;
		count = 0;
		for(int i = 0; i < RETRIES; i++){
			long int time = ping(BUFFER);
			if(time > 0){
				charPeriod += time;
				count++;
			}
		}
		double avgCharPeriod = (double)charPeriod/(count*BUFFER);
		charRate += (((double)1000000/(avgCharPeriod * TIMESHIFT)) - charRate)/SMOOTHING;

		trials += RETRIES*2;





		//Check for disconnect by timeout flag
		if(timeoutCount >= TIME_THRESH){
			computer.print("Disconnected");
			disconnects++;
			//wait for a connection again
			while(ping() == -1);
			//reset important variables
			charRate = 0;
			packetRate = 0;
			timeoutCount = 0;
		}





		//Print every second
		if(millis() - timeLast >= 1000){
			computer.println();
			computer.print(millis()/3600000);computer.print(':');
			computer.print(millis()/60000);computer.print(':');
			computer.print(millis()/1000);computer.print('.');
			computer.print(millis()%1000);computer.print('\t');

			computer.print(trials);computer.print('\t');
			computer.print(avgCharPeriod*64/1000);computer.print('\t');
			computer.print(packetRate);computer.print('\t');
			computer.print(charRate);computer.print('\t');
			computer.print('\t');
			computer.print(disconnects);computer.print('\t');


			if(diagCounter >= 50){
				printDiag();
				diagCounter = 0;
			}
			diagCounter++;
			timeLast = millis();
		}
	}
}

void loop(){}
