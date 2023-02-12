#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#define FIREBASE_HOST "test-8c359-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "waqtMbJlSVYaaOJkTpTiWoElsIwFKOSWRiJb7OyQ"
#define WIFI "isoDevs"
#define PASS "bubt2a1302"

void setup() {
  // put your setup code here, to run once:
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

  Firebase.begin(FIREBASE_HOST);
}
String tmp1 = "",tmp2 = "";
bool tmp3 = 0;

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
        Serial.println("Money = " + value1 + " ,Option = " + value2 + " ,Status = " + value3);
      }
        
    }
    else
    {
      Serial.println("Money = " + value1 + " ,Option = " + value2 + " ,Status = " + value3);
    }
      
  }
  else
  {
    Serial.println("Money = " + value1 + " ,Option = " + value2 + " ,Status = " + value3);
  }
     
  delay(1000);
  // tmp1 = Firebase.getString("/Payment/Money");
  // tmp2 = Firebase.getString("/Payment/Option");
  // tmp3 = Firebase.getString("/Payment/Payment Status");  
}
