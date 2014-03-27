//This program is designed to test configuration of a device in C++
//If it can be successfully designed, the code will probably be copied under
//the Serial.begin() function in the Communications class
//
//	Use:
//		./serialTest $PATH_TO_TTY $BAUD
//
//TODO:	Check validity of baud rate
//		Figure out the flags that need to be set (may be none)
//		Write to the specified tty and read after that
//			->we can bounce the characters from the Arduino

#include <termios.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>					//required to open and create files
#include <unistd.h>					//required to close the file
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int setupSerial(unsigned int baudInt, const char* path){		//see $man termios


	int fd = open(path,O_NDELAY);
	if (fd<0){
	   cerr<<"Opening failed"<<endl;
	   return 0;
	}

	long baudFloat;
	switch (baudInt)
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
	tcgetattr(fd, &options);		//get current options for port

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


	if(tcsetattr(fd, TCSANOW, &options)<0){	//set new options
	cerr << "Cannot set attributes." << endl;
	return 0;
	} else return 1;					//return happiness
}

int main(int argc, char* argv[]){
//	string path = "/dev/tty10";
	cout << "Opening "<< argv[1] <<endl;
	if(setupSerial(atoi(argv[2]), argv[1])){
		cout << "Success. You just changed the baud rate to "<< argv[2] << endl;
		return 0;
	}else return 1;
}

