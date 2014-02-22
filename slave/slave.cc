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
//	int picture[300];	//this is to store the picture as a series of 16 bit ints
	int picName;		//Picture file name
//	int picIndex;		//index to recompile the picture in order
	int dataTime;  		
} dataStruct;

void setup()
{
	//declare sensor pins here
}

void loop()
{
//	getData();
//	getPic();
//	writeData();
//	borp();
//	counter();
}
