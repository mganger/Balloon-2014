//This code runs a lowpass filter on the data

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <new>


using namespace std;

/*
//Generates 1/2 the sinc function
void genSinc(double * sinc, int length, int freq){
	sinc[0]=1;
	for(int i = 1; i< length; i++){
		sinc[i] = sin(.1*i)/i;
	}
}

void print(double * array, int size){
	for(int i=0; i<size; i++){
		std::cout << array[i] << std::endl;
	}
}


void print(int * array, int size){
	for(int i=0; i<size; i++){
		std::cout << array[i] << std::endl;
	}
}

void noiseGen(int*noise, int size){
	for(int i = 0; i < size; i++){
		srand(time(NULL)+i*i);
		noise[i] = rand()/1000000;
	}
}

void convolver(int * input, int inputSize, double *filter, int filterSize){
	double buffer[inputSize];
	for(int i = 0; i<inputSize; i++){
		buffer[i]=0;
	}
	for(int i = filterSize - 1; i < (inputSize - filterSize + 1); i++){
		buffer[i] += input[i];
		for(int j = 1; j < filterSize; j++){
			buffer[i+j] += input[i]*filter[j];
			buffer[i-j] += input[i]*filter[j];
		}
	}
	for(int i = 0; i< inputSize; i++){
		input[i] = buffer[i];
	}
}

void csvOut(int* a1,int size){
	std::fstream csv("data.csv", std::fstream::trunc | std::fstream::out);
	for (int i = 0; i < size; i++){
		csv << a1[i] << std::endl;
	}
	csv.close();
}

int main(){
	int size = 1000;
	double filter[size];
	genSinc(filter, size,1);

	int noisesize = 10000;
	int noise[noisesize];
	noiseGen(noise, noisesize);
//	convolver(noise, noisesize, filter, size);

//Just to double check
//	print(noise, noisesize);
	csvOut(noise,noisesize);
}


*/

//Converted from The Scientist and Engineer's Guide to Digital Signal Processing
//pg 294


int main(int argc, char ** argv){

	int input[2000];
	int length = sizeof(input)/sizeof(input[0]);
	//put random noise into the array
	int switcher = -1;
	for(int i = 0; i < length; i++){
		srand(time(NULL)+i);
		input[i] = rand()*switcher;
		switcher *= -1;
	}

	int * output = new int[length];

	double pi = 3.14159265358979323846264338327950288419716939;
	double cutoff = .1;			//Keep between 0 and .5
	int filterSize = 1001;			//odd points?
	double * sincFilter = new double[filterSize];

	//calculate lowpass filter
	//calculates 1/2, sets first half equal to second half
	sincFilter[filterSize / 2] = 2*pi * cutoff;
	for (int i = 1; i < filterSize/2; i++){
		double buffer = sin(2*pi*cutoff * i) / i;
		sincFilter[filterSize/2 +i] = buffer;
		sincFilter[filterSize/2 -i] = buffer;		
	}

	for (int i = 0; i < filterSize; i++){
		sincFilter[i] *= 0.54 - 0.46 * cos(2 * pi * i/filterSize);
	}

	//Normalize the lowpass filter for unity gain (at DC, apparently)
	double sum;
	for (int i = 0; i <filterSize + 1; i++){
		sum += sincFilter[i];
	}

	for(int i = 0; i < filterSize +1; i++){
		sincFilter[i] /= sum;
	}

//	ofstream file;
//	file.open("noise.csv",fstream::in | fstream::trunc);
//	//Make a csv out of it
//	for (int i = 0; i <filterSize; i++){
//		file << sincFilter[i] << endl;
//		file.flush();
//	}
//	file.close();


	//Convolve the input signal in three parts, on the end pretending like
	//the edges are zero (don't exist)

	//front edge
	for(int i = 0; i < filterSize; i++){
		double buffer = 0;
		for(int j = 0; j < filterSize; j++){
			if(i-j >= 0) {
				buffer += input[i-j] * sincFilter[j];
			}
		}
		output[i] = buffer;
	}

	//main convolution
	for(int i = filterSize; i < length; i++){
		double buffer = 0;
		for(int j = 0; j < filterSize; j++){
			buffer += input[i-j] * sincFilter[j];
		}
		output[i-filterSize/2] = buffer;
	}

	ofstream file;
	file.open("noise.csv",fstream::in | fstream::trunc);
	//Make a csv out of it
	for (int i = 0; i <length; i++){
		file << output[i] << endl;
		file.flush();
	}
	file.close();

//	delete[] sincFilter;
//	delete[] output;
}
