const int TRIG_PIN1 = 3; // 초음파 센서의 TRIG 핀
const int ECHO_PIN1 = 2; // 초음파 센서의 ECHO 핀
const int TRIG_PIN2 = 4; // 초음파 센서의 TRIG 핀
const int ECHO_PIN2 = 5; // 초음파 센서의 ECHO 핀
const int TRIG_PIN3 = 9; // 초음파 센서의 TRIG 핀
const int ECHO_PIN3 = 10; // 초음파 센서의 ECHO 핀
const int BUZZER_PIN = 8; // 부저 핀

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(TRIG_PIN3, OUTPUT);
  pinMode(ECHO_PIN3, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  long duration1, distance1;
  long duration2, distance2;
  long duration3, distance3;

  // 초음파 센서 1
  digitalWrite(TRIG_PIN1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);
  duration1 = pulseIn(ECHO_PIN1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // 초음파 센서 2
  digitalWrite(TRIG_PIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  duration2 = pulseIn(ECHO_PIN2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  // 초음파 센서 3
  digitalWrite(TRIG_PIN3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN3, LOW);
  duration3 = pulseIn(ECHO_PIN3, HIGH);
  distance3 = duration3 * 0.034 / 2;

  // 물체가 10cm 이내에 감지되면 부저 울림
  if (distance1 < 10 || distance2 < 10 || distance3 < 10) {
    int buzzerFrequency = 2038; // 부저 주파수 (2038Hz)
    tone(BUZZER_PIN, buzzerFrequency); // 부저 울리기
  } else {
    noTone(BUZZER_PIN); // 부저 멈춤
  }

  delay(100); // 0.1초 대기
}