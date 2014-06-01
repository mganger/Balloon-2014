//Much like master, except works on a real file, not a device

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

int calcSum(string data){
	char b = 0;
	for(unsigned int i = 0;i < data.length();i++)
	{
		b = b ^ data.at(i);
	}
	return b;
}

int main(int argc, char** argv){

	//Argument testing
	if(argc != 2){
		cout << "Wrong number of arguments" << endl;
		return 0;
	}

	string file_lines;
	long int linecount = 0;
	fstream inputfile;
	inputfile.open(argv[1]);
	while(getline(inputfile,file_lines)){
		linecount++;
	}
	//Error handling
	if(!inputfile.is_open()){
		cerr << "Can't open " << argv[1] << endl;
	}
	inputfile.close();

	inputfile.open(argv[1]);

	cout << linecount << " lines in " << argv[1] << endl;

	string outputname;
	string badoutput;
	stringstream filename;
	filename << argv[1];
	getline(filename,outputname,'.');
	badoutput = outputname;
	outputname += "_clean.csv";
	badoutput += "_dirty.txt";
	
	ofstream output(outputname.c_str(),ios::trunc);
	ofstream bad(badoutput.c_str(),ios::trunc);

	int outlinecount = 0;
	int badlinecount = 0;
	

	for(int i = 0; i < linecount; i++){
		stringstream linestream;
		string tmp;
		getline(inputfile,tmp);
		linestream << tmp;
		string garbage;
		string data;
		string check = "00";
		getline(linestream,garbage,'$');
		getline(linestream,data,'*');
		check[0] = linestream.get();
		check[1] = linestream.get();
		int checksum = calcSum(data);
		int humansum = ((int)check.at(0) - 48) * 16 + (int)check.at(1) - 48;
		if(checksum == humansum)
		{
			output << data << endl;
			outlinecount++;
//			cout << tmp << endl;
		}else{
			bad << data << endl;
			badlinecount++;
		}
//		cout << calcSum(data) << ',';
//		cout << ((int)check.at(0) - 48) * 16 + (int)check.at(1) - 48 << endl;
	}
	inputfile.close();
	output.close();
	bad.close();

	cout << linecount - badlinecount << " goodlines" << endl;
	cout << badlinecount << " corrupted lines" << endl;

	//work with only the good data
	for(int i = 0;i < outlinecount; i++){
		
	}
}
