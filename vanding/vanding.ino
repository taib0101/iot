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
const int motorPin5 = D4;
const int motorPin6 = D5;
const int motorPin7 = D6;
const int motorPin8 = D7;

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
  stepper.setSpeed(65);
  stepper2.setSpeed(50);
  Firebase.begin(FIREBASE_HOST);
}

String tmp1 = "",tmp2 = "";
bool tmp3 = "";
int stepCount = 0;

void customer(String value1,String value2,bool value3)
{
  for(int i = 1; i <= 2; ++i)
  {
    delay(1000);
    for(int j = 1; j <= 5; ++j)
    {
      stepper.step(stepsPerRevolution);
      delay(1000);
      stepper2.step(stepsPerRevolution);
      delay(1000);
    }
    Serial.println("output");
    delay(1000);
  }
  Serial.println("Money = " + value1 + " ,Option = " + value2 + " ,Status = " + value3);
}

void loop() {
  String value1 = Firebase.getString("/Payment/Money");
  String value2 = Firebase.getString("/Payment/Option");
  bool value3 = Firebase.getString("/Payment/Payment Status");
  
  if(value1 == tmp1)
  {
    if(value2 == tmp2)
    {
      if(value3 == tmp3)
      {
        Serial.println("Please Take something");
      }
      else
      {
        customer(value1,value2,value3);
      }
    }
    else
    {
      customer(value1,value2,value3);
    }
  }
  else
  {
    customer(value1,value2,value3);
  }  
  delay(1000);
  // tmp1 = Firebase.getString("/Payment/Money");
  // tmp2 = Firebase.getString("/Payment/Option");
  // tmp3 = Firebase.getString("/Payment/Payment Status");  
}