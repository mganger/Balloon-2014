//Designed to test the functions of the md5 library

#include <stdio.h>
#include "../master/hash-library/md5.h"	
#include "../master/hash-library/md5.cpp"
#include <string.h>
#include <iostream>

using namespace std;

int main()
{
	string test;
	MD5 md5;
	cout << "Enter a string to calculate the md5\n";
	cin >> test;
	cout << "The md5 of " << test << " is: \n";
	cout << md5(test) << endl;

	
	return 0;
}
