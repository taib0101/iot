//

//////////////////////////////////////

//#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <FirebaseArduino.h>
#define BLYNK_TEMPLATE_ID "TMPL6pWBD5rV"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define FIREBASE_HOST "test-8c359-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "waqtMbJlSVYaaOJkTpTiWoElsIwFKOSWRiJb7OyQ"
#define WIFI_SSID "Heisenberg"
#define WIFI_PASSWORD "scanf(&n)"



void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  WiFi.enableInsecureWEP();

  // connect to wifi.
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("didn't get");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  delay(500);
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST);

}

void loop()
{
  pushToFirebase(200, "biscuit");
  Serial.println(getUsername());
  delay(3600000);
}

String getUsername(){
  return Firebase.getString("username");  
}

void pushToFirebase(float tk, String items){
  
  while(true){
    DynamicJsonBuffer jsonBuffer;
    JsonObject& purchase = jsonBuffer.createObject();
    purchase["price"] = tk;
    purchase["items"] = items;
    purchase["buyer"] = "sadman";
  
  
    Firebase.push("purchases", purchase);
    if (Firebase.failed()) {
        Serial.print("Failed to push purchase to firebase");
        Serial.println(Firebase.error());
        delay(1000);
        continue;
    }
    Serial.println("pushed purchase to firebase"); 
    break;
  }
  
  
}
