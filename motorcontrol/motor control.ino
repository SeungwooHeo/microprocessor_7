//MOTOR A 제어를 위한 핀 두개를 선언
#include <Wire.h>

#define R_ctrl 4 //
#define R_PWM 6 // 오른쪽 위
#define L_ctrl 2 //
#define L_PWM 5// 왼쪽 위

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  pinMode(R_ctrl, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_ctrl, OUTPUT);
  pinMode(L_PWM, OUTPUT);
}

void loop()
{
  foward();
}

//모터 움직임
void forward()
{
  digitalWrite(R_ctrl, HIGH);
  analogWrite(R_PWM, 200);
  digitalWrite(L_ctrl, HIGH);
  analogWrite(L_PWM, 200);
}

void stop()
{
  digitalWrite(R_ctrl, LOW);
  analogWrite(R_PWM, 0);
  digitalWrite(L_ctrl, LOW);
  analogWrite(L_PWM, 0);

}