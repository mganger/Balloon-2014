//Program designed to test the adafruit gps
//It tries to parse the useful data


//position of the variables within the transmission (comma delimited)
//put here for convenience
#define	LONGPOS	5
#define	LATPOS	8
#define	ALTPOS	10

//designed to parse the comma delimited gps signal into useful measurements
void parse(char * input, char * latitude, char * longitude, char * altitude){

	//walk through the char array and parse between data points
	//there is no conversion of ascii to ints; it is put right into the arrays 
	for(int i = 0;; i++){

	}

}

void setup(){

	//create the objects we need
	SoftwareSerial softTTL(2, 3);
	String gpsString;

	//setup communications
	softTTL.begin(9600);
	Serial.begin(115200);


	//Wait for the gps to come online
	softTTL.listen();
	while(!softTTL.isListening()){}
	Serial.println("GPS is online");

	while(1){
		//do nothing if the gps hasn't sent anything
		while(!softTTL.available()){}
	
	
		//When things are available, read into a string
		for(int i = 0;softTTL.available();i++){
			gpsString += (char)softTTL.read();
		}
		parse(gpsString);

	}
}

void loop(){
	Serial.println("Error: Entered loop");
}
