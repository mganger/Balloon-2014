//This is a program designed specifically to parse the battery data. It uses
//the calibration, and finds both the voltage and wattage relationship in SI.
//It may work with other files. YMMV
//
//Usage:
//	./parser $INPUT_FILE $OUTPUT_FILE

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv){

//	if(argc != 2){
//		cout << "Wrong number of arguments" << endl;
//		return 0;
//	}

	//count the number of lines
	int lineNumber;
	ifstream file("humidity.log");
	string check;
	for(int i = 0;;){
		getline(file,check,'\n');
		if(check == ""){
			lineNumber = i;
			file.close();
			break;
		}
		i++;
	}
	cout << lineNumber << " lines in the file" << endl;
	cout << "Outputing in the format HOURS,HUMIDITY" << endl;

	//Read the csv line into variables
	ifstream input("humidity.log");
	ofstream output("output.csv", ios::trunc);
	string time;
	string clock;
	string readingStr;

	for(int i = 0; i < lineNumber; i++){
		getline(input, time, ',');
		getline(input, clock, ',');
		getline(input, readingStr, '\n');
		int reading = atoi(readingStr.c_str());
		long double humidity = ((double)reading-169.2266423755) / 6.34297802915;
		output << atof(time.c_str()) / 3600000 << ',' << humidity << endl;
	}
	return 0;
}
