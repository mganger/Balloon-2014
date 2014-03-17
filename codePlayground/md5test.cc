//Designed to test the functions of the md5 library

#include <stdio.h>
#include "../master/hash-library/md5.h"	
#include <string.h>
#include <iostream>

using namespace std;


int main()
{
	MD5 md5;
	cout << md5("Hello World") << endl;

	
	return 0;
}
