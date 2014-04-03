//This program is designed to pump something to a given tty so that it can be 
//used to test the serialtest program (funny and seemingly redundant, but whatever).

#include <fstream>
#include <time.h>
#include <iostream>
#include <fcntl.h>					//required to open and create files
#include <unistd.h>					//required to close the file
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

int main(int argc, char** argv){
	if(argc != 2){
		cerr << "Wrong number of arguments" << endl;
		return 1;
	}

	//open the file
	int fd = open(argv[1], O_NDELAY | O_RDWR);
	if (fd<0){
	   cerr << "Opening "<< argv[1] << " failed"<<endl;
	   return 1;
	}

	while(1){

		ostringstream time;

		time << clock();
		string timestr = time.str();
		cout << "Wrote " << write(fd, timestr.c_str(), timestr.size()) << " byte(s)" << endl;
		cout << "Should've written " << timestr.size() << " byte(s)" << endl;
		cout << clock() << endl;

		usleep(1000000);				//so we don't use up all the cpu
	}
}

