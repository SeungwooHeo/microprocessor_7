#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <SoftwareSerial.h>

#define ML_Ctrl 2
#define ML_PWM 5
#define MR_Ctrl 4
#define MR_PWM 6

SoftwareSerial Serial1(9,10);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

int red1 = 0;
int blue1 = 0;
int green1 = 0;
int brightness1 = 0;

int red2 = 0;
int blue2 = 0;
int green2 = 0;
int brightness2 = 0;

int distance1;
int distance2;
int distance3;

void setup()
{
    Serial.begin(9600);
    Serial1.begin(115200);

    Wire.begin();

    // 모터제어 pin 초기화
    pinMode(ML_Ctrl, OUTPUT);
    pinMode(ML_PWM, OUTPUT);
    pinMode(MR_Ctrl, OUTPUT);
    pinMode(MR_PWM, OUTPUT);
}

void loop()
{
  // 컬러 센서 읽기- 센서1
  tcs.getRawData(&red1, &green1, &blue1, &brightness1);

  // Print color values to Serial Monitor
  // Serial.print("TCS1   ");
  // Serial.print("R:\t"); Serial.print(red1);
  // Serial.print("\tG:\t"); Serial.print(green1);
  // Serial.print("\tB:\t"); Serial.print(blue1);
  // Serial.print("\tBrightness:\t"); Serial.print(brightness1);  // 추가: 밝기 출력
  // Serial.println("");

  if( Serial1.available()) {
    String str = Serial1.readStringUntil('\n');
    // ....+....1....+....2....+....3.
    // [0126,0139,0105,0064,0019,0038]
    red2      = str.substring(1,5).toInt();
    green2    = str.substring(7,12).toInt();
    blue2     = str.substring(12,17).toInt(); 
    distance1 = str.substring(17,22).toInt(); 
    distance2 = str.substring(22,27).toInt(); 
    distance3 = str.substring(27,32).toInt(); 

    // Serial.println("Recv : " + str);
    // Serial.print("TCS2   ");
    // Serial.print("R:\t"); Serial.print(red2);
    // Serial.print("\tG:\t"); Serial.print(green2);
    // Serial.print("\tB:\t"); Serial.print(blue2);
    // Serial.println("");

    // Serial.print("Distance 1: "); Serial.print(distance1);
    // Serial.print("\tDistance 2: "); Serial.print(distance2);
    // Serial.print("\tDistance 3: "); Serial.println(distance3);
  }

  //  빨간불 이거나 충돌조건이면 Stop
  if (red1 > 180 || distance1 < 13 || distance2 < 13 || distance3 < 13) {
    debug("Stop");
    stop();
  }
  else if (red2 > 60)
  {
    debug("decreaseSpeed");
    decreaseSpeed();
  }
  // 나머지 경우
  else
  {
    normalSpeed();
  }
  
  delay(50); // 적절한 딜레이 추가
}

// 모터 정상 속도
void normalSpeed()
{
    digitalWrite(ML_Ctrl, HIGH);
    analogWrite(ML_PWM, 105);

    digitalWrite(MR_Ctrl, HIGH);
    analogWrite(MR_PWM, 105);
}

// 모터 감속
void decreaseSpeed()
{
    digitalWrite(ML_Ctrl, HIGH);
    analogWrite(ML_PWM, 200);

    digitalWrite(MR_Ctrl, HIGH);
    analogWrite(MR_PWM, 200);
}

// 모터 정지
void stop()
{
    digitalWrite(ML_Ctrl, LOW);
    analogWrite(ML_PWM, 0);

    digitalWrite(MR_Ctrl, LOW);
    analogWrite(MR_PWM, 0);
}

void debug(String str) {
  
  Serial.println("Action = " + str);

  Serial.print("  TCS1   ");
  Serial.print("  R:\t"); Serial.print(red1);
  Serial.print("  \tG:\t"); Serial.print(green1);
  Serial.print("  \tB:\t"); Serial.print(blue1);
  Serial.print("  \tBrightness:\t"); Serial.print(brightness1);  // 추가: 밝기 출력
  Serial.println("");

  Serial.print("  TCS2   ");
  Serial.print("  R:\t"); Serial.print(red2);
  Serial.print("  \tG:\t"); Serial.print(green2);
  Serial.print("  \tB:\t"); Serial.print(blue2);
  Serial.println("");

  Serial.print("  Distance 1: "); Serial.print(distance1);
  Serial.print("  \tDistance 2: "); Serial.print(distance2);
  Serial.print("  \tDistance 3: "); Serial.println(distance3);  

}