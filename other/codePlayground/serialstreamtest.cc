/*
 * serialstreamtest.cc
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

//This code reads streams from a tty
//It does not set the baud rate, so it must be used within a script that sets
//the baud rate (like stty)

//NOTE: This is far superior to the original serialtest! It currently does not
//take input

//Usage:
//	./serialstreamtest $DEVICEPATH

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char** argv){

	//Argument testing
	if(argc != 2){
		cerr << "Can't take " << argc -1 << " arguments." << endl;
		return 0;
	}

	fstream device;
	device.open(argv[1]);

	//Error handling
	if(!device.is_open()){
		cerr << "Can't open " << argv[1] << endl;
	}

	while(1){
		string line;
		getline(device,line, '\n');
		cout << line << endl;
	}
}
