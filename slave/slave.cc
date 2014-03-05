// This is the code for the slave (balloon).
//
//
//


//#include <dataPoint.h>
//#include <arduino.h>
#include <stdio.h>
//#include <MD5.h>

struct trans
{
	int transferIndex;
	int transferTime;
	short unsigned int errorCode;		//0 - 255, Might include corrupted transmission, no data to send, low battery, etc. 0 = ok
	
} dataTran, picturesTran;


struct data			//this gets written to the SD
{
	int bid;
	int priority;
	unsigned long int dataIndex;		//this is how the data is indexed. 32 bits, so keep below 4 billion points
	int temp;		
	int pressure;
	int co2;
	int n2;
	bool picNew;		//0 means that the picture has not been updated, 1 that it has (
	int picture[300];	//this is to store the picture as a series of 16 bit ints
	int picName;		//Picture file name
	int picIndex;		//index to recompile the picture in order
	int dataTime;  		
} dataStruct;

void setup()
{
	//declare sensor pins here
}

void loop()
{
//	resetData() 		//This should somehow set all values to 1024. Note that we cannot really have a definite reset of the picture values, so we will need a specific bit (i.e. picNew) to handle that 
//	getData();		//These two should be in an if then statement based on the master request
//	getPic();
//	writeData();
//	borp();
//	counter();
}
