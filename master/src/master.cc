/*
 * master.cc
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
 *
 * USAGE: ./master <DEVICE PATH> ...
 * Explicitly uses 115200 baud
 */


#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/Communications.h"
#include "../lib/Communications.cc"

using namespace std;

//takes a string, parses index, writes to unique file, returns 1 with success,
//0 with error. Note that the files it generates don't have filler zeros (not
//necessary)
int writePoint(string data){
	//generate the filename string
	string indexString;
	string fileName;
	fileName = "datapoint_";
	//extract index (the first number) to go in name
	bool caseEnd = 1;
	for(unsigned int i = 0; (i < data.length() ) & (caseEnd); i++){
		switch (data.at(i)){
			case ',':
				caseEnd = 0;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				indexString += data.at(i);
				break;
			default:
				cout << "Invalid character " << data.at(i) << " in index" << endl;
				return 0;
		}
	}

	//Check to see how many numbers are in it, put into file name with zeros
	for(unsigned int i = 0; i < (15 - indexString.length()); i++){
		fileName += '0';
	}
	fileName += indexString.c_str();


	//if it already exists, we don't want to write over it
	//we might be able to recursively runs some stuff
	if (ifstream(fileName.c_str())){
		cout << "File " << fileName.c_str() << " already exists" << endl;
		return 0;
	}

	ofstream outfile;
	outfile.open(fileName.c_str());
	outfile << data;
	outfile.close();


//writes the largest point taken in the directory to "lastfile"
	fstream filenumber;
	filenumber.open("lastfile", ios::in);
	string fileNumberToBeUsedForGetline;
	getline(filenumber,fileNumberToBeUsedForGetline);
	filenumber.close();
	if(atoi(fileNumberToBeUsedForGetline.c_str()) < atoi(indexString.c_str())){
		filenumber.open("lastfile", ios::trunc | ios::out);
		filenumber << indexString.c_str();
		filenumber.close();
	}
	return atoi(indexString.c_str());
}

//This function looks at all the data and returns the latest point that needs
//TODO: have this function write the unreceived points to a file and read that
//when returning need points. That way, it could probably handle billions of files
int findPoint(int lastpoint){
	for(int i = lastpoint-1; i; i--){
		string filename;
		filename = "datapoint_";
		stringstream filenumber;
		filenumber << i;
		for(unsigned int j = 0; j < (15 - filenumber.str().length()); j++){
			filename += '0';
		}
		filename += filenumber.str();

		ifstream file(filename.c_str());
		if(file.is_open() == 0){
			return i;
		}
		file.close();
	}

	return 0;
}

int main(int argc, char** argv)
{
	if(argc != 2){
		cerr << "Wrong number of arguments: " << argc - 1 << endl;
		return 0;
	}

	fstream deviceFile;
	deviceFile.open(argv[1], ios::in);

	//Check to see if the file exists
	if(!deviceFile.is_open()){
		cerr << "Invalid device: " << argv[1] << endl;
	}

	int lastPoint;
	for(;;){
		string line;
		getline(deviceFile, line);
		lastPoint = writePoint(line);

		int requestPoint;
		if(lastPoint == 0){
			cout << "Couldn't write file" << endl;
			continue;
		}
		requestPoint = findPoint(lastPoint);

		//If a point needs to be resent, it has to open and close the
		//file connection. Otherwise, things break
		if(requestPoint){
			deviceFile.close();
			deviceFile.open(argv[1], ios::out);
			deviceFile << "request " << requestPoint << endl;
			deviceFile.close();
			deviceFile.open(argv[1], ios::in);
		}
	}
	deviceFile.close();
}
