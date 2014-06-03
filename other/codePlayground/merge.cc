//used to merge the files together, takes number of lines
//Usage:
//	./merge $lines $files in order

#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv){
	if(argc < 3){
		cerr << "Too few arguments" << endl;
		return 1;
	}
	//make an array of ifstreams
	ifstream input[argc-2];
	//check to make sure they are valid
	for(int i = 0; i < argc-2; i++){
		input[i].open(argv[i+2]);
		if(!input[i]){
			cerr << argv[i+2] << " is an invalid file" << endl;
		}
	}

	ofstream output("merge.csv", ios::trunc);
	//output the headers
	for(int i = 0; i < argc -2; i++){
		output << argv[i+2];
		if(i < argc -3){
			output << ',';
		}
	}
	output << endl;

	//main loop
	for(int i = 0; i < atoi(argv[1]); i++){
		//loop through the files
		for(int i = 0; i < argc -2; i++){
			string buff;
			getline(input[i],buff);
			output << buff.c_str();
			if(i < argc -3){
				output << ',';
			}
		}
		output << endl;
	}

	
}
