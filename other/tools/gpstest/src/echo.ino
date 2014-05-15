// Test code for Adafruit GPS modules using MTK3329/MTK3339 driver
// This code just echos whatever is coming from the GPS unit to the
// serial monitor, handy for debugging!
// Modified from the Adafruit GPS github example by Michael

#include "Adafruit_GPS.h"
 #include <SoftwareSerial.h>
// Connect the GPS Power pin to 5V
// Connect the GPS Ground pin to ground
// If using software serial (sketch example default):
//   Connect the GPS TX (transmit) pin to Digital 3
//   Connect the GPS RX (receive) pin to Digital 2
// If using hardware serial (e.g. Arduino Mega):
//   Connect the GPS TX (transmit) pin to Arduino RX1, RX2 or RX3
//   Connect the GPS RX (receive) pin to matching TX1, TX2 or TX3

#define GPSECHO  true

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}


void setup()  
{    
	Serial.begin(115200);
	Serial.println("GPS Test Begin");
	GPS.begin(9600);
	
	// uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
	GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	//GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
	//GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);
	
	//GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
	//RMC or RMCGGA only
	GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);
	//RMC only
	//GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);

	// Request updates on antenna status
	GPS.sendCommand(PGCMD_ANTENNA);

	useInterrupt(true);
	
	delay(1000);
}

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  if (GPSECHO)
    if (c) UDR0 = c;  
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
}

void loop(){}
