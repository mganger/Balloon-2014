//Library to actually write the data from the borp function to the digital pin
//Accepts a structure and writes the data to the pin
//See this: http://www.instructables.com/id/Arduino-is-Slow-and-how-to-fix-it/?ALLSTEPS
//According to the author, we can modify the port register directly using something 
//like this:
//High:
//PORT{letter} |= _BV(P{letter}{number});
//
//Low:
//PORT{letter} &= ~_BV(P{letter}{number});
//
//We will have to look up the specific pins for the Due

//#include "Arduino.h" 		//Includes all the standard Arduino Libraries
#include "writeData.h"		//Include the headers for this library

writeData::writeData(struct data, int actualPin)
{
	
}
