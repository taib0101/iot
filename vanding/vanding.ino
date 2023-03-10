#include <FirebaseArduino.h>//
#include <ArduinoJson.h>//
#include <ArduinoJson.hpp>
#include <ESP8266WiFi.h>//
#include <Stepper.h>//
#define FIREBASE_HOST "test-8c359-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "waqtMbJlSVYaaOJkTpTiWoElsIwFKOSWRiJb7OyQ"
#define WIFI "Heisenberg"
#define PASS "scanf(&n)"
const int steps = 500;
const int pin1 = D0;
const int pin2 = D1;
const int pin3 = D2;
const int pin4 = D3;
const int pin5 = D5;
const int pin6 = D6;
const int pin7 = D7;
const int pin8 = D8;
#define IR_PIN D0
#define IR_PIN2 D7

Stepper stepper(steps,pin1,pin3,pin2,pin4);
Stepper stepper2(steps,pin5,pin7,pin6,pin8);
void setup() {
  pinMode(IR_PIN,INPUT);
  pinMode(IR_PIN2,INPUT);
  Serial.begin(9600);
  WiFi.enableInsecureWEP();
  WiFi.begin(WIFI,PASS);
  Serial.println("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("tring to load");
    delay(500);
  }
  Serial.println();
  Serial.println("connected: ");
  delay(500);
  Serial.println(WiFi.localIP());
  stepper.setSpeed(50);
  delay(500);
  stepper2.setSpeed(70);
  delay(500);
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

void customer(String value1,String value2)
{
  bool bb = 1;
  Serial.println("Processing for " + value2 + " ......");
  if(value2 == "Kitkat")
  {
    for(int i = 1; i <= 3 && bb; ++i)
    {
      for(int j = 1; j <= 5 && bb; ++j)
      {
        stepper.step(-steps);
        delay(1000);
        bool sense = digitalRead(IR_PIN);
        Serial.println(sense);
        if(sense == 0)
          bb = 0;
        Serial.print("..");
      }
    }
    Serial.println("");
  }
  else if(value2 == "Cake")
  {
    for(int i = 1; i <= 3 && bb; ++i)
    {
      for(int j = 1; j <= 5 && bb; ++j)
      {
        stepper2.step(steps);
        delay(1000);
        bool sense = digitalRead(IR_PIN2);
        Serial.println( sense);
        if(sense == 0)
          bb = 0;        
        Serial.print("..");
      }
    }
    Serial.println("");
  }
  Serial.println("Thank you purchased " + value2 + " successfully");
  return;  
}

String tmp1 = Firebase.getString("/Payment/Money");
String tmp2 = Firebase.getString("/Payment/Option");
String tmp4 = "-1" ;

void loop() {
  tmp1 = Firebase.getString("/Payment/Money");
  tmp2 = Firebase.getString("/Payment/Option");
  String tmp3 = Firebase.getString("/Payment/Step");
  Serial.println("Do you wanna take something?");
  delay(9000);
  String value1 = Firebase.getString("/Payment/Money");
  String value2 = Firebase.getString("/Payment/Option");
  String value3 = Firebase.getString("/Payment/Step");
  Serial.println("option = " + value2);
  Serial.println("step = " + value3);

  bool bb = 0;
  if((value3 != tmp3) || (tmp4 != "-1"))
    bb = 1;
  if(bb)
  {
    customer(value1,value2);
  }
  else
  {
    Serial.println("Please Take something");
  }
}