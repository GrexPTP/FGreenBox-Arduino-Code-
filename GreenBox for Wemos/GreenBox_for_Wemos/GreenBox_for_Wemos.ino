
//chú ý check lại pH và nhiệt độ

//5 6 7 cho module thời gian thực
//8 cho LED
//9 cho đèn sợi tóc
//10 cho máy bơm nước + phun sương
//11 cho quạt
//12 cho dd thủy canh
//13 cho nước

//A0 CB nhiệt độ
//A1 Cb độ ẩm
//A2 Cb pH
#include <Wire.h>
#include <DS1302.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>



#define FIREBASE_HOST "f-green-box.firebaseio.com" // Firebase Address
#define FIREBASE_AUTH ""   //Authorication
//Set up wifi name and passwords --> Remember to edit.
#define ssid  "3e"
#define password  "56482101"

// Variable to check wifi is connected and possibility to transfer data
int tempt;


//khai báo
// Fields receive data from base.
bool isWarmClicked, isWaterClicked, isCoolDownClicked, isLedChecked;


int led = D8;// ro le
int light = D9; // Done
int drop = D10;
int fan = D11;
int hydroponics = D12;
int waterFlow = D13;



//thời gian thực
// Fix by yourself


/*DS1302 rtc(5, 6, 7);
Time t;*/
int temper;
int humidity;
int pH;


void setup(){
  //Set up wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  //connect firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.begin(9600);

  
 /* //thời gian thực
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(6, 8, 2010); */  // Set the date to August 6th, 2010

  //setup chân digital
  pinMode(led,OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(drop,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(hydroponics,OUTPUT);
  pinMode(waterFlow,OUTPUT);
}

void loop() {
  // Test Wifi is working
  tempt += 1;
  // Go to firebase and check. Could be deleted afterwards 
  Firebase.setInt("temp",tempt);
  
  // Get all analog sensor from arduino
  if (Serial.available()) {
    
     temper = Serial.read();
     humidity = Serial.read(); 
     //pH = Serial.read();
     // Update to server.    
     Firebase.setString("Temperature",String(temper)); 
     Firebase.setString("Humidity",String(humidity));
     Firebase.setString("pH",String(pH));
   }
   // get user's interaction  
  isWaterClicked = Firebase.getBool("Water");
  isCoolDownClicked = Firebase.getBool("Cool Down");
  isLedChecked = Firebase.getBool("Led");
  isWarmClicked = Firebase.getBool("Warm");


  // Control light  
  if (temper <= 25 || isWarmClicked){
      digitalWrite(light, HIGH);
      delay(3000);  
     } else {
       digitalWrite(light,LOW);     
      delay(3000);
     }
     
  // Control fans and water bumps for cooling 
  if (temper >= 35 || isCoolDownClicked){
    digitalWrite(fan,HIGH);
    digitalWrite(drop,HIGH);
  }else{
    digitalWrite(fan,LOW);
    digitalWrite(drop,LOW);
  }
  
  // Control water bumps for humidity.
  if (humidity > 750 || isWaterClicked){ // Needed scaling to range 0 - 100% to compute and display properly
    digitalWrite(drop,HIGH);
  }else{
    digitalWrite(drop,LOW);
  }

 
  // Control water flows and hydroponics moisture.
  // More chemicals
 if (pH > 100 && pH < 424){//Needed scaling to the scale of 8 to compute and display properly
  digitalWrite(hydroponics,HIGH);
  delay(1500)
  digitalWrite(hydroponics,LOW);
 }
 // More water
 if (pH > 475 && pH < 924) {
  digitalWrite(waterFlow,HIGH);
  delay(2000);
  digitalWrite(waterFlow,LOW);
  }
  




  
  /*
  //lấy thông số
  nhietdo = analogRead(A0);
  //get temperature
  String temperature = String(nhietdo);
  Firebase.setString("Temperature",temperature);
  
  doam = analogRead(A1);
  get humidity
  String humidity = String(doam);
  Firebase.setString("Humidity",humidity);
  pH = analogRead(A2);
  //get PH
  String ph = String(pH);
  Firebase.setString("pH",ph);
  t = rtc.getTime();

  if (t.min>5 && t.min<15) digitalWrite(quat,HIGH);
  else digitalWrite(quat,LOW);
  
  if ((t.hour>=5 && t.hour<=17) || isWarmClicked) {
    if (nhietdo<150 || isWarmClicked){
      
      digitalWrite(light,HIGH);
      if (nhietdo >= 150) Firebase.setBool("Warm",false);
    }
    else {digitalWrite(light,LOW);
     
    }
    digitalWrite(led,HIGH);
  }
  else digitalWrite(led,LOW);
  
  if (nhietdo>200 || isCoolDownClicked) {
    
    digitalWrite(suong,HIGH);
    digitalWrite(quat,HIGH);
    if (nhietdo <= 200) Firebase.setBool("Cool Down",false);
  }
  else {
    
    digitalWrite(suong,LOW);
    digitalWrite(quat,LOW);
  }

  if (doam > 750 || isWaterClicked) {
    
    digitalWrite(suong,HIGH);
    if (doam <=750) Firebase.setBool("Water",false);
  }
  else digitalWrite(suong,LOW);
 

  if (pH>100 && pH<424) {
    digitalWrite(ddtc,HIGH);
    delay(1500);
    digitalWrite(ddtc,LOW);
  }
  if (pH>475 && pH<924) {
    digitalWrite(nuoc,HIGH);
    delay(2000);
    digitalWrite(nuoc,LOW);
  }
  

 // Use this code to control led by phone
  isLedChecked = Firebase.getBool("Led");
  if (isLedChecked) digitalWrite(led,HIGH);
  else digitalWrite(led,LOW);
  
  
  delay(300000);
  */
  
  


     
    
  
  
}

