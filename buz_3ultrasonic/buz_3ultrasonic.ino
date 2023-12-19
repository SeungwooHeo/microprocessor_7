const int BUZZER_PIN = 2;

const int trigPin1 = 8;
const int echoPin1 = 9;
const int trigPin2 = 10;
const int echoPin2 = 11;
const int trigPin3 = 12;
const int echoPin3 = 13;

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  long duration1 = pulseIn(echoPin1, HIGH);
  int distance1 = duration1 * 0.034 / 2;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  long duration2 = pulseIn(echoPin2, HIGH);
  int distance2 = duration2 * 0.034 / 2;

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  long duration3 = pulseIn(echoPin3, HIGH);
  int distance3 = duration3 * 0.034 / 2;

  Serial.print("Distance 1: "); Serial.print(distance1);
  Serial.print("\tDistance 2: "); Serial.print(distance2);
  Serial.print("\tDistance 3: "); Serial.println(distance3);

  if (distance1 < 13 || distance2 < 13 || distance3 < 13) {
    int buzzerFrequency = 2038;
    tone(BUZZER_PIN, buzzerFrequency);
  } else {
    noTone(BUZZER_PIN);
  }

  delay(100);
}
