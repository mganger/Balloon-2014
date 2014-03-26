/*
 * Communications.cc
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


#include "Communications.h"
#include <string>					//library to create string objects
#include <fstream>					//library for reading and writing files
#include <iostream>					//necessary for cout

int Communications::begin(std::string path){
	std::fstream device;
	device.open(path.c_str());
	if(device.is_open() == 0){		//if device is not open
		std::cout << "Error opening device\n";
		device.close();
		return 0;					//return 0 (false) if unsuccessful
	}
	else {
		serialPath = path;			//save the path within the object
		std::cout << "Successfully opened device\n";
		device.close();
		return 1;					//return 1 (true) if successful
	}
}
