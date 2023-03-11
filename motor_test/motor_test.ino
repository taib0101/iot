#include <FirebaseArduino.h>//
#include <ArduinoJson.h>//
#include <ArduinoJson.hpp>
#include <ESP8266WiFi.h>//
#include <Stepper.h>//
#define WIFI "Matrix "
#define PASS "alif@1234"
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
#define IR_PIN D0
#define IR_PIN2 D5
#define host "firebase link"
#define auth "firebase auth key"

void setup() {
  pinMode(IR_PIN, INPUT);//sensor
  Serial.begin(9600);
  WiFi.enableInsecureWEP();
  WiFi.begin(WIFI,PASS);
  Serial.println("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("tring to load");
    delay(500);
  }
  Serial.println();
  Serial.println("connected: ");//wifi
  delay(500);
  Serial.println(WiFi.localIP());
  stepper.setSpeed(70);//stepper
  delay(500);
  stepper2.setSpeed(70);
  delay(500);
  Firebase.begin(host,auth);//firebase

}

void loop() {
  bool bb = 1;
  string value = Firebae.getString("/purchase/option")
  for(int i = 1; i <= 3 && bb; ++i)
    {
      for(int j = 1; j <= 5 && bb; ++j)
      {
        stepper2.step(stepsPerRevolution);
        delay(1000);
        bool sensorValue = digitalRead(IR_PIN);
        Serial.println(sensorValue);
        if(sensorValue == LOW)
        {
          bb = 0;
          // digitalWrite(LED_PIN, HIGH);          
          Serial.println("Object detected!");
        }
      }
    }

}
