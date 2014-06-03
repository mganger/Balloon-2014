//program to combine the o3 files into one
//assumes that each line number has the same index
//usage: ./combine $file1 $file2

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
	if(argc != 3){
		cerr << "Can't take " << argc << " arguments" << endl;
		return 1;
	}

	ifstream in1(argv[1]);
	stringstream in1stream;
	in1stream << in1.rdbuf();
	int linecount = countlines(in1stream);
	ifstream in2(argv[2]);
	stringstream in2stream;
	in2stream << in2.rdbuf();
	int linecount2 = countlines(in2stream);

	in1.close();
	in2.close();

	if(linecount != linecount2){
		cerr << argv[1] << " has " << linecount << " lines, while ";
		cerr << argv[2] << " has " << linecount2 << " lines." << endl;
		return 1;
	}

	cout << linecount << " lines" << endl;
	
	//change the name of the file
	stringstream ifilename;
	ifilename << argv[1];
	string ofilename;
	getline(ifilename,ofilename, '.');
	ofilename += "_combined.csv";

	ofstream out(ofilename.c_str(), ios::trunc);
	for(int i = 0; i < linecount; i++){
		string buff1, buff2;
		getline(in1stream, buff1);
		getline(in2stream, buff2);
		out << (atof(buff1.c_str()) + atof(buff2.c_str()))/2 << endl;
	}
	return 0;
}
