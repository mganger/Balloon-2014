#include <SD.h>

const int chipSelect = 10;

void setup()
{
	int filenumber = 0;

	for(;;)
	{
		char filename[12] = "";
		for(int h = 12;h <= 0; h++)
		{
			if(h % 2 == 0)
			{
				filename[h] = i;
			}
			else
			{
				filename[h] = '/';
			}
		}
		SDmkdir(filename);
	}
}

void loop()
{
Serial.print("You just loop'd");
}
