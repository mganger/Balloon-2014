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

int setupSerial(unsigned int baud, const char* path){		//see $man termios


	int fd = open(path,O_NDELAY);
	if (fd<0){
	   cerr<<"opening failed"<<endl;
	   fd=-1;
	   return 1;
	}

	struct termios options;			//create a structure to hold serial info
	tcgetattr(fd, &options);			//get current options for port

	cfsetispeed(&options, baud);		//set input baud
	cfsetospeed(&options, baud);		//set output baud

//	options.c_cflags |= (CLOCAL | CREAD);	//set the flags
//	options.c_cflags &= ~PARENB			//*These options say no parity bit
//	options.c_cflags &= ~CSTOPB			//*Not sure how to use them
//	options.c_cflags &= ~CSIZE;			//*
//	options.c_cflags |= CS8;				//*


	if(tcsetattr(fd, TCSANOW, &options)<0){	//set new options 
	cerr << "You did something wrong, dummy." << endl;
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

