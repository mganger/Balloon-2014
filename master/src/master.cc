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
 * Current Dependencies:
 *	openssl headers (openssl-devel on fedora)
 *		NOT ANYMORE. MD5 capability in the hash-library
 */


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/Communications.h"
#include "../lib/Communications.cc"

using namespace std;

//takes a string, parses index, writes to unique file, returns 1 with success,
//0 with error. Note that the files it generates don't have filler zeros (not
//necessary
int writePoint(string data){
	//generate the filename string
	string fileName;
	fileName = "datapoint_";
	const char* tmp = data.c_str();
	//extract index (the first number) to go in name
	//robustly handles errors
	for(unsigned int i = 0; i < data.length(); i++){
		switch (tmp[i]){
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
				fileName += tmp[i];
			case ',':
				break;
			default:
				cout << "Invalid character " << tmp[i] << " in index" << endl;
				return 0;
		}
	}

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
	return 1;
}


int main(int argc, char** argv)
{
	if(argc != 2){
		cerr << "Wrong number of arguments" << endl;
		return 0;
	}


	Communications Serial;
	ofstream outputFile;

	Serial.setup(115200,argv[1]);
	string serialString;
	if(Serial.gather(serialString)){
		//error handling if Serial.gather returns a 0
	}

	writePoint(serialString);
	outputFile.open("ballonData.dat",ios::app);




}
