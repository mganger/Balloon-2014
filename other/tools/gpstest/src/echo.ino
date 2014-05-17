// Test code for Adafruit GPS modules using MTK3329/MTK3339 driver
// This code just echos whatever is coming from the GPS unit to the
// serial monitor, handy for debugging!
// Modified from the Adafruit GPS github example by Michael
// Interrupt is called once a millisecond, looks for any new GPS data, and
// stores it in an array, to be sent at the next transmission.

#include "TimerOne.h"
#include <SoftwareSerial.h>
// GPS Power  -> 5V
// GPS Ground -> GND
// GPS TX     -> D3
// GPS RX     -> D2

//We need a global variable to act as a array counter (only in this instance).
//In the Data class, this can be kept as a private variable. We also need a
//global array to handle the gps transmittance
int counter = 0;
char gpsBuffer[256];
SoftwareSerial GPS(3, 2);

void gpsBufferRead(){
	//reads characters from the gps and writes directly to serial register
	if(GPS.available()){
		gpsBuffer[counter] = GPS.read();
		counter++;
	}
}

void setup()
{    
	Serial.begin(115200);
	Serial.println("GPS Test Begin");
	GPS.begin(9600);
	delay(1000);
	
	//setup the timer to call the interrupt every 1ms
	Serial.begin(115200);
	Timer1.initialize(1000);
	Timer1.attachInterrupt(gpsBufferRead);

	while(1){
		delay(100);
	}
}

void loop(){}
