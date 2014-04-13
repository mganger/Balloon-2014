#include <Wire.h>
#include "IntersemaBaro.h"

Intersema::BaroPressure_MS5607B baro(true);

void setup() { 
    Serial.begin(9600);
    baro.init();
}

void loop() {
	Serial.print("#,press,alt");
	for(int n = 0;;n++)
	{
		long press = baro.getPressure();
		long alt = baro.getHeightCentiMeters();
		Serial.print(n);
		Serial.print(",");
		Serial.print((float)(press));
		Serial.print(",");
		Serial.println((float)(alt));
		delay(1000);
	}
}
