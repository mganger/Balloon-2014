/*
 Requires the SD library from the Adafruit website 
 * SD card attached MOSI - pin 11, MISO - pin 12, CLK - pin 13, CS - pin 10
*/
 
#include <SD.h>
 
const int chipSelect = 10;
 
File dataFile;
 
void setup()
{
	Serial.begin(115200);
	Serial.print("Initializing SD card...");

	// Open serial communications and wait for port to open:
	pinMode(10, OUTPUT);
	

	Serial.println("card initialized.");
	
	// see if the card is present and can be initialized:
	if (!SD.begin(chipSelect)) 
	{
		Serial.println("Card failed, or not present");
		// don't do anything more:
		while (1) ;
	}

	for(long int filenumber = 0 ;filenumber <= 9999999;filenumber++)
	{
		// create a new file
		char filename[18] = "";
		tahu(filenumber,filename);
		filename[13] = '.';
		filename[14] = 'C';
		filename[15] = 'S';
		filename[16] = 'V';
		if(filenumber%10 == 0){
			char directory[13];
			for(int i = 0; i < 12; i++){
				directory[i] = filename[i];
			}
			directory[12] = '\0';
			SD.mkdir(directory);
			Serial.print("Making directory ");
			Serial.println(filenumber);
		}


		// only open a new file if it doesn't exist
		if (!SD.exists(filename))
		{	
			dataFile = SD.open(filename, FILE_WRITE);
		}
		if (!dataFile)
		{
			Serial.print("Couldn't create file: ");
			Serial.println(filename);
			filenumber++;
			continue;
		}
		Serial.print("Logging to: ");
		Serial.println(filename);
		
		// make a string for assembling the data to log:
		String dataString = "";
	
		// read three sensors and append to the string:
		for(int i = 0; i < 10; i++){
			for (int analogPin = 0; analogPin < 3; analogPin++)
			{
				int sensor = analogRead(analogPin);
				dataString += String(sensor);
					if (analogPin < 2)
					{
						dataString += ",";
					}
			}
		}
		dataFile.println(dataString);
		dataFile.close();
	}
}

char * tahu(int i,char * a)
{
	for(int h = 12; h >= 0; h--)
	{
		if(h % 2 == 0)
		{
			a[h] = (i % 10) + 48;
			i = i/10;
		}
		else
		{
			a[h] = '/';
		}
	}
	return a;
}

void loop()
{
}
