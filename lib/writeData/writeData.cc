//Library to actually write the data from the borp function to the digital pin		MG
//Library to write data to the local memory (ie SD Card), not the radio			AR

//Accepts a structure and writes the data to the pin
//See this: http://www.instructables.com/id/Arduino-is-Slow-and-how-to-fix-it/?ALLSTEPS
//According to the author, we can modify the port register directly using something 
//like this:
//*** This is unecessary because we can use the Serial Write function.***//

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
