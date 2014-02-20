/*
Borp.h - Library for sending data from an Arduino over a serial connection, specifically designed for the Arudino Due and MM2 radio chips.
Balloon Over Radio Protocol (B.O.R.P)
Created by Hougthon College Science Honors program 2014
*/

#ifndef Borp_h		//Apparently this keeps prevents problems if the same library is include(d) twice
#define Borp_h

#include "Arduino.h"

class Borp
{
	public:
		Borp(int pin);				//The constructor initializes the borp, it has to have the same name as the class
		void phoneHome(struct data);		//This will be the function that actually pipes data to the radio
	private:
		struct data;				//Private variable data structure to store points
};

#endif
