/*
 * lowpass.cc
 * This file is part of Sinc Lowpass Filter
 *
 * Copyright (C) 2014 - Michael Ganger
 *
 * Sinc Lowpass Filter is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Sinc Lowpass Filter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sinc Lowpass Filter. If not, see <http://www.gnu.org/licenses/>.
 */

//This code runs an (almost) ideal lowpass filter on input data.
//As it uses a stream, it can easily be adapted to any project
//	Usage:
//		./lowpass <frequency> <filtersize> <pathToSingleLineText>
//
//Period is the cutoff (in given by the sample width of the frequency) and needs
// to be in the range (2,inf). Filter size directly relates to the length
//of computation time (but also to quality, so don't be too stingy with cpu 
//time). A good rule of thumb is to have the filter size be at least 5x the 
//cutoff period. 
 


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <new>
#include <iomanip>				//for setprecision() for outfile


using namespace std;
//Converted from The Scientist and Engineer's Guide to Digital Signal Processing
//pg 294

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
	cout << "Converting to floats" << endl;
	long double* doubleConvert = new long double[lineCount[0]];
	//convert the string line by line into that
	for(int i = 0; i < lineCount[0]; i++){
		string buff;
		getline(streamer, buff);
		doubleConvert[i] = atof(buff.c_str());
	}

	return doubleConvert;
}

int main(int argc, char ** argv){

	if(argc != 4){
		cerr << "Wrong number of arguments" << endl;	
		return 34;
	}

	double amount = 1/atof(argv[1]);
	if(amount <= 0){
		cerr << "Amount is too small (0 < amount < .5)" << endl;
		return 35;
	}

	if(amount >= .5){
		cerr << "Amount is too large (0 < amount < .5)" << endl;
		return 36;
	}


	int filterSize = atoi(argv[2]);
	if(filterSize%2 == 0){
		argc++;
	}

	cout << "Copying file" << endl;
	stringstream fileStr;
	fstream file(argv[3], ios::in );
	fileStr << file.rdbuf();
	file.close();

	int length = 0;
	long double* input = atofArray(fileStr, &length);

	if(length < 2*filterSize){
		cerr << "Filter size is too large for the input data length" << endl;
		return 37;
	}

	cout << length << " data points" << endl;

//	//put random noise into the array
//	int switcher = -1;
//	for(int i = 0; i < length; i++){
//		srand(time(NULL)+i);
//		input[i] = rand()*switcher;
//		switcher *= -1;
//	}


	cout << "Creating output array" << endl;
	double * output = new double[length];

	cout << "Creating sinc filter" << endl;
	double pi = 3.14159265358979323846264338327950288419716939;
	double cutoff = amount;			//Keep between 0 and .5
	double * sincFilter = new double[filterSize];

	//Calculates lowpass filter
	//Only does it in one direction (so we only get 1/2 of the filter)
	sincFilter[0] = 2 * pi * cutoff;
	for (int i = 1; i < filterSize; i++){
		sincFilter[i] = sin(2 * pi * cutoff * i) / i;
	}

	//Applies a Blackmann window to the filter
	for (int i = 0; i < filterSize; i++){
		sincFilter[i] *= 0.54 - 0.46 * cos(pi + 2 * pi * i / (filterSize * 2));
	}

//	Outputs the sinc filter to a file for easy viewing
//	ofstream sincfile;
//	sincfile.open("sinc.csv");
//	for(int i = 0; i < filterSize; i++){
//		sincfile << sincFilter[i] << endl;
//	}
//	sincfile.close();
//	return 0;

	//Normalize the lowpass filter for unity gain
	//First integrate the parts, then divide every sameple by the sum
	double sum;
	sum = sincFilter[0];
	for (int i = 1; i <filterSize + 1; i++){
		sum += 2 * sincFilter[i];
	}

	for(int i = 0; i < filterSize +1; i++){
		sincFilter[i] /= sum;
	}

	cout << "Normalized filter to " << log(1/sum)*10 << " dB" << endl;

	//Convolve the input signal in three parts, on the end pretending like
	//the edges are zero (or that they don't exist)



	//front edge
	cout << "Convolving front edge" << endl;
	for(int i = 0; i < filterSize; i++){
		double buffer = input[i] * sincFilter[0];
		for(int j = 1; j < filterSize; j++){
			buffer += input[i + j] * sincFilter[j];
			if(i-j >= 0) {
				buffer += input[i-j] * sincFilter[j];
			}else{
				buffer += input[0] * sincFilter[j];
			}
		}
		output[i] = buffer;
	}

	//back edge
	cout << "Convolving back edge" << endl;
	for(int i = length - filterSize-1; i < length ; i++){
		double buffer = input[i] * sincFilter[0];
		for(int j = 1; j < filterSize; j++){
			buffer += input[i - j] * sincFilter[j];
			if(i+j <= length) {
				buffer += input[i+j] * sincFilter[j];
			}else{
				buffer += input[length-1] * sincFilter[j];
			}
		}
		output[i] = buffer;
	}

//	cout << input[length-1] << endl;

	//main convolution
	cout << "Performing main convolution" << endl;
	for(int i = filterSize; i < length-filterSize; i++){
		double buffer = input[i]* sincFilter[0];
		for(int j = 1; j < filterSize; j++){
			buffer += input[i-j] * sincFilter[j];
			buffer += input[i+j] * sincFilter[j];
		}
		output[i] = buffer;
	}

	cout << "Writing to file with 16 significant figures" << endl;

	//change the name of the file
	stringstream ifilename;
	ifilename << argv[3];
	string ofilename;
	getline(ifilename,ofilename, '.');
	ofilename += "_lowpass.csv";


	ofstream outfile;
	outfile.open(ofilename.c_str());
	outfile << setprecision(16);
	for (int i = 0; i < length; i++){
		outfile << output[i] << endl;
	}
	outfile.close();

}
