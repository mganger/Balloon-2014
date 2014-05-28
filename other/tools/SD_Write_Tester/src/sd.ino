//Program to test only the sd card. writes to one file

#define CSELECT 10
#define PERIOD 100

#include <SD.h>
#include <SPI.h>
File file;

void setup(){
	Serial.begin(9600);
	pinMode(CSELECT,OUTPUT);
	SD.begin(CSELECT);
	for(;;){
		file = SD.open("SDTEST.CSV",FILE_WRITE);
		Serial.println(file.println(millis()));
		file.close();
	}
}

void loop(){}
