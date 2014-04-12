//This program runs a simple lowpass filter on a text file
//derived from filteredValue = oldValue + (newValue - oldValue) / (smoothing / timeSinceLastUpdate)
//from http://phrogz.net/js/framerate-independent-low-pass-filter.html
//Usage ./lowpass <amount> <file>
//10 is probably good enough for the amount

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

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
	int* array = atoiArray(fileStr, &lineCount);

	lowpass(array, lineCount, atoi(argv[1]));

	cout << "Writing to file" << endl;
	ofstream outfile;
	outfile.open("smooth.csv");
	for (int i = 0; i < lineCount; i++){
		outfile << array[i] << endl;
	}
	outfile.close();
}
