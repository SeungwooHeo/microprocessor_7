#include <Wire.h>
#define ML_Ctrl 2
#define ML_PWM 5
#define MR_Ctrl 4
#define MR_PWM 6

int red = 0;
int blue = 0;
int green = 0;
int brightness = 0;
int distance1 = 0;
int distance2 = 0;
int distance3 = 0;

int newFlag = 0;

void receiveEvent( int param ) {

  if( newFlag == 0 ) {
    Wire.readBytes((byte *)&red, sizeof(red));
    Wire.readBytes((byte *)&blue, sizeof(blue));
    Wire.readBytes((byte *)&green, sizeof(green));
    Wire.readBytes((byte *)&brightness, sizeof(brightness));    
    Wire.readBytes((byte *)&distance1, sizeof(distance1));
    Wire.readBytes((byte *)&distance2, sizeof(distance2));
    Wire.readBytes((byte *)&distance3, sizeof(distance3));
    newFlag = 1;  
  }
}

void setup()
{
    Serial.begin(9600);
    Wire.begin(9);
    Wire.onReceive( receiveEvent );

    // 모터제어 pin 초기화
    pinMode(ML_Ctrl, OUTPUT);
    pinMode(ML_PWM, OUTPUT);
    pinMode(MR_Ctrl, OUTPUT);
    pinMode(MR_PWM, OUTPUT);
}

void loop()
{
    if( newFlag == 1 ) {
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

        //  빨간불 이거나 충돌조건이면 Stop
        if (red > 500 || distance1 < 13 || distance2 < 13 || distance3 < 13) {
          stop();
        }
        else if (red > 60)
        {
          decreaseSpeed();
        }
        else
        {
          normalSpeed();
        }
        newFlag = 0;
    }
    delay(3); // 적절한 딜레이 추가
}

// 정상 주행
void normalSpeed()
{
    digitalWrite(ML_Ctrl, HIGH);
    analogWrite(ML_PWM, 140);

    digitalWrite(MR_Ctrl, HIGH);
    analogWrite(MR_PWM, 140);
}

// 감속 주행
void decreaseSpeed()
{
    digitalWrite(ML_Ctrl, HIGH);
    analogWrite(ML_PWM, 200);

    digitalWrite(MR_Ctrl, HIGH);
    analogWrite(MR_PWM, 200);
}

// 정지
void stop()
{
    digitalWrite(ML_Ctrl, LOW);
    analogWrite(ML_PWM, 0);

    digitalWrite(MR_Ctrl, LOW);
    analogWrite(MR_PWM, 0);
}
