#include <FirebaseArduino.h>//
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ArduinoJson.h>//
#include <ArduinoJson.hpp>
//#include <BearSSLHelpers.h>
//#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>//
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
//#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
//#include <WiFiClientSecureAxTLS.h>
//#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>//
#include <WiFiServerSecure.h>
//#include <WiFiServerSecureAxTLS.h>
//#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#include <Stepper.h>//
#define FIREBASE_HOST "test-8c359-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "waqtMbJlSVYaaOJkTpTiWoElsIwFKOSWRiJb7OyQ"
#define WIFI "k20"
#define PASS "00000000"
const int stepsPerRevolution = 600;
const int motorPin1 = D0;
const int motorPin2 = D1;
const int motorPin3 = D2;
const int motorPin4 = D3;
const int motorPin5 = D5;
const int motorPin6 = D6;
const int motorPin7 = D7;
const int motorPin8 = D8;

Stepper stepper(stepsPerRevolution, motorPin1, motorPin3, motorPin2, motorPin4);
Stepper stepper2(stepsPerRevolution, motorPin5, motorPin6, motorPin7, motorPin8);
void setup() {
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
  stepper.setSpeed(70);
  delay(500);
  stepper2.setSpeed(70);
  delay(500);
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

int stepCount = 0;

void customer(String value1,String value2)
{
  Serial.println("Processing for " + value2 + " ......");
  if(value2 == "Kitkat")
  {
    for(int i = 1; i <= 2; ++i)
    {
      for(int j = 1; j <= 5; ++j)
      {
        stepper.step(stepsPerRevolution);
        delay(1000);
        Serial.print("..");
      }
    }
    Serial.println("");
  }
  else if(value2 == "Cake")
  {
    for(int i = 1; i <= 2; ++i)
    {
      for(int j = 1; j <= 5; ++j)
      {
        stepper2.step(-stepsPerRevolution);
        delay(1000);
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
  delay(1000);
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