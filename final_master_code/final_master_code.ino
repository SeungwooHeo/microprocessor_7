#include <Wire.h>

#define ML_Ctrl 2
#define ML_PWM 5
#define MR_Ctrl 4
#define MR_PWM 6

int red = 0;
int blue = 0;
int green = 0;
int distance1 = 0;
int distance2 = 0;
int distance3 = 0;

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    // 모터제어 pin 초기화
    pinMode(ML_Ctrl, OUTPUT);
    pinMode(ML_PWM, OUTPUT);
    pinMode(MR_Ctrl, OUTPUT);
    pinMode(MR_PWM, OUTPUT);
}

void loop()
{
    // 통신으로 값 가져오기
    Wire.requestFrom(9, sizeof(red) + sizeof(blue) + sizeof(green) + sizeof(distance1) + sizeof(distance2) + sizeof(distance3));

    while (Wire.available() >= sizeof(red))
    {
        Wire.readBytes((byte *)&red, sizeof(red));
    }
    while (Wire.available() >= sizeof(blue))
    {
        Wire.readBytes((byte *)&blue, sizeof(blue));
    }
    while (Wire.available() >= sizeof(green))
    {
        Wire.readBytes((byte *)&green, sizeof(green));
    }
    while (Wire.available() >= sizeof(distance1))
    {
        Wire.readBytes((byte *)&distance1, sizeof(distance1));
    }
    while (Wire.available() >= sizeof(distance2))
    {
        Wire.readBytes((byte *)&distance2, sizeof(distance2));
    }
    while (Wire.available() >= sizeof(distance3))
    {
        Wire.readBytes((byte *)&distance3, sizeof(distance3));
    }

    // 값 출력 (옵션)
    Serial.print("Red: ");
    Serial.print(red);
    Serial.print("\tBlue: ");
    Serial.print(blue);
    Serial.print("\tGreen: ");
    Serial.print(green);
    Serial.print("\tDistance 1: ");
    Serial.print(distance1);
    Serial.print("\tDistance 2: ");
    Serial.print(distance2);
    Serial.print("\tDistance 3: ");
    Serial.println(distance3);

    // // 컬러센서 r값이 200을 넘으면 모터 멈춤
    // if (red > 250)
    // {
    //     stop();
    // }
    // // 컬러센서 90 < r <= 140 & blue <= 60 일 경우 감속
    // else if (red > 150 && red <= 250)
    // {
    //     decreaseSpeed();
    // }
    // // 나머지 경우
    // else
    // {
    //     normalSpeed();
    // }

    // // 초음파
    // if (distance1 < 13 || distance2 < 13 || distance3 < 13)
    // {
    //     stop();
    // }
    // else
    // {
    //     normalSpeed();
    // }

    //  빨간불 이거나 충돌조건이면 Stop
    if (red > 250 || distance1 < 13 || distance2 < 13 || distance3 < 13) {
        stop();
    }
    else if (red > 150 && red <= 250)
    {
        decreaseSpeed();
    }
    // 나머지 경우
    else
    {
        normalSpeed();
    }

    //  아니면

    delay(10); // 적절한 딜레이 추가
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
    analogWrite(ML_PWM, 80);

    digitalWrite(MR_Ctrl, HIGH);
    analogWrite(MR_PWM, 80);
}

// 모터 정지
void stop()
{
    digitalWrite(ML_Ctrl, LOW);
    analogWrite(ML_PWM, 0);

    digitalWrite(MR_Ctrl, LOW);
    analogWrite(MR_PWM, 0);
}