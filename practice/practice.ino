#include<ArduinoJson.h>
#include<ArduinoJson.hpp>
#include<FirebaseArduino.h>
#include<ESP8266WiFi.h>
#include<Stepper.h>
#define wifi "Heisenberg"
#define pass "scanf(&n)"
#define host "test-8c359-default-rtdb.firebaseio.com"
#define auth "waqtMbJlSVYaaOJkTpTiWoElsIwFKOSWRiJb7OyQ"
const int steps = 500;
const int pin1 = D0;
const int pin2 = D1;
const int pin3 = D2;
const int pin4 = D3;
const int pin5 = D5;
const int pin6 = D6;
const int pin7 = D7;
const int pin8 = D8;
Stepper stepper(steps,pin1,pin3,pin2,pin4);
Stepper stepper2(steps,pin5,pin7,pin6,pin8);
#define IR_PIN D0
#define IR_PIN2 D7

void setup() {
  pinMode(IR_PIN, INPUT);
  pinMode(IR_PIN2, INPUT);
  Serial.begin(9600);
  WiFi.enableInsecureWEP();
  WiFi.begin(wifi,pass);
  Serial.println("connecting...");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("trying to connect");
    delay(500);
  }
  Serial.println();
  Serial.println("connected");
  Serial.println(WiFi.localIP());
  stepper.setSpeed(55);
  delay(500);
  stepper2.setSpeed(70);
  delay(500);
  Firebase.begin(host,auth);
}

void loop() {
  String value = Firebase.getString("/Payment/Option");
  Serial.println("val = " + value);
  delay(9000);
  bool bb = 1;
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
    }
  }
  delay(1000);
}
