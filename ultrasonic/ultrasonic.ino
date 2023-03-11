#define trigPin D0
#define echoPin D1

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(40);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  delay(500);
  Serial.println(duration);
  long distance = (duration/2) / 29.1;
  
  if (distance > 10) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  else
    Serial.println("None");
  delay(1000);
}