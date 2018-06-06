#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
int tempSensor = A0;
int humidSensor = A1;
int pHSensor = A2;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  //Set pinMode for humidity sensor
  pinMode(2,INPUT);
  pinMode(humidSensor,INPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  // Calculate temperature using LM35 on A0 port
  int reading = analogRead(tempSensor);  
  float voltage = reading * 5.0 / 1024.0; 
  int temperature = voltage * 100.0;

  
  // Calculate humidity using sensor on A1 port
  int humidity = (analogRead(humidSensor)*100)/1023 ; //(Convert from 0-1023 to 0-100)
  //------ Needed convert to percentage scale--- Form a formula.

  //Send data
  mySerial.write(temperature);
  mySerial.write(humidity);
  
  



  

}
