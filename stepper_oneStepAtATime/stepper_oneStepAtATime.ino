#include <Stepper.h>

const int stepsPerRevolution = 200;
const int motorPin1 = D1;
const int motorPin2 = D2;
const int motorPin3 = D3;
const int motorPin4 = D4;

Stepper stepper(stepsPerRevolution, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  stepper.setSpeed(60);
}

void loop() {
  stepper.step(stepsPerRevolution / 4);
  delay(1000);
  stepper.step(-stepsPerRevolution / 4);
  delay(1000);
}
