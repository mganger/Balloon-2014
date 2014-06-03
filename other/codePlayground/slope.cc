//program to apply a calibration curve to the file. Assumes that the input file
//is y, and the output is x (x = (y-b)/m)
//usage: ./slope $m $b $file

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int countlines(stringstream& streamer){

	int linecount = 0;

	//Go through the string and count the number of newlines
	string lineString = streamer.str();
	const char * lineChar = lineString.c_str();
	for(unsigned long int i = streamer.str().length(); i; i--){
		if(lineChar[i] == '\n'){
			linecount++;
		}
	}
	return linecount;
}


int main(int argc, char** argv){
	if(argc != 4){
		cerr << "Can't take " << argc << " arguments" << endl;
		return 1;
	}

	double m = atof(argv[1]);
	double b = atof(argv[2]);

	ifstream in(argv[3]);
	stringstream instream;
	instream << in.rdbuf();
	int linecount = countlines(instream);
	in.close();

	cout << linecount << " lines" << endl;
	
	//change the name of the file
	stringstream ifilename;
	ifilename << argv[3];
	string ofilename;
	getline(ifilename,ofilename, '.');
	ofilename += "_calibrated.csv";

	ofstream out(ofilename.c_str(), ios::trunc);
	for(int i = 0; i < linecount; i++){
		string buff;
		getline(instream, buff);
		out << (atof(buff.c_str())-b)/m << endl;
	}
	out.close();
	return 0;
}
