#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

int main()
{

	ofstream longData;
	longData.open("../data.csv");

	//Opens a stream to index file, stores index to string 'number'
	ifstream index;
	index.open("lastfile");
	string number;
	getline(index,number);
	cout << number << " points available" << endl;
	int num = atoi (number.c_str());
	index.close();

	for(int h = 0; h <= num;h++)
	{
		//Creates a file name based on the index string
		string filename = "datapoint_";
		stringstream h_string;
		h_string << h;
		int length = h_string.str().length();

		for(int i = 0;i < (15 - length);i++)
		{
			filename +='0';
		}

		filename += h_string.str();
		//Reads in from the file 
		ifstream point(filename.c_str());
		string data;
		getline(point,data);
		if(data != ""){
			longData << data << '\n';
		}
		point.close();
	}
		longData.close();
}
