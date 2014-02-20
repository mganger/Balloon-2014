// This is the code for the slave (balloon).
//
//
//


#include <dataPoint.h>

struct dataStruct()
{
  unsigned int bid;
  unsigned int temp;
  unsigned int pressure;
  unsigned int co2;
  unsigned int n2;
  unsigned int picture[];
  unsigned int time;  
}

void setup()
{
	//declare sensor pins here
}

void loop()
{
  getData();
  getPic();
  writeData();
  borp();
  counter();
}
