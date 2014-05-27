void setup()
{
Serial.begin(9600);
	
	for(;;){
		Serial.println("$GPGGA,071554.000,4225.6561,N,07809.3925,W,1,4,2.38,383.2,M,-34.0,M,,*6F");
		Serial.println("$GPVTG,263.63,T,,M,3.56,N,6.59,K,A");
		Serial.println("$GPGGA,071556.000,4225.6558,N,07809.3919,W,1,4,2.38,383.8,M,-34.0,M,,*62");
		Serial.println("GPGSA,A,3,26,24,15,21,18,05,,,,,,,1.60,1.31,0.92");
		Serial.println("GPVTG,264.53,T,,M,5.05,N,9.36,K,A");
		Serial.println("$GPGGA,071536.000,4225.6563,N,07809.3910,W,1,4,2.38,391.8,M,-34.0,M,,*66");
		delay(1000);
		}
}

void loop(){}
