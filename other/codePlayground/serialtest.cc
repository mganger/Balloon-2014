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
#include <fcntl.h>			//required to open and create files
#include <unistd.h>			//required to close the file and sleep
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <ctime>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>

#define PERIOD 1			//Change if stuff is getting cut off
#define SENDNEW 0			//0 to skip \n and \r, 1 to send them
					//It will still log them, though (this
					//is a good thing)

using namespace std;
int fd = -1;				//global to hold the file descriptor



//see $man termios for more information on this
int setupSerial(unsigned int baudInt, const char* path){	

	//Open the device, set flags, return file descriptor
	fd = open(path,O_NDELAY | O_RDWR | O_NOCTTY | O_NONBLOCK); 

	//If the device cannot be opened, fd = -1
	if (fd<0){
	   cerr<<"Opening "<< path << " failed"<<endl;
	   return 0;
	}

	//change the ints to bauds (long numbers that are't intuitive)
	long baudLong;
	switch (baudInt)
	{
		case 0:
			default:
			cerr << baudInt << " is an invalid baud rate" << endl;
			break;
		case 115200:
			baudLong = B115200;
			break;
		case 38400:
			baudLong = B38400;
			break;
		case 19200:
			baudLong  = B19200;
			break;
		case 9600:
			baudLong  = B9600;
			break;
		case 4800:
			baudLong  = B4800;
			break;
		case 2400:
			baudLong  = B2400;
			break;
		case 1800:
			baudLong  = B1800;
			break;
		case 1200:
			baudLong  = B1200;
			break;
		case 600:
			baudLong  = B600;
			break;
		case 300:
			baudLong  = B300;
			break;
		case 200:
			baudLong  = B200;
			break;
		case 150:
			baudLong  = B150;
			break;
		case 134:
			baudLong  = B134;
			break;
		case 110:
			baudLong  = B110;
			break;
		case 75:
			baudLong  = B75;
			break;
		case 50:
			baudLong  = B50;
			break;
	}



	struct termios options;			//create a structure to hold serial info
	tcgetattr(fd, &options);		//get current options for port

	//set input and output baud
	if(cfsetispeed(&options, baudLong)<0){
		cerr << "Cannot set the input baud to " << baudInt << endl;
		return 0;
	}
	if(cfsetospeed(&options, baudLong)<0){
		cerr << "Cannot set the output baud to " << baudInt << endl;
		return 0;
	}

//	options.c_cflags |= (CLOCAL | CREAD);	//set the flags
//	options.c_cflags &= ~PARENB;		//*These options say no parity bit
//	options.c_cflags &= ~CSTOPB;		//*Not sure how to use them
//	options.c_cflags &= ~CSIZE;		//*They weren't working,
//	options.c_cflags |= CS8;		//*either


	cfmakeraw(&options);
	tcflush(fd, TCIOFLUSH);

	//set the new options for the device (i.e. baud)
	if(tcsetattr(fd, TCSANOW, &options)<0){
	cerr << "Cannot set attributes." << endl;
	return 0;
	} else return 1;			//return happiness
}

void useThatSerial(){
	cout << "Listening:" << endl;

	//timestamp----------------------------------------------------------------
	ostringstream timeStream;
	time_t now = time(0);
	tm *ltm = localtime(&now);		//make new time structure

	//create the stream for the timestamp
//	timeStream << endl << "--------------------------"<< endl;
	timeStream << ltm->tm_hour <<"."<< ltm->tm_min <<"."<< ltm->tm_sec;
	timeStream << "," ;
	timeStream << 1+ltm->tm_mon <<"-"<< ltm->tm_mday <<"-"<< 1900+ltm->tm_year;


	//create a string holding the current time
	ofstream writefile("logWrite.txt",std::ofstream::out | std::ofstream::app);
	writefile << "---------------------------------------" << endl;
	writefile << timeStream.str();
	writefile << endl << endl;
	writefile.close();

	//Add log suffix to the timestamped file
	timeStream << "_log.txt";

	ofstream readfile(timeStream.str().c_str(),std::ofstream::out | std::ofstream::app);
	readfile.close();
	//timestamp----------------------------------------------------------------


	struct pollfd fds;			//necessary so that stdin does not
	fds.fd = 0;				//block our program
	fds.events = POLLIN;


	char outBuff[2];			//create read buffer
	char inBuff[2];				//create write buffer

	//loop forever!!!!!
	for(;;){
		while(read(fd, outBuff,1) > 0){	//read 1 character into the buffer
			//log what it is reading from the device
				ofstream myfile(timeStream.str().c_str(),std::ofstream::out | std::ofstream::app);
			//write it to a file
				myfile << outBuff[0];
			//print that character to stdout
				cout << outBuff[0];
			//close the file
			myfile.close();
			usleep(PERIOD);
		}
	
		while(poll(&fds, 1, 0) > 0){		//read character from stdin
			//read the char into buffer
			read(0, inBuff, 1);

			//log what you are sending to the device
				ofstream myfile("logWrite.txt",std::ofstream::out | std::ofstream::app);
			//write to the log
				myfile << inBuff[0];
			//write to the device
			//Doesn't send a newline character (who wants 'em, anyway?)
				if(((inBuff[0] != '\n') & (inBuff[0] != '\r')) | SENDNEW){
					write(fd, inBuff,1);
				}
			//close the file
			myfile.close();
			usleep(PERIOD);
		}
		usleep(1000);			//so we don't use up all the cpu
	}
}


//takes baud and device arguments (can take multiple devices)
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

