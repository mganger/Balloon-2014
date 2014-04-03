//This program is designed to test configuration of a device in C++
//If it can be successfully designed, the code will probably be copied under
//the Serial.begin() function in the Communications class
//After testing the specified baud rate, it attempts to set the specified tty
//to that baud. Then, it listens on the device (forever and inefficiently) for
//any incoming serial data. The best way to test is to set up the Arduino to
//print continously at a non-standard baud, and try to listen.
//	Use:
//		./serialTest $BAUD $PATH_TO_TTY (can be multiple)
//					NOTE:
//						If multiple files are given, only the first
//						only the first one is used
//
//TODO:	Determine if other flags (for setting the baud) are needed
//
//	CONFIRMED TO WORK (at 9600 and 19200 baud, so far)


#include <termios.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>					//required to open and create files
#include <unistd.h>					//required to close the file and sleep function
#include <stdio.h>
#include <stdlib.h>


using namespace std;
int fd = -1;						//global to hold the file descriptor


int setupSerial(unsigned int baudInt, const char* path){		//see $man termios


	fd = open(path,O_NDELAY | O_RDWR); 
	if (fd<0){
	   cerr<<"Opening "<< path << " failed"<<endl;
	   return 0;
	}

	long baudFloat;
	switch (baudInt)
	{
		case 0:
			default:
			cerr << baudInt << " is an invalid baud rate" << endl;
			break;
		case 115200:
			baudFloat = B115200;
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

void useThatSerial(){
	cout << "Listening:" << endl;
	char buff[2];					//create temporary read buffer
	while(1){						//listen forever!
	
		while(read(fd, buff,1) == 1){		//read 1 character into the buffer
			//log what it is reading from the device
				ofstream myfile("readlog.txt",std::ofstream::out | std::ofstream::app);
			//write it to a file
				myfile << buff[0];
			//print that character to stdout
				cout << buff[0];
			//close the file
			myfile.close();
		}
	
		while(cin.peek() != '\0'){			//check for chars in the buffer
			//log what you are sending to the device
				ofstream myfile("writelog.txt",std::ofstream::out | std::ofstream::app);
			//read a char from the buffer (and remove it)
				cin >> buff[0];
			//write to the log
				myfile << buff[0];
			//write to the device
				write(fd, buff,1);
			//close the file
			myfile.close();
		}
		usleep(10000);				//so we don't use up all the cpu
	}
}


int main(int argc, char* argv[]){

	for(int i = 2; i <= argc; i++){
	
		cout << "Opening "<< argv[i] <<endl;
		if(setupSerial(atoi(argv[1]), argv[i])){
				cout << "Success. You just changed the baud rate to "<< argv[1] << endl;
				useThatSerial();
			}	
		}
	return 0;
}

