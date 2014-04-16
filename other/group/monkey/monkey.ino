/* Arduino code for the Science Honors program at Houghton College
 * Team Flying Monkeys
 */

int co2  = A0;
int temp = A1;
int humm = A2;
int pinArray[] = {irr, hum, pre, the, gps, co2};
int pinNumber = 6;
int dataArray[6];
int led = 13;
int SDCount = 0;

//Code for SD read
#include <SD.h>
#include <SPI.h>
File dataFile;

void setup()
{
  Serial.begin(9600);
  initPins(pinArray, pinNumber);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

//Code for SD read
	Serial.print("Initializing SD card...");
	pinMode(chipselect,OUTPUT);
	if(!SD.begin(chipSelect))
	{
		Serial.println("Dude, your card reader sucks, or it's not plugged in...");
		while(1);
	}
	Serial.println("Card initialized.");

	char filename[] = "LOGGER000000.txt";
	for (uint8_t i = 0; i <10000;i++)
	{
		filename[6]=i/100000 + '0';
		filename[7]=i/10000  + '0';
		filename[8]=i/1000   + '0';
		filename[9]=i/100    + '0';
		filename[10]=i/10    + '0';
		filename[11]=i%10    + '0';
		if(!SD.exists(filename))
		{
			dataFile = SD.open(filename, FILE_WRITE);
			break;
		}
	}
	if(!dataFile)
	{
		Serial.println("couldn't create file");
	}
	Serial.print("Loggeing to: ");
	Serial.println(filename);
}


void loop()
{
  //writes the data from each pin into a spot on the data package
  dataArray[0] = analogRead(pinArray[0]);
  dataArray[1] = analogRead(pinArray[1]);
  dataArray[2] = analogRead(pinArray[2]);
  dataArray[3] = analogRead(pinArray[3]);
  dataArray[4] = analogRead(pinArray[4]);
  dataArray[5] = analogRead(pinArray[5]);


  //during every loop the arduino will take the dataArray of every
  digitalWrite(led, HIGH); //whenever there is something to print, the led will turn on
  for (int v = 0; v < 6; v++)
  {
    Serial.print(dataArray[v]);
    Serial.print(",");
  }

  Serial.println(";");
  delay(100);
  digitalWrite(led, LOW); //after printing the data, the led will turn off

  delay(1000);  //delays the led from turning on again for one second


	String dataString = "";
	dataFile.println(dataString);

	SDCount++;
	if (SDCount>50)
	{
		dataFile.flush();
		SDCount = 0;
	}
}

//starts all of the pins at once and declares them as inputs
void initPins(int * pin, int number)
{
  for (int i = 0; i < pinNumber; i++)
  {
    pinMode(pinArray[i], INPUT);
  }
}
