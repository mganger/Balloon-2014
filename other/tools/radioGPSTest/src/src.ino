/*
 * Radio GPS Test
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
 * 
 * This program is a really simple program designed to bounce the gps data from
 * software serial to hardware serial.
 */

#include <SoftwareSerial.h>

void setup(){

	Serial.begin(115200);
	Serial.print("Initializing gps...");

	SoftwareSerial gps(3,2);	//Rx,Tx
	gps.begin(9600);

	Serial.println("Alpha One-Two, Check. Over");
	gps.print('0');
	Serial.println("GPS Ready");
	Serial.println();

	unsigned long int timeLast= millis();
	while(1){
		if(gps.available()){
			Serial.write(gps.read());
		}
		if(millis()-timeLast >= 10000){
			Serial.println("KD2BJD");
			Serial.println();
			timeLast = millis();
		}
	}

}

void loop(){}

