const int BUZZER_PIN = 2;

void setup() {
  analogWrite(11,255);
  pinMode(12,1);
  pinMode(13,0);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(12,1);
  delayMicroseconds(10);
  digitalWrite(12,0);
  long t = pulseIn(13,1);
  long d = (t/2)*0.034;
  Serial.println(d);

  if (d < 13){
    int buzzerFrequency = 2038;
    tone(BUZZER_PIN, buzzerFrequency);
  } else {
    noTone(BUZZER_PIN);
  }

  delay(100);;
}
