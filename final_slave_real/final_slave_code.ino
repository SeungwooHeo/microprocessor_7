#include <Wire.h>
#include "Adafruit_TCS34725.h"

// SoftwareWire softWire(2, 3);

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

const int BUZZER_PIN = 2;
const int trigPin1 = 8;
const int echoPin1 = 9;
const int trigPin2 = 10;
const int echoPin2 = 11;
const int trigPin3 = 12;
const int echoPin3 = 13;

int red;
int blue;
int green;
int distance1;
int distance2;
int distance3;
int brightness;

void setup() {
  Serial.begin(9600);
  Wire.begin();  //

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  if (tcs.begin()) {
    Serial.println("Found sensor");
    tcs.setInterrupt(false);
  } else {
    Serial.println("No TCS34725 found... check your connections");
    while (1); // 프로그램 정지
  }
}

void loop() {
  // Trigger ultrasonic sensor 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  long duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // Trigger ultrasonic sensor 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  long duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  // Trigger ultrasonic sensor 3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  long duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2;

  // Print distances
  Serial.print("Distance 1: "); Serial.print(distance1);
  Serial.print("\tDistance 2: "); Serial.print(distance2);
  Serial.print("\tDistance 3: "); Serial.println(distance3);

  if (distance1 < 13 || distance2 < 13 || distance3 < 13) {
    int buzzerFrequency = 2038;
    tone(BUZZER_PIN, buzzerFrequency);
  } else {
    noTone(BUZZER_PIN);
  }

  // 컬러 센서
  float r, g, b;
  tcs.getRawData(&red, &green, &blue, &brightness);

  // Print color
  Serial.print("R:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
  Serial.print("\tBrightness:\t"); Serial.print(brightness);  // 추가: 밝기 출력
  Serial.println("");

  // 전송
  requestEvent();

  delay(50);
}

void requestEvent() {
  // 컬러 센서 데이터 전송
  Wire.beginTransmission(9); // 8은 슬레이브의 I2C 주소입니다.
  Wire.write((byte*)&red, sizeof(red));
  Wire.write((byte*)&green, sizeof(green));
  Wire.write((byte*)&blue, sizeof(blue));
  Wire.write((byte*)&brightness, sizeof(brightness));

  // 초음파 센서 데이터 전송
  Wire.write((byte*)&distance1, sizeof(distance1));
  Wire.write((byte*)&distance2, sizeof(distance2));
  Wire.write((byte*)&distance3, sizeof(distance3));
  Wire.endTransmission();
}