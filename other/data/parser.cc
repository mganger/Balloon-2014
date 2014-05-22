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
	ifstream file("battery.log");
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
	cout << "Outputing in the format HOURS,VOLTAGE,WATTAGE" << endl;

	//Read the csv line into variables
	ifstream input("battery.log");
	ofstream output("output.csv", ios::trunc);
	ofstream wattageFile("wattage.csv", ios::trunc);
	string time;
	string clock;
	string readingStr;
	//add up all the wattage values
	long double watts = 0;
	long double wattHrTotal = 0;

	for(int i = 0; i < lineNumber; i++){
		getline(input, time, ',');
		getline(input, clock, ',');
		getline(input, readingStr, '\n');
		int reading = atoi(readingStr.c_str());
//		output << atof(time.c_str())/3600000 << ',' << atof(reading.c_str()) / 182.33 << endl;
		if(reading > 547){
			long double voltage = reading / 182.33;
			watts = voltage * voltage / 75;
			wattHrTotal += watts *.1 /3600;
//			wattageFile << time.c_str() << ',' << watts << ',' << wattHrTotal / 3600000 << endl;
		}
	}
	cout << wattHrTotal << endl;
	return 0;
}
