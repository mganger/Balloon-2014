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




#include <stdio.h>
#include "../lib/MD5.h"
#include "../lib/MD5.cpp"
#include "../lib/Borp.h"
#include "../lib/Borp.cc"
#include "../lib/Data.h"
#include "../lib/Data.cc"

void setup()
{
	
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
	point.readSensorData(); //Fill in collected data baszed on group.
	Borp radio(1,9600);	//Baud rate and pin should be hardcoded by each group.
	radio.phoneHome(point.returnData());
	
}