//This code runs a lowpass filter on the data

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>


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
