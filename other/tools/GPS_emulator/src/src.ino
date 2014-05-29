void setup()
{
Serial.begin(9600);
	
	for(;;){
		Serial.println("$GPGGA,032955.000,4225.6575,N,07809.3982,W,2,8,1.06,381.2,M,-34.0,M,0000,0000*6E");
		Serial.println("$GPGSA,A,3,13,10,04,17,12,02,05,25,,,,,1.89,1.06,1.56*05");
		Serial.println("$GPRMC,032955.000,A,4225.6575,N,07809.3982,W,0.00,242.71,290514,,,D*7E");
		Serial.println("$GPVTG,242.71,T,,M,0.00,N,0.00,K,D*3A");
		delay(1000);
		}
}

void loop(){}
