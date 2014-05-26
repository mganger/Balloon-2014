/*
 * src.ino
 * This file is part of Balloon 2014
 *
 * Copyright (C) 2014 - Michael Ganger
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

//This program is designed to run diagnostics on a radio connection, much like a
//ping. Right now it works with a modified 256 byte buffer; if this means 
//nothing to you, change BUFFER below to 63 or less or else it will not work.

#include <SoftwareSerial.h>

#define SPACES 14		//muber of spaces to keep things pretty
#define BUFFER 250		//keep within a safe buffer
#define TIMEOUT 100		//timeout in milliseconds
#define TIME_THRESH RETRIES	//timeout threshold
#define RETRIES 10		//number of pings per test
#define TIMESHIFT 1.00488461885	//ratio Actual/Arduino (see code below)
#define SMOOTHING 2		//amount to smooth data
#define REFRESH	500		//minimum milliseconds between screen refreshes
#define WELCOME "\r\n\r\n\r\nHoughton College Radio Diagnostics v1.0.4\r\nLicensed under GPLv2\r\nCopyright (C) 2014 - Michael Ganger\r\n\r\n"

//globals
SoftwareSerial computer(2,3);	//Rx,Tx
int timeoutCount = 0;		//flagged by ping
int packetFail = 0;
int packetSuccess = 0;
long int baudRate = 0;

//used to make things pretty
void fill(int size){
	for(int i = SPACES - size; i; i--){
		computer.print(" ");
	}
}


void printDiag(){
	computer.println("\r\n");
	fill(computer.print("|Time"));
	fill(computer.print("Trials"));
	fill(computer.print("64 byte time"));
	fill(computer.print("Ping"));
	fill(computer.print("Packet"));
	fill(computer.print("Disconnects"));
	fill(computer.print("Live Corrupt"));
	fill(computer.print("Total Corrupt"));
	fill(computer.print("Live Timeouts"));
	computer.println();


	fill(computer.print("|ms"));
	fill(computer.print("#"));
	fill(computer.print("ms"));
	fill(computer.print("Packet/s"));
	fill(computer.print("Char/s"));
	fill(computer.print("#"));
	fill(computer.print("%"));
	fill(computer.print("%"));
	fill(computer.print("%"));
	computer.println();
}

//returns microseconds if connected, -1 for connection timeout, and 0 for fail
long int ping(byte charNumber){
	if(charNumber == 1) return ping();

	//flush the buffer
	while(Serial.available()){
		Serial.read();
	}

	//construct a string with the right number of characters
	byte array[charNumber];
	char comparray[charNumber];
	comparray[0] = 0;

	//fill the array with random characters
	for(int i = 0; i < charNumber; i++){
		array[i] = random(33,126);
	}

	//send the string
	unsigned long int endtime;
	unsigned long int time = micros();
	Serial.write(array,charNumber);

	//receive the string
	Serial.readBytes(comparray,charNumber);
	endtime = micros();

	//Check for timeout
	if(comparray[0] == 0){
		return -1;
	}

//	computer.println(array);
//	computer.println(comparray);

	//compare the arrays
	for(int i = 0; i < charNumber; i++){
		if(array[i] != comparray[i]){
			packetFail++;
			return 0;
		}
	}

	//if everything went well, return the amount of time to ping
	packetSuccess++;
	return endtime - time;
}

//single character
long int ping(){

	//flush the buffer
	while(Serial.available()){
		Serial.read();
	}

	//make a random character
	byte randnum = random(33,126);
//	computer.write(randnum);
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
//	computer.write(received);

	//check for failure
	if(received != randnum){
//		computer.println("Characters do not match");
		packetFail++;
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
		Serial.end();

		//look for input from the computer
		if(computer.available()){
			char character = computer.read();
			switch(character){
				case '0': 
					baudRate = 1200;
					Serial.begin(baudRate);
					computer.println(baudRate);
					return;
				case '1': 
					baudRate = 2400;
					Serial.begin(baudRate);
					computer.println(baudRate);
					return;
				case '2': 
					baudRate = 4800;
					Serial.begin(baudRate);
					computer.println(baudRate);
					return;
				case '3': 
					baudRate = 9600;
					Serial.begin(baudRate);
					computer.println(baudRate);
					return;
				case '4':
					baudRate = 19200;
					Serial.begin(baudRate);
					computer.println(baudRate);
					return;
				case '5': 
					baudRate = 38400;
					Serial.begin(baudRate);
					computer.println(baudRate);
					return;
				case '6': 
					baudRate = 57600;
					Serial.begin(baudRate);
					computer.println(baudRate);
					return;
				case '7': 
					baudRate = 76800;
					Serial.begin(baudRate);
					computer.println(baudRate);
					return;
				case '8': 
					baudRate = 115200;
					Serial.begin(baudRate);
					computer.println(baudRate);
					return;
			}
		}
	}
	timeoutCount = 0;
}

void setup(){

	computer.begin(19200);
	computer.print(WELCOME);
	computer.println();
	computer.print("Baud Options:\r\n");
	fill(computer.print("0) 1200"));
	fill(computer.print("1) 2400"));
	computer.print("2) 4800\r\n");
	fill(computer.print("3) 9600"));
	fill(computer.print("4) 19200"));
	computer.print("5) 38400\r\n");
	fill(computer.print("6) 57600"));
	fill(computer.print("7) 76800"));
	computer.print("8) 115200\r\n\r\n");
	randomSeed(analogRead(0));

//	//Use this code block to manually calibrate the microsecond timer
//	while(1){
//		computer.println(micros());
//		delay(1000);
//	}


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
//		computer.print(ping(BUFFER));computer.print('\t');
//	}







	//Run diagnostics
	Serial.setTimeout(TIMEOUT);
	printDiag();
	//wait for connection
	while(ping() == -1);
	double packetRate = 0;
	double charRate = 0;
	int diagCounter = 0;
	unsigned long int timeLast = millis();
	long int trials = 0;
	int disconnects = 0;
	packetSuccess = 0;
	packetFail = 0;
	timeoutCount = 0;
	while(1){
		//test io connection speed
		unsigned long int packetPeriod = 0;
		int corruptCount = 0;
		int pingTimeout = 0;
		int successCount = 0;
		int count = 0;
		for(int i = 0; i < RETRIES; i++){
			long int time = ping();
			if(time > 0){
				packetPeriod += time;
				count++;
				successCount++;
			}
			if(time == -1){
				pingTimeout++;
			}
			if(time == 0){
				corruptCount++;
			}
		}
		if(count != 0){
			double avgPeriod = (double)packetPeriod/count;
			packetRate += (((double)1000000/(avgPeriod * TIMESHIFT)) - packetRate)/SMOOTHING;
		}

		//test character io speed at 1/2 BUFFER
		unsigned long long int charHalfPeriod = 0;
		count = 0;
		for(int i = 0; i < RETRIES; i++){
			long int time = ping(BUFFER/2);
			if(time > 0){
				charHalfPeriod += time;
				count++;
				successCount++;
			}
			if(time == 0){
				corruptCount++;
			}
		}
		if(count != 0){
			double avgHalfCharPeriod = (double)charHalfPeriod/(count*BUFFER/2);
			charRate += (((double)1000000/(avgHalfCharPeriod * TIMESHIFT)) - charRate)/SMOOTHING;
		}

		//test character io speed
		unsigned long long int charPeriod = 0;
		count = 0;
		for(int i = 0; i < RETRIES; i++){
			long int time = ping(BUFFER);
			if(time > 0){
				charPeriod += time;
				count++;
				successCount++;
			}
			if(time == 0){
				corruptCount++;
			}
		}
		if(count != 0){
			double avgCharPeriod = (double)charPeriod/(count*BUFFER);
			charRate += (((double)1000000/(avgCharPeriod * TIMESHIFT)) - charRate)/SMOOTHING;
		}




		trials += RETRIES*3;


		//Print every second
		if(millis() - timeLast >= REFRESH){
			computer.println();
			fill(computer.print(millis()));
			fill(computer.print(trials));
			fill(computer.print(64000/(charRate)));
			fill(computer.print(packetRate));
			fill(computer.print(charRate));
			fill(computer.print(disconnects));
			fill(computer.print((double)100*corruptCount/(RETRIES*3)));
			fill(computer.print((double)100*packetFail/(packetFail+packetSuccess)));
			fill(computer.print((double)100*pingTimeout/RETRIES));


			if(diagCounter >= 50){
				printDiag();
				diagCounter = 0;
			}
			diagCounter++;
			timeLast = millis();
		}



		//Check for disconnect by timeout flag
		if(pingTimeout >= TIME_THRESH){
			computer.print("Disconnected");
			disconnects++;
			//wait for a connection again
			while(ping() == -1);
			//reset important variables
			charRate = 0;
			packetRate = 0;
			timeoutCount = 0;
		}

	}
}

void loop(){}
