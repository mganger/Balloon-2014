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

//This program is designed to send an indexed line with arbitrary numbers in
//order to test the master's ability to index
#define PERIOD 100


void setup(){
	Serial.begin(115200);
	Serial.print("Intitializing...\n");
	unsigned long int timeLast = 0;
	unsigned long int counter = 0;

	for(;;){
		if(millis() - timeLast >= PERIOD){
			timeLast = millis();
			Serial.print(counter);
			Serial.print(",");
			Serial.print(random(5000));
			Serial.print("\r\n");
			counter++;
		}
	}
}

void loop(){
	Serial.println("Error: entered loop");
}
