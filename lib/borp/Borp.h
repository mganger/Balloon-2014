/*
Borp.h - Library for sending data from an Arduino over a serial connection, specifically designed for the Arudino Due and MM2 radio chips.
Balloon Over Radio Protocol (B.O.R.P)
Created by Hougthon College Science Honors program 2014
*/

#ifndef Borp_h		//Checks to see if Borp_h is defined (ie if the Borp Libraries have been included yet).
#define Borp_h		//Defines Borp_h if it has not yet been defined

#include "Arduino.h"	//includes standard arduino libraries

class Borp
{
	public:
		Borp(int pin);				//The constructor initializes the borp, it has to have the same name as the class
		void phoneHome(struct data);		//This will be the function that actually pipes data to the radio
		void testTransmission(int num);		//This can be used to test the radios until we build our struct data;
	private:
		int pin;				//Stores what pin the serial radio is connected to
};

#endif			//Ends check for included libraries

