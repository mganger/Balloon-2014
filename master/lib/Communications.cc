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
#include <string>				//library to create string objects
#include <fstream>				//library for reading and writing files
#include <iostream>				//necessary for cout
#include <termios.h>
#include <fcntl.h>				//required to open and create files
#include <unistd.h>				//required to close the file
#include <stdio.h>
#include <stdlib.h>


char Communications::gather(){
	char buff[2];
	read(fileDescriptor, buff, 1);
	return buff[1];
}

int Communications::gather(string serialString){
	serialString = "";			//Clear string

	int counter = 0;
	for(char tmpBuffer;tmpBuffer != '\n';counter++){
		if(read(fileDescriptor, &tmpBuffer, 1) <= 0){
			break;
		}
		serialString += tmpBuffer;
	}
	return counter;
}

int Communications::setup(unsigned int baudInt,const char* path){
	fileDescriptor = open(path,O_NDELAY);
	if (fileDescriptor<0){
	   cerr<<"Opening failed"<<endl;
	   return 0;
	}

	long baudFloat;
	switch (baudInt)				//take int and return 
	{
		case 0:
			default:
			cerr << baudInt << " is an invalid baud rate" << endl;
			break;
		case 38400:
			baudFloat = B38400;
			break;
		case 19200:
			baudFloat  = B19200;
			break;
		case 9600:
			baudFloat  = B9600;
			break;
		case 4800:
			baudFloat  = B4800;
			break;
		case 2400:
			baudFloat  = B2400;
			break;
		case 1800:
			baudFloat  = B1800;
			break;
		case 1200:
			baudFloat  = B1200;
			break;
		case 600:
			baudFloat  = B600;
			break;
		case 300:
			baudFloat  = B300;
			break;
		case 200:
			baudFloat  = B200;
			break;
		case 150:
			baudFloat  = B150;
			break;
		case 134:
			baudFloat  = B134;
			break;
		case 110:
			baudFloat  = B110;
			break;
		case 75:
			baudFloat  = B75;
			break;
		case 50:
			baudFloat  = B50;
			break;
	}



	struct termios options;		//create a structure to hold serial info
	tcgetattr(fileDescriptor, &options);		//get current options for port

	if(cfsetispeed(&options, baudFloat)<0){		//set input baud
		cerr << "Cannot set the input baud to " << baudInt << endl;
		return 0;
	}
	if(cfsetospeed(&options, baudFloat)<0){		//set output baud
		cerr << "Cannot set the output baud to " << baudInt << endl;
		return 0;
	}

//	options.c_cflags |= (CLOCAL | CREAD);	//set the flags
//	options.c_cflags &= ~PARENB			//*These options say no parity bit
//	options.c_cflags &= ~CSTOPB			//*Not sure how to use them
//	options.c_cflags &= ~CSIZE;			//*
//	options.c_cflags |= CS8;				//*


	if(tcsetattr(fileDescriptor, TCSANOW, &options)<0){	//set new options
	cerr << "Cannot set attributes." << endl;
	return -1;
	} else return fileDescriptor;				//return happiness

}
