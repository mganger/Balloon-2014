//This program runs a simple lowpass filter on a text file
//derived from filteredValue = oldValue + (newValue - oldValue) / (smoothing / timeSinceLastUpdate)
//from http://phrogz.net/js/framerate-independent-low-pass-filter.html
//Usage ./lowpass <amount> <file>
//10 is probably good enough for the amount
//This has been updated to use long double floating point precision (80 bits)
//The algorithm is so fast that we might as well be as precise as possible
//The longest part is literally writing to the file
//Note that this leads to about 5 times data expansion (.6 orders of magnitude)

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>					//for setprecision() for outfile

using namespace std;

//creates an array with the number of lines
int* atoiArray(stringstream& streamer, int* lineCount){
	
	//Go through the string and count the number of newlines
	cout << "Counting lines" << endl;
	string lineString = streamer.str();
	const char * lineChar = lineString.c_str();
	for(unsigned long int i = streamer.str().length(); i; i--){
		if(lineChar[i] == '\n'){
			lineCount[0]++;
		}
	}
	//Make a new array of that size
	cout << "Converting to ints" << endl;
	int* intConvert = new int[lineCount[0]];
	//convert the string line by line into that
	for(int i = 0; i < lineCount[0]; i++){
		string buff;
		getline(streamer, buff);
		intConvert[i] = atoi(buff.c_str());
	}

	return intConvert;
}

long double* atofArray(stringstream& streamer, int* lineCount){
	
	//Go through the string and count the number of newlines
	cout << "Counting lines" << endl;
	string lineString = streamer.str();
	const char * lineChar = lineString.c_str();
	for(unsigned long int i = streamer.str().length(); i; i--){
		if(lineChar[i] == '\n'){
			lineCount[0]++;
		}
	}
	//Make a new array of that size
	cout << "Converting to ints" << endl;
	long double* doubleConvert = new long double[lineCount[0]];
	//convert the string line by line into that
	for(int i = 0; i < lineCount[0]; i++){
		string buff;
		getline(streamer, buff);
		doubleConvert[i] = atof(buff.c_str());
	}

	return doubleConvert;
}

void lowpass(int * array, int size, int b){

	//do it forward and backward to avoid phase issues
	int oldvalue = array[0];
	cout << "Pass 1" << endl;
	for(int i = 0; i < size; i++){
		oldvalue += (array[i] - oldvalue) / b;
		array[i] = oldvalue;
	}
	cout << "Pass 2" << endl;
	oldvalue = array[size];
	for(int i = size; i == 0; i--){
		oldvalue += (array[i] - oldvalue) / b;
		array[i] = oldvalue;
	}
	return;
}

void lowpass(long double * array, int size, double b){

	//do it forward and backward to avoid phase issues
	long double oldvalue = array[0];
	cout << "Pass 1" << endl;
	for(int i = 0; i < size; i++){
		oldvalue += (array[i] - oldvalue) / b;
		array[i] = oldvalue;
	}
	cout << "Pass 2" << endl;
	oldvalue = array[size];
	for(int i = size; i == 0; i--){
		oldvalue += (array[i] - oldvalue) / b;
		array[i] = oldvalue;
	}
	return;
}


int main(int argc, char ** argv){
	if(argc != 3){
		cerr << "Wrong number of arguments" << endl;	
		return 34;
	}

	cout << "Copying file" << endl;
	stringstream fileStr;
	fstream file(argv[2], ios::in );
	fileStr << file.rdbuf();
	file.close();

	int lineCount = 0;
	long double* array = atofArray(fileStr, &lineCount);

	lowpass(array, lineCount, atof(argv[1]));

	cout << "Writing to file" << endl;
	ofstream outfile;
	outfile << setprecision(16);
	outfile.open("smooth.csv");
	for (int i = 0; i < lineCount; i++){
		outfile << array[i] << endl;
	}
	outfile.close();
}
