#include <Wire.h>
#include "Adafruit_TCS34725.h"

// 모터 제어 핀 정의
#define ML_Ctrl 2
#define ML_PWM 5
#define MR_Ctrl 4
#define MR_PWM 6

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  
  // 모터 제어 핀 초기화
  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);
  
  // 컬러센서 초기화
  if (tcs.begin()) {
    // Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found... check your connections");
    while (1); // 프로그램 정지
  }
}

void loop() {
  // 컬러센서에서 읽은 값을 가져오기
  float red, green, blue;
  tcs.getRGB(&red, &green, &blue);

  // r값이 200을 넘으면 모터 멈춤
  if (red > 140) {
    stopMotors();
  } else if (red > 90 && red <= 140 && blue <= 60) {
    // r값이 100 이상 200 이하이면서 b값이 60 이하이면 속도를 줄임
    decreaseSpeed();
  } else {
    // 그 외의 경우 모터 정상 동작
    normalSpeed();
  }

  // 결과를 시리얼로 출력
  Serial.print("R:\t"); Serial.print(int(red)); 
  Serial.print("\tG:\t"); Serial.print(int(green)); 
  Serial.print("\tB:\t"); Serial.println(int(blue));
  
  delay(500); // 0.5초 대기
}

// 모터 정지 함수
void stopMotors() {
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 0);
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 0);
}

// 모터 속도 감소 함수
void decreaseSpeed() {
  analogWrite(ML_PWM, 80);
  analogWrite(MR_PWM, 80);
}

// 모터 정상 속도 함수
void normalSpeed() {
  analogWrite(ML_PWM, 105);
  analogWrite(MR_PWM, 105);
}