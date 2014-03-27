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



#include <arduino.h>
#include <stdio.h>
#include <MD5.h>

void setup()
{
	Borp radio;
	radio.Borp(1,9600);
		//Baud rate and pin should be hardcoded by each group.
}

void loop()
{
	//while (time<alloted){
	//	check for connection request
	//	}
	//send feedback to master
	//collect data
	//write data
	//if (connection == 1){
	//	check for data request
	//	prepare data
	//	send data
	//	}
	Data point;
	point.recordData(temp,pres,CO2_); //Fill in collected data baszed on group.
	radio.phoneHome(point);
	
}
