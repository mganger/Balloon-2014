#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

int calcSum(string data){
	char b = 0;
	for(int i = 0;i < data.length();i++)
	{
		b = b ^ data.at(i);
	}
	return b;
}

int main(int argc, char** argv){

	//Argument testing
	if(argc != 3){
		cerr << "Can't take " << argc -1 << " arguments." << endl;
		return 0;
	}

	string sttyControl = "stty -F ";
	sttyControl += argv[1];
	sttyControl += " ";
	sttyControl += argv[2];
	cout << sttyControl;
	system(sttyControl.c_str());

	fstream device;
	device.open(argv[1]);

	//Error handling
	if(!device.is_open()){
		cerr << "Can't open " << argv[1] << endl;
	}

	ofstream rawDataFile("rawData.csv",ios::app);
	ofstream badDataFile("badData.csv",ios::app);
	while(1){
		string garbage;
		string data;
		string check = "00";
		getline(device,garbage,'$');
		cout << garbage;
		getline(device,data,'*');
		check[0] = device.get();
		check[1] = device.get();
		cout << data << check << ',';
		int checksum = calcSum(data);
		int humansum = ((int)check.at(0) - 48) * 16 + (int)check.at(1) - 48;
		if(checksum == humansum)
		{
			rawDataFile << data << endl;
		}else{
		cout << "CORRUPTED DATA HAS BEEN RECEIVED";
			badDataFile << data << endl;
		};
//		cout << calcSum(data) << ',';
//		cout << ((int)check.at(0) - 48) * 16 + (int)check.at(1) - 48 << endl;
	}
}
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
//	./serialstreamtest $DEVICEPATH $BAUD

