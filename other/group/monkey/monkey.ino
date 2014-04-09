//April Kaye Petersen
int irr = A0;
//infrared radiation sensor
int hum = A1;
//humidity sensor
int pre = A2;
//pressure sensor
int the = A3;
//temperature sensor
int gps = A4;
//um...gps
int co2 = A5;
//CO2 sensor
int pinArray[] = {irr, hum, pre, the, gps, co2};
int pinNumber = 6;
int dataArray[6];
int led = 13;

void setup()
{
  Serial.begin(9600);
  initPins(pinArray, pinNumber);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(led, OUTPUT);
  
  Serial.println("Temp,Pres,Alt,GPS,Toast,Fish;");
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

}

//starts all of the pins at once and declares them as inputs
void initPins(int * pin, int number)
{
  for (int i = 0; i < pinNumber; i++)
  {
    pinMode(pinArray[i], INPUT);
  }
}

//April Kaye Petersen

