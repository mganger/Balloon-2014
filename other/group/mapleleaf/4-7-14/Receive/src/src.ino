/*
 * Kevin_Receive.ino
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
 *	This program is designed to receive the over the Rx of the serial port and
 *	print it over Tx (or USB serial if connected). Everything is bounced 
 *	verbatim.
 *
 *	This was composed by Kayla (although Michael also cleaned up the indents
 *	and added a few comments).
 */


void setup() {
	Serial.begin(9600); 
}

void loop() {
	if (Serial.available()>0){			//If something is in the buffer
		int characters = Serial.read();	//set integer to value of 1st char
		Serial.write(characters);		//Write that value to Tx
	}
}									//Loop through forever
