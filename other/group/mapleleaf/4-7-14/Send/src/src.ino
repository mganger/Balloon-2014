/*
 * src.ino
 * This file is part of Balloon Program
 *
 * Copyright (C) 2014 - Team Maple Leaf
 *
 * Balloon Program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Balloon Program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Balloon Program. If not, see <http://www.gnu.org/licenses/>.
 *
 *README
 *======
 *	This program is designed to read the data from (currently) analog pins,
 *	store this data in an array, send this array as text (ASCII) over ttl 
 *	serial between two Arduinos, and bounce whatever is received on the second
 *	Arduino to the computer (via serial).
 *
 *	Each part of the program was accomplished separately, in three separate
 *	files. These should have been included with this program. The work was
 *	divided as follows:
 *		Jordan:	read from the pins
 *		Olivia:	send the data over ttl
 *		Kayla:	read the data and bounce to computer
 *		Michael:	concatenate the programs, produce the working system
 *					->I touched it as little as possible
 *					->I did clean up the indenting a bit
 *					->I also added comments
 *
 *	The indiviual parts are denoted by comments in this file and the other
 */

//Jordan-------------------Setup the sensor pins
int ht = A0;				//
int pt = A1;				//
int co2 = A2;				//carbon dioxide 
int no2 = A3;				//nitrous oxide
int o3 = A4;				//ozone
int p = A5;				//pressure

//Put them into an array for convenience
int SensorArray[6] = {ht, pt, co2, no2, o3, p};

void setup() {
	Serial.begin(9600);
//Jordan-------------------Setup up the pins. This could probably be a loop
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	pinMode(A4, INPUT);
	pinMode(A5, INPUT);
}

void loop() {

//Jordan-------------------
	int dataArray[6] = {-1};			//create an array to hold the readings
	for(int i = 0; i<= 5; i++){		//loop through the pins to read the data
		//Put the data at a certain pin into the array
		dataArray[i] = analogRead(SensorArray[i]);
	} 
//Olivia-------------------
	for (int i=0; i<=5; i++){		//print the data from the array
		Serial.println(dataArray[i]);
		delay (1000);				//won't need this
	}
}

