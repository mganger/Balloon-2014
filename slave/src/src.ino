/*
 * slave.cc
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

#define BAUD 9600
#define PERIOD 1000/FREQ			//period in milliseconds
#define FREQ 10					//frequency of readings
#define SIZE 14					//keep updated with actual number

#include "MD5.h"
#include "Borp.h"
#include "Data.h"




void setup(){
	//Constuct data and radio (at 115200 baud
	Borp radio;
	Data data;

	for(;;){

		while(Serial.available() == 0){}

		delay(2);

		unsigned long int flag = radio.listen();
		radio.phoneHome(&flag, 1);

		

		//This just waits until the time to the last collect is equal to PERIOD
//		while((millis() - point.timeSince())<PERIOD){}
	}
}

//Leave loop empty; let's try using the setup as a main function (or better,
//call loop from the setup program). However, if putting everything in setup 
//doesn't work, we can put everything within loop and never let it finish
void loop(){
	Serial.println("ERROR: Completed setup and entered loop");
	delay(1000);
}







