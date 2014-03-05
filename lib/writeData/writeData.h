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

//QUESTION: Should we put getData and writeData into one library? Might make things less confusing.
//Syntax would look like:  Data::writeData


#ifndef writeData_h		//Checks to see if this library has been included 
#define writeData_h		//This ensures that it is not included twice

//#include "Arduino.h"		//includes standard arduino libraries (do we need to?)

class writeData
{
	public:
		struct data;
		writeData(struct data, int actualPin);		//write data to pin registry

	private:
		//not sure what to put here
};

#endif			//Ends check for included libraries
